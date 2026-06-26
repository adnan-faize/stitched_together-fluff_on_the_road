/**
 *
 */

#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <cstdint>

enum class LogLevel : uint8_t {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

class Logger {
    public:
        static void Init(const std::string& filename);
        static void Log(LogLevel level, const std::string& message);
        static void Shutdown();

    private:
        static void CheckFileSize();
        static void CompressLogFile();

        static std::ofstream m_File;
        static std::mutex m_Mutex;
        static std::string m_Filename;
        static const size_t MAX_FILE_SIZE = 5 * 1024 * 1024; // 5MB limit

        Logger() = delete;
        ~Logger() = delete;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
};
