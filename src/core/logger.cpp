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

#include "logger.hpp"

namespace stfr::core {

    void Logger::Init(const std::string& filename) {
        m_Filename = filename;
        m_File.open(filename, std::ios::app);
    }

    void Logger::Shutdown() {
        std::lock_guard<std::mutex> lock(m_Mutex);

        if (m_File.is_open()) {
            m_File.flush();
            m_File.close();
        }
    }

    void Logger::DisableLogs() {
        m_Disabled = true;
    }

    template<typename... Args>
    void Logger::Log(LogLevel level, const std::format_string<Args...> fmt, Args&&... args) {
        if (m_Disabled) { return; }
        if (!m_Initialized) { Init("default.log"); }

        std::string message = std::format(fmt, std::forward<Args>(args)...);
        _Log(level, message);
    }

    void Logger::_Log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(m_Mutex);

        std::string datetime = "";

        std::string prefix = "TODO";

        std::cout << prefix << message << std::endl; // TODO : Add datetime

        if (m_File.is_open()) {
            m_File << prefix << message << std::endl;
        }

        CheckFileSize();
    }

    void Logger::CheckFileSize() {
        if (std::filesystem::exists(m_Filename) && std::filesystem::file_size(m_Filename) > MAX_FILE_SIZE) {
            CompressLogFile();
        }
    }

    void Logger::CompressLogFile() {
        m_File.close();

        // TODO : Compress the file

        std::string archiveName = m_Filename + "." + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".log";
        std::filesystem::rename(m_Filename, archiveName);

        m_File.open(m_Filename, std::ios::app);
    }

}
