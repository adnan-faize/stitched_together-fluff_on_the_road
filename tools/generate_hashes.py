# Hash generation script to verify the integrity of shared libraries on startup.
# This script computes the 64-bit FNV-1a hash of each shared library and
# generates a C++ header file containing the expected hashes.

import sys
import argparse
from pathlib import Path
from typing import Dict

# --- FNV-1a 64-bit Constants ---
FNV_OFFSET_BASIS = 0xCBF29CE484222325
FNV_PRIME = 0x100000001B3
FNV_MASK = 0xFFFFFFFFFFFFFFFF


def compute_fnv1a_hash(filepath: Path) -> int:
    """Computes the 64-bit FNV-1a hash of a binary file."""
    hash_val = FNV_OFFSET_BASIS

    with filepath.open("rb") as f:
        # 64KB chunks reduce disk I/O overhead compared to 4KB
        while chunk := f.read(65536):
            for byte in chunk:
                # Combined into a single line to slightly reduce Python interpreter loop overhead
                hash_val = ((hash_val ^ byte) * FNV_PRIME) & FNV_MASK

    return hash_val


def generate_cpp_header(output_path: Path, shared_libs: Dict[str, Path]) -> None:
    """Generates a cleanly formatted C++ header with the expected hashes."""

    entries = []
    for name, path in shared_libs.items():
        if not path.is_file():
            print(f"Warning: File '{path}' not found. Skipping...")
            continue

        hash_val = compute_fnv1a_hash(path)
        # Format as a 16-character hex string padded with zeros
        entries.append(f'\t\t{{"{name}", 0x{hash_val:016x}ULL}}')

    if not entries:
        print("Error: No valid libraries were found to hash. Aborting.")
        sys.exit(1)

    # Join the entries with commas and newlines for the C++ array
    entries_str = ",\n".join(entries)

    # Using a multiline string makes the C++ generation much easier to read/edit
    header_template = f"""\
#pragma once

#include <cstdint>

namespace stfr_core::integrity {{

    static constexpr struct {{
        const char* name;
        uint64_t hash;
    }} EXPECTED_HASHES[] = {{
{entries_str}
    }};

}} // namespace stfr_core::integrity
"""

    # Write the entire template to disk at once
    output_path.write_text(header_template, encoding="utf-8")
    print(f"Successfully generated integrity header at '{output_path}'")


def main():
    parser = argparse.ArgumentParser(description="Generate FNV-1a hashes for game engine shared libraries.")
    parser.add_argument("output_file", type=Path, help="Path to the generated C++ header file (e.g. src/core/hashes.h)")
    parser.add_argument("libraries", nargs="+", help="Shared libraries in the format 'HeaderEntryName=path/to/lib.dll'")

    args = parser.parse_args()

    # Safely parse the key=value arguments
    shared_libs = {}
    for item in args.libraries:
        try:
            name, path_str = item.split("=", 1)
            shared_libs[name] = Path(path_str)
        except ValueError:
            print(f"Error: Invalid argument format '{item}'. Expected 'Name=Path'.")
            sys.exit(1)

    generate_cpp_header(args.output_file, shared_libs)


if __name__ == "__main__":
    main()
