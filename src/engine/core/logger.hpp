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
#include <string_view>

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

        Logger() = delete;
        ~Logger() = delete;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
};

template<>
inline static void Log(LogLevel level, const std::format_string<Args...> fmt, Args&&... args) {
    
}