/**
 * @file main.cpp
 *
 * @brief ...
 *
 * @author Adnan FAIZE <adnanfaize@gmail.com>
 */

#include <cstdlib>
#include <print>

#define GAME_VERSION "v.1"

#ifdef STFR_DEBUG
    #define CR_HOST
    #include <cr.h>
#else

#endif

int main(int argc, char** argv) {

#ifdef STFR_DEBUG
    std::println("[INFO] Booting in DEBUG mode version {} with Hot-Reloading.", GAME_VERSION);
    cr_plugin ctx;
    cr_plugin_load(ctx, LIB_GAME_ENTRYPOINT);

    while (true) {

        cr_plugin_update(ctx);
        if (ctx.version == 0) { break; }
    }

    cr_plugin_close(ctx);
#else
    std::println("[INFO] Booting in RELEASE mode version {}", GAME_VERSION);

    while (true) {

    }
#endif

    return EXIT_SUCCESS;
}
