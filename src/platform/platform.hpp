#pragma once

#include <cstdint>
#include <string_view>

#include "shared/stfr_api.hpp"

namespace stfr_platform {

    class STFR_API Platform {
        public:
            void Initialize(uint16_t width, uint16_t height, std::string_view title);
            void Initialize(std::string_view title);

            void PollEvents();
            bool ShouldClose() const;
            void SwapBuffers();
            float GetTime() const;
            void* GetNativeWindow() const;

        private:
            void* m_Window = nullptr;
    };

}
