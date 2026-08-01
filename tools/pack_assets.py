# This script is used to pack assets into a single binary file for use in the game engine.
# It takes a directory of assets (images, sounds, etc.) and creates a binary file that
# can be loaded by the engine at runtime.
#
# Format specification :
# Header    : "STFR_PAK" (8 bytes)
# Num Files : uint32     (4 bytes)
# File Entries :
#   Path   : char[128]
#   Offset : uint32
#   Size   : uint32
# Data : Raw binary file data

import sys
import struct
import shutil
from pathlib import Path
from typing import Union

# --- Format Constants ---
HEADER_MAGIC = b"STFR_PAK"
MAX_PATH_LENGTH = 128

# '<8sI' means: Little-endian (<), 8-byte string (8s), unsigned int (I)
HEADER_FORMAT = '<8sI'
# '<128sII' means: Little-endian (<), 128-byte string (128s), two unsigned ints (II)
TOC_ENTRY_FORMAT = f'<{MAX_PATH_LENGTH}sII'


def pack_directory(source_dir: Union[str, Path], output_file: Union[str, Path]) -> None:
    source_path = Path(source_dir)
    output_path = Path(output_file)

    if not source_path.is_dir():
        print(f"Error: Directory '{source_path}' does not exist.")
        sys.exit(1)

    # 1. Collect all files and calculate their metadata
    toc_entries = []

    # rglob('*') recursively finds all items in the directory
    for file_path in source_path.rglob('*'):
        if file_path.is_file():
            # Create a relative path and force forward slashes for the game engine
            rel_path = file_path.relative_to(source_path).as_posix()
            path_encoded = rel_path.encode('utf-8')

            if len(path_encoded) >= MAX_PATH_LENGTH:
                print(f"Error: Path '{rel_path}' is too long (>= {MAX_PATH_LENGTH} bytes).")
                sys.exit(1)

            # Get exact file size in bytes
            size = file_path.stat().st_size
            toc_entries.append((path_encoded, file_path, size))

    num_files = len(toc_entries)
    if num_files == 0:
        print(f"Warning: No files found in '{source_path}'.")
        return

    print(f"Packing {num_files} files into '{output_path}'...")

    # 2. Calculate offsets
    header_size = struct.calcsize(HEADER_FORMAT)
    toc_size = struct.calcsize(TOC_ENTRY_FORMAT) * num_files

    # The actual file data starts immediately after the Header and the Table of Contents
    current_data_offset = header_size + toc_size

    # 3. Write the binary package
    try:
        with output_path.open('wb') as out_file:

            # --- Write Header ---
            out_file.write(struct.pack(HEADER_FORMAT, HEADER_MAGIC, num_files))

            # --- Write Table of Contents (ToC) ---
            for path_encoded, _, size in toc_entries:
                # Pad the string with null bytes until it is exactly 128 bytes long
                path_buf = path_encoded.ljust(MAX_PATH_LENGTH, b'\0')

                # Pack the padded path, the offset, and the size all at once
                out_file.write(struct.pack(TOC_ENTRY_FORMAT, path_buf, current_data_offset, size))

                # Advance the offset for the next file
                current_data_offset += size

            # --- Write Raw File Data ---
            for _, full_path, _ in toc_entries:
                with full_path.open('rb') as in_file:
                    # shutil.copyfileobj is much faster and uses almost zero RAM
                    # because it streams the data in chunks instead of reading it all at once.
                    shutil.copyfileobj(in_file, out_file)

        print("Packing complete!")

    except IOError as e:
        print(f"File system error during packing: {e}")
        sys.exit(1)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python pack_assets.py <source_directory> <output_file>")
        sys.exit(1)

    pack_directory(sys.argv[1], sys.argv[2])
