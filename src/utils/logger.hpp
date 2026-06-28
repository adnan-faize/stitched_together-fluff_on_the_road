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

namespace stfr::utils {

    #ifdef STFR_DEBUG
        #define LOG_DEBUG(fmt, ...) stfr::utils::Logger::Log(stfr::utils::LogLevel::DEBUG, fmt, __VA_ARGS__)
    #else
        #define LOG_DEBUG(fmt, ...)
    #endif

    enum class LogLevel : uint8_t {
        INFO    = 0,
        WARNING = 1,
        ERROR   = 2,
        FATAL   = 3,
        DEBUG   = 4,
    };

    class Logger {
        public:
            static void Init(const std::string& filename);
            static void Shutdown();
            static void DisableLogs();
            template<typename... Args>
            static void Log(LogLevel level, const std::format_string<Args...> fmt, Args&&... args);

        private:
            static void _Log(LogLevel level, const std::string& message);
            static void CheckFileSize();
            static void CompressLogFile();

            static const size_t MAX_FILE_SIZE = 5 * 1024 * 1024; // 5MB limit
            static std::ofstream m_File;
            static std::mutex m_Mutex;
            static std::string m_Filename;
            static bool m_Initialized;
            static bool m_Disabled;

            Logger() = delete;
            ~Logger() = delete;
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;
    };

}
