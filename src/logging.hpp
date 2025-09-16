#ifndef LOGGING_HPP
#define LOGGING_HPP

#ifdef USE_LOGGER

#include "logger.hpp"

using namespace CPlusPlusLogging;

#else

#define LOG_ERROR(x)
#define LOG_ALARM(x)
#define LOG_ALWAYS(x)
#define LOG_INFO(x)
#define LOG_BUFFER(x)
#define LOG_TRACE(x)
#define LOG_DEBUG(x)

#endif // USE_LOGGER

inline void InitLogging(int logLevel)
{
#ifdef USE_LOGGER
    switch (logLevel) {
    case 1:
        Logger::getInstance()->enableFileLogging();
        break;

    case 2:
        Logger::getInstance()->enableFileLogging();
        Logger::getInstance()->enaleLog();
        break;

    case 3:
        Logger::getInstance()->enableConsoleLogging();
        break;

    case 4:
        Logger::getInstance()->enableConsoleLogging();
        Logger::getInstance()->enaleLog();
        break;

    default:
        Logger::getInstance()->updateLogType(NO_LOG);
        break;
    }
#endif
}

inline bool HasLogging()
{
#ifdef USE_LOGGER
    return true;
#else
    return false;
#endif
}

#endif // LOGGING_HPP
