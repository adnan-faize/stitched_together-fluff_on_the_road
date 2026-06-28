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

#include "utils/logger.hpp"

int main(int argc, char** argv) {
    stfr::utils::Logger::Init("stfr.log");


#ifdef STFR_DEBUG
    stfr::utils::Logger::Log(stfr::utils::LogLevel::INFO, "[INFO] Booting in DEBUG mode version {} with Hot-Reloading.", GAME_VERSION);
    cr_plugin ctx;
    cr_plugin_load(ctx, LIB_GAME_ENTRYPOINT);


    while (true) {

        cr_plugin_update(ctx);
        if (ctx.version == 0) { break; }
    }

    cr_plugin_close(ctx);
#else
    stfr::utils::Logger::Log(stfr::utils::LogLevel::Info, "[INFO] Booting in RELEASE mode version {}.", GAME_VERSION);

    while (true) {

    }
#endif

    stfr::utils::Logger::Shutdown();

    return EXIT_SUCCESS;
}
