#pragma once

#include <vector>

#include "shared/stfr_api.hpp"

namespace stfr_renderer::opengl {

    class STFR_API OpenGLBackend {
        public:
            void Initialize(void* nativeWindow);
            void Clear(float r, float g, float b, float a);
            void Present();
    };

}
