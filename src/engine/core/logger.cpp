/**
 *
 */

#include "engine/core/logger.h"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>

void Logger::Init(const std::string& filename) {
    m_Filename = filename;
    m_File.open(filename, std::ios::app);
}

void Logger::Log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_Mutex);

    std::string prefix = "TODO";

    std::cout << prefix << message << std::endl;

    if (m_File.is_open()) {
        m_File << prefix << message << std::endl;
    }

    CheckFileSize();
}

void Logger::CheckFileSize() {
    
}

void Logger::CompressLogFile() {
    m_File.close();
    
}
