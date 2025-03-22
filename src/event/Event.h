#ifndef EVENT_H
#define EVENT_H

#include "../sensor/Sensor.h"
#include <chrono>

struct SensorEvent {
    int sensorID;
    bool state; // 1: HIGH or 2: LOW 
    long long timestamp; // Timestamp in milliseconds
};

#endif