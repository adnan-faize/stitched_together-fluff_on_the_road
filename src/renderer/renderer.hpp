#pragma once

#ifdef STFR_RENDERER_OPENGL
    #include "opengl/opengl_backend.hpp"
#elifdef STFR_RENDERER_METAL
    #include "metal/metal_backend.hpp"
#endif

namespace stfr_renderer {

    #ifdef STFR_RENDERER_OPENGL
        using Renderer = opengl::OpenGLBackend;
    #elifdef STFR_RENDERER_METAL
        using Renderer = metal::MetalBackend;
    #endif

}
