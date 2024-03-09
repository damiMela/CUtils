#pragma once

#include <string>
#include <sstream>
namespace cutils
{

    class ILogger
    {
    public:
        typedef enum LogLevel
        {
            LOG_TRACE = 0,
            LOG_DEBUG,
            LOG_INFO,
            LOG_WARNING,
            LOG_ERROR,
            LOG_FATAL
        } LogLevel;

    private:
    public:
        virtual ~ILogger() {}

        virtual void Log(const std::string &message, const std::string &module, const std::string &method, int line, LogLevel level) = 0;
    };
} // namespace cutils
