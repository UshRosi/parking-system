#ifndef EVENT_H
#define EVENT_H

#include <chrono>

struct SensorEvent {
    int gateID;
    int sensorID;
    bool state; // 1: HIGH or 2: LOW 
    long long timestamp; // Timestamp in milliseconds
};

#endif