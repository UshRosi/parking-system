#ifndef EVENT_H
#define EVENT_H

#include <chrono>

struct SensorEvent {
    int gateID;
    int sensorID;
    bool state; 
    uint64_t timestamp;
};

#endif