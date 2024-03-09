#pragma once

#include "ILogger.hpp"
#include <cstdarg>
#include <cstdio>

#define TRACE(fmt, ...) Log(fmt, __func__, __LINE__, LOG_TRACE, ##__VA_ARGS__)
#define DEBUG(fmt, ...) Log(fmt, __func__, __LINE__, LOG_DEBUG, ##__VA_ARGS__)
#define INFO(fmt, ...) Log(fmt, __func__, __LINE__, LOG_INFO, ##__VA_ARGS__)
#define WARNING(fmt, ...) Log(fmt, __func__, __LINE__, LOG_WARNING, ##__VA_ARGS__)
#define ERROR(fmt, ...) Log(fmt, __func__, __LINE__, LOG_ERROR, ##__VA_ARGS__)
#define FATAL(fmt, ...) Log(fmt, __FUNC__, __LINE__, LOG_FATAL, ##__VA_ARGS__)

typedef enum LogLevel_t
{
    LOG_TRACE = 0,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogLevel_t;

namespace cutils
{
    class ClassLogger
    {
    private:
        ILogger *logger;
        std::string module;

    private:
        void _Log(const std::string &message, const char *method,
                  int line, ILogger::LogLevel level)
        {
            logger->Log(message, module, method, line, level);
        }

    public:
        ClassLogger(ILogger *logger, const char *module) : logger(logger), module(module){};

        void Log(const char *format, const char *functionName, int lineNumber, LogLevel_t level, ...)
        {
            va_list args;
            va_start(args, level);
            char buffer[1024];
            vsnprintf(buffer, sizeof(buffer), format, args);
            va_end(args);
            _Log(buffer, functionName, lineNumber, (cutils::ILogger::LogLevel)level);
        }
    };
};