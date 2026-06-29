/**
 * @ file logger.hpp
 *
 * @ brief ...
 *
 * @ author Adnan FAIZE <>
 */

#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <cstdint>
#include <format>
#include <atomic>

namespace stfr_core {

    #ifdef STFR_DEBUG
        #define LOG_DEBUG(fmt, ...) stfr::utils::Logger::Log(stfr::utils::DEBUG, fmt, __VA_ARGS__)
    #else
        #define LOG_DEBUG(fmt, ...)
    #endif

    enum class LogLevel : uint8_t {
        INFO,
        WARNING,
        ERROR,
        FATAL,
        DEBUG,
    };

    class Logger {
        public:
            static void Init(const std::string& filename);
            static void Shutdown();
            template<typename... Args>
            static void Log(LogLevel level, const std::format_string<Args...> fmt, Args&&... args) {
                if (!m_Initialized) { return; }

                std::string message = std::format(fmt, std::forward<Args>(args)...);
                _Log(level, message);
            }

        private:
            static void _Log(LogLevel level, const std::string& message);
            static void CompressLogFile();

            static const size_t MAX_FILE_SIZE = 5 * 1024 * 1024; // 5MB limit
            inline static std::mutex m_Mutex;
            inline static std::ofstream m_File;
            inline static std::string m_Filename = "";
            inline static bool m_Initialized = false;
            inline static std::atomic<bool> m_IsCompressing = false;

            Logger() = delete;
            ~Logger() = delete;
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;
    };

}
