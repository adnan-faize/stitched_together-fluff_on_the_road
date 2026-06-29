/**
 * @file main.cpp
 *
 * @brief ...
 *
 * @author Adnan FAIZE <adnanfaize@gmail.com>
 */

#include <cstdlib>

#ifdef STFR_DEBUG
    #define CR_HOST
    #include <cr.h>
#else

#endif

#include "core/logger.hpp"
#include "core/hash.hpp"

int main(int argc, char** argv) {
    stfr_core::Logger::Init("stfr.log");

#ifdef STFR_DEBUG
    stfr_core::Logger::Log(stfr_core::LogLevel::INFO, "Booting in DEBUG mode version {} with Hot-Reloading.", GAME_VERSION);
    cr_plugin ctx;
    cr_plugin_load(ctx, LIB_GAME_ENTRYPOINT);

    while (true) {

        cr_plugin_update(ctx);
        if (ctx.version == 0) { break; }
    }

    cr_plugin_close(ctx);
#else
    stfr_core::Logger::Log(stfr_core::LogLevel::Info, "Booting in RELEASE mode version {}.", GAME_VERSION);

    while (true) {

    }
#endif

    stfr_core::Logger::Shutdown();

    return EXIT_SUCCESS;
}

#include "dll_hashes.h"

void VerifyEngineIntegrity() {
    for (const auto& entry : stfr_core::integrity::EXPECTED_HASHES) {
        uint64_t actual = stfr_core::CalculateFileHash(entry.name);
        if (actual != entry.hash) { exit(-1); }
    }
}
