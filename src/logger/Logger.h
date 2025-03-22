#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    static Logger& getInstance(); // Singleton accessor

    void log(const std::string& message);
    void logError(const std::string& message);
    void logWarning(const std::string& message);

private:
    Logger(); // Private constructor
    ~Logger();

    Logger(const Logger&) = delete; // Disable copy constructor
    Logger& operator=(const Logger&) = delete; // Disable assignment operator

    std::ofstream logFile; // File stream for logging
    std::mutex logMutex;   // Ensures thread safety
};

#endif // LOGGER_H
