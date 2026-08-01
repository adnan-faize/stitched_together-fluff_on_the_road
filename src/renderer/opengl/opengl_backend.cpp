#include <glad/glad.h>

#include "opengl_backend.hpp"

namespace stfr_renderer::opengl {

    void STFR_API OpenGLBackend::Initialize(void* nativeWindow) {
        if (!gladLoadGL()) {}
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void STFR_API OpenGLBackend::Clear(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void STFR_API OpenGLBackend::Present() {

    }

}
