/**
 * @file logger.hpp
 *
 * @author Adnan FAIZE
 */

#pragma once

#include <cstdint>
#include <string_view>

namespace stfr_core {

    enum class LogLevel : uint8_t {
        TRACE = 0,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class Logger {
        public:
            static void Initialize();
            static void Shutdown();

            // Callback passed to ...
            static void LogCallback(LogLevel level, const char* message);

        private:
            static void Log(LogLevel level, std::string_view message);
    };

}
