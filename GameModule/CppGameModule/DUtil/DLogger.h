#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <functional>
#include <cstdarg>
#include <vector>
#include <cassert>
#include <cstdio>
#include <list>

namespace DDebug
{
    class Logger {
    public:
        enum class Level {
            INFO,
            WARNING,
            ERROR
        };
        using LoggerHandler = std::function<void(Level, const char*)>;

    private:
        std::mutex mtx;

        std::ofstream logFile;

        std::string levelToString(Level level) const;

    public:
        static Logger& getInstance();

        Logger(const std::string& filename);

        ~Logger();

        void log(Level level, const char* format, ...);

        void subscribe(LoggerHandler handler);
        void clearHandler();

        void publish(Level _level, const char* str);
    private:
        std::list<LoggerHandler> m_handlers;
    };

}
