/**
 * @file main.cpp
 *
 * @brief Main entry point for the application.
 *
 * @author Adnan FAIZE
 */

#include <cstdlib>

#include "platform/platform.hpp"
#include "renderer/renderer.hpp"

int main(int argc, char** argv) {
    stfr_platform::Platform platform;
    stfr_renderer::Renderer renderer;

    platform.Initialize(1280, 720, "Stitched Together : Fluff on The Road");
    renderer.Initialize(platform.GetNativeWindow());

    while (!platform.ShouldClose()) {
        platform.PollEvents();

        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);
        renderer.Present();

        platform.SwapBuffers();
    }

    return EXIT_SUCCESS;
}
