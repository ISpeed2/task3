#include "LoggerFactory.h"
#include <iostream>

// ConsoleLogger Implementation
void ConsoleLogger::log(const std::string& message) {
    std::cout << "Log: " << message << std::endl;
}

// ConsoleLoggerFactory Implementation
Logger* ConsoleLoggerFactory::createLogger() {
    return new ConsoleLogger();
}
