#include "Logger.h"

// Initialize singleton instance
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

// Constructor opens the log file
Logger::Logger() {
    logFile.open("app.log", std::ios::app); // Append mode
    if (!logFile) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
    }
}

// Destructor closes the log file
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Generic log function
void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[INFO] " << message << std::endl;
    if (logFile) logFile << "[INFO] " << message << std::endl;
}

// Error log function
void Logger::logError(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cerr << "[ERROR] " << message << std::endl;
    if (logFile) logFile << "[ERROR] " << message << std::endl;
}

// Warning log function
void Logger::logWarning(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[WARNING] " << message << std::endl;
    if (logFile) logFile << "[WARNING] " << message << std::endl;
}
