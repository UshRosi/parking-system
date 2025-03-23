#ifndef PARKINGEVENT_H
#define PARKINGEVENT_H

#include <chrono>

struct ParkingEvent {
    int gateID;                     // Gate ID (e.g., 1, 2)
    long long timestamp;            // Timestamp in milliseconds  
    bool isEntry; 
};

#endif // PARKINGEVENT_H