#pragma once

#include <string_view>

#include "shared/stfr_api.hpp"

namespace stfr_platform::ps4 {

    class STFR_API Ps4Backend {
        public:
            void Initialize(int width, int height, std::string_view title);
            void PollEvents();
            bool ShouldClose() const;
            void SwapBuffers();
            float GetTime() const;
            void* GetNativeWindow() const { return nullptr; }
    };

}
