#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;


enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string& logFilePath);
    void LogMessage(const std::string& message,const std::string& name, LogLevel level);

private:
    void InitLogging();

    std::string logFilePath;
    
};

#endif // LOGGER_H
