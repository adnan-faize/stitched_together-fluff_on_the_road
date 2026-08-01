#include <string_view>

#include <GLFW/glfw3.h>

#ifdef STFR_RENDERER_METAL
    #define GLFW_EXPOSE_NATIVE_COCOA
    #include <GLFW/glfw3native.h>
#endif

#include "platform/platform.hpp"

namespace stfr_platform {

    void STFR_API Platform::Initialize(uint16_t width, uint16_t height, std::string_view title) {
        glfwInit();

        #ifdef STFR_RENDERER_OPENGL
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #elifdef STFR_RENDERER_METAL
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        #endif

        m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

        #ifdef STFR_RENDERER_OPENGL
            glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
        #endif
    }

    void STFR_API Platform::Initialize(std::string_view title) {
        Initialize(1280, 720, title);
    }

    void STFR_API Platform::PollEvents() {
        glfwPollEvents();
    }

    bool STFR_API Platform::ShouldClose() const {
        return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window));
    }

    void STFR_API Platform::SwapBuffers() {
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
    }

    float STFR_API Platform::GetTime() const {
        return static_cast<float>(glfwGetTime());
    }

    void* STFR_API Platform::GetNativeWindow() const {
        #ifdef STFR_RENDERER_METAL
            return glfwGetCocoaWindow(static_cast<GLFWwindow*>(m_Window));
        #else
            return m_Window;
        #endif
    }
}
