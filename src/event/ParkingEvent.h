#ifndef PARKINGEVENT_H
#define PARKINGEVENT_H

#include <chrono>

struct ParkingEvent {
    int gateID;                    
    long long timestamp;            
    bool isEntry; 
};

#endif // PARKINGEVENT_H