#include "pch.h"
#include "DLogger.h"

namespace DDebug
{
    std::string Logger::levelToString(Level level) const {
        switch (level) {
        case Level::INFO: return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR: return "ERROR";
        default: return "UNKNOWN";
        }
    }
    Logger& Logger::getInstance()
    {
        static Logger instance("app.log");
        return instance;
    }
    Logger::Logger(const std::string& filename)
    {
        std::cout << "create loger " << filename << std::endl;
        logFile.open(filename, std::ios_base::app);
        if (!logFile) {
            throw std::runtime_error("Failed to open log file");
        }
    }

    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void Logger::log(Level level, const char* format, ...)
    {
        std::lock_guard<std::mutex> lock(mtx);

        // vsnprintf를 사용하여 가변 인자를 문자열로 변환
        va_list args;
        va_start(args, format);
        std::vector<char> buf(vsnprintf(nullptr, 0, format, args) + 1); // +1 for '\0'
        va_end(args);
            
        va_start(args, format);
        vsnprintf(buf.data(), buf.size(), format, args);
        va_end(args);

        auto logEntry = levelToString(level) + ": " + buf.data();
        std::cout << logEntry << std::endl;

        if (logFile.is_open()) {
            logFile << logEntry << std::endl;
        }

        publish(level, logEntry.c_str());
    }

    void Logger::subscribe(LoggerHandler handler) {
        m_handlers.push_back(handler);
        std::cout << "subscribe log" << std::endl;
    }
    void Logger::clearHandler()
    {
        m_handlers.clear();
    }
    void Logger::publish(Level _level, const char* str)
    {
        for (const auto& handler : m_handlers) {
            handler(_level, str);
        }
    }
}