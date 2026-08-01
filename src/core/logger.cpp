#include <csignal>

#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "logger.hpp"

namespace stfr_core {

    struct LogMessage {
        LogLevel level;
        std::string message;
    };

    struct LoggerData {
        std::mutex queueMutex;
        std::vector<LogMessage> messageQueue;
        std::condition_variable_any cv;
        std::jthread workerThread;
        bool isRunning = false;

        std::ofstream fileStream;
        std::string logDir = "logs";
        size_t currentFileSize = 0;
        const size_t MAX_FILE_SIZE = 5 * 1024 * 1024; // 5 MB
    };

    static LoggerData* s_data = nullptr;

    static const char* GetLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE   : return "[TRACE  ]";
            case LogLevel::DEBUG   : return "[DEBUG  ]";
            case LogLevel::INFO    : return "[INFO   ]";
            case LogLevel::WARNING : return "[WARNING]";
            case LogLevel::ERROR   : return "[ERROR  ]";
            case LogLevel::FATAL   : return "[FATAL  ]";
            default                : return "[UNKNOWN]";
        }
    }

    static void SignalHandler(int signal) {
        const char* sigName = "UNKNOWN";

        switch (signal) {
            case SIGSEGV: sigName = "SIGSEGV (Segmentation Fault)";      break;
            case SIGABRT: sigName = "SIGABRT (Aborted)";                 break;
            case SIGINT : sigName = "SIGINT (Interrupt / Ctrl+C)";       break;
            case SIGTERM: sigName = "SIGTERM (Terminated)";              break;
            case SIGILL : sigName = "SIGILL (Illegal Instruction)";      break;
            case SIGFPE : sigName = "SIGFPE (Floating Point Exception)"; break;
        }

        if (s_data && s_data->fileStream.is_open()) {
            std::string msg = std::format("[FATAL] Program exited with signal {}\n", sigName);
            std::cerr << msg;
            s_data->fileStream << msg;
            s_data->fileStream.flush();
        }

        std::signal(signal, SIG_DFL);
        std::raise(signal);
    }

    void Logger::Initialize() {
        if (s_data) { return; }
        s_data = new LoggerData();

        std::signal(SIGSEGV, SignalHandler);
        std::signal(SIGABRT, SignalHandler);
        std::signal(SIGINT , SignalHandler);
        std::signal(SIGTERM, SignalHandler);
        std::signal(SIGILL , SignalHandler);
        std::signal(SIGFPE , SignalHandler);


    }

    void Logger::Shutdown() {
        if (!s_data) { return; }

        s_data->workerThread.request_stop();
        s_data->cv.notify_one();
        s_data->workerThread.join();

        if (s_data->fileStream.is_open()) {
            s_data->fileStream.close();
        }

        delete s_data;
        s_data = nullptr;
    }

    void Logger::Log(LogLevel level, std::string_view message) {
        if (!s_data || !s_data->isRunning) { return; }

        std::lock_guard<std::mutex> lock(s_data->queueMutex);
        s_data->messageQueue.push_back({level, std::string(message)});

        s_data->cv.notify_one();
    }

    void Logger::LogCallback(LogLevel level, const char *message) {
        Log(level, message);
    }

}
