#include "Logger.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>

#include <iostream>
#include <cstdio> 



namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;



Logger::Logger(const std::string& logFilePath) : logFilePath(logFilePath) {
    InitLogging();
}

void Logger::InitLogging() {

    
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    logging::add_file_log(
        keywords::file_name = "logs/%Y-%m-%d_%H-%M-%S_%5N.txt",
        keywords::rotation_size = 1 * 1024 * 1024,
        keywords::format = "[%LineID%][%TimeStamp%][%Severity%]%Message%",
        logging::keywords::auto_flush = true
    );

    logging::add_common_attributes();
    }



void Logger::LogMessage(const std::string& message,const std::string& name, LogLevel level) {


    switch (level) {
        case TRACE:
            BOOST_LOG_TRIVIAL(trace) << "[" << name << "] : " <<message;
            break;
        case DEBUG:
            BOOST_LOG_TRIVIAL(debug) << "[" << name << "] : " <<message;
            break;
        case INFO:
            BOOST_LOG_TRIVIAL(info) <<  "[" << name << "] : "<< message;
            break;
        case WARNING:
            BOOST_LOG_TRIVIAL(warning) << "[" << name << "] : "<< message;
            break;
        case ERROR:
            BOOST_LOG_TRIVIAL(error) << "[" << name << "] : "<< message;
            break;
        default:
            BOOST_LOG_TRIVIAL(info) << "[" << name << "] : " <<message;
    }

    //logging::core::get()->flush();
}
