/**
 * @file hash.hpp
 *
 * @brief Function to calculate the hash of a file using the FNV-1a algorithm.
 *
 * @author Adnan FAIZE <>
 */

#pragma once

#include <string>
#include <fstream>
#include <cstdint>

namespace stfr::core {

    inline uint64_t CalculateFileHash(const std::string& filepath) {
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

}
