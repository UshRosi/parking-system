#include "Timestamp.h"

uint64_t  getTimestamp() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
std::string getString(uint64_t timestamp) {
    std::time_t time = timestamp / 1000;
    std::tm* tm = std::localtime(&time);  

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%A, %B %d, %Y %H:%M:%S", tm);
    return std::string(buffer);
}

