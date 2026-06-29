import sys


def get_fnv1a_hash(filepath):
    hash_val = 0xCBF29CE484222325
    with open(filepath, "rb") as f:
        while chunk := f.read(4096):
            for byte in chunk:
                hash_val ^= byte
                hash_val = (hash_val * 0x100000001B3) & 0xFFFFFFFFFFFFFFFF
    return hash_val


def generate_header(output_path, dlls):
    with open(output_path, "w") as f:
        f.write("#pragma once\n\n")
        f.write("#include <cstdint>\n\n")
        f.write("namespace stfr_core::integrity {\n\n")
        f.write(
            "\tstatic constexpr struct { const char* name; uint64_t hash; } EXPECTED_HASHES[] = {\n"
        )
        for name, path in dlls.items():
            hash = get_fnv1a_hash(path)
            f.write(f'\t\t{{"{name}", 0x{hash:016x}ULL}},\n')
        f.write("\t};\n\n")
        f.write("}\n")


output_file = sys.argv[1]
dlls = dict(item.split("=") for item in sys.argv[2:])
generate_header(output_file, dlls)
