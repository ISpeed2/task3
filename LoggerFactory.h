#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include <string>

// Forward declaration for the Logger interface
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& message) = 0;
};

// ConsoleLogger Implementation
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override;
};

// LoggerFactory Interface (Factory Method Pattern)
class LoggerFactory {
public:
    virtual ~LoggerFactory() = default;
    virtual Logger* createLogger() = 0; // Factory method
};

// Concrete LoggerFactory for creating ConsoleLoggers
class ConsoleLoggerFactory : public LoggerFactory {
public:
    Logger* createLogger() override;
};

#endif
