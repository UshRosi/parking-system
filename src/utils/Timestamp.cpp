#include "Timestamp.h"

long long getTimestamp() {
    using namespace std::chrono;
    // Get the current time point
    auto now = system_clock::now();
    // Convert to milliseconds since epoch
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count();
    return ms;
}