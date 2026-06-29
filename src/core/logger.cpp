/**
 * @ file logger.hpp
 *
 * @ brief ...
 *
 * @ author Adnan FAIZE <>
 */

#include <iostream>
#include <filesystem>
#include <chrono>
#include <format>

#include "logger.hpp"

namespace stfr_core {

    void Logger::Init(const std::string& filename = "") {
        if (!filename.empty()) {
            m_Filename = filename;
            m_File.open(filename, std::ios::app);
        }

        m_Initialized = true;
    }

    void Logger::Shutdown() {
        if (!m_Initialized) { return; }

        std::lock_guard<std::mutex> lock(m_Mutex);

        if (m_Filename.empty()) { return; }
        if (m_File.is_open()) {
            m_File.flush();
            m_File.close();
        }
    }

    void Logger::_Log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(m_Mutex);

        std::string timestamp = std::format("{:%FT%T%Ez}", std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()});

        std::string prefix = "UNKNOWN";

        switch (level) {
            case LogLevel::INFO:    prefix = "INFO";
            case LogLevel::WARNING: prefix = "WARNING";
            case LogLevel::ERROR:   prefix = "ERROR";
            case LogLevel::FATAL:   prefix = "FATAL";
            case LogLevel::DEBUG:   prefix = "DEBUG";
        }

        std::cout << std::format("{} [{}] {}", timestamp, prefix, message) << std::endl;

        if (m_Filename.empty()) { return; }
        if (m_File.is_open()) {
            m_File << std::format("{} [{}] {}", timestamp, prefix, message) << std::endl;
        }

        CompressLogFile();
    }

    void Logger::CompressLogFile() {
        if (!std::filesystem::exists(m_Filename) || std::filesystem::file_size(m_Filename) <= MAX_FILE_SIZE) {
            return;
        }

        m_File.close();

        // TODO : Compress the file

        std::string archiveName = m_Filename + "." + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".log";
        std::filesystem::rename(m_Filename, archiveName);

        m_File.open(m_Filename, std::ios::app);
    }

}
