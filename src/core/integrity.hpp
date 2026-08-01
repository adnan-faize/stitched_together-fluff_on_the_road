/**
 * @file integrity.hpp
 *
 * @brief Calculate and check the hash of a file using FNV-1a algorithm.
 */

#pragma once

#include <string>
#include <fstream>
#include <cstdint>

namespace stfr_core {

    inline static uint64_t calculateFileHash(const std::string& filepath) {
        constexpr uint64_t FNV_OFFSET_BASIS = 0xcbf29ce484222325ULL;
        constexpr uint64_t FNV_PRIME = 0x100000001b3ULL;

        std::ifstream file(filepath, std::ios::binary);

        if (!file.is_open()) { return 0; }

        uint64_t hash = FNV_OFFSET_BASIS;
        char byte;

        while (file.get(byte)) {
            hash ^= static_cast<uint8_t>(byte);
            hash *= FNV_PRIME;
        }

        return hash;
    }

    inline bool checkFileHash(const std::string& filepath) {
        // TODO
        return false;
    }

}
