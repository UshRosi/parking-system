#ifndef GATE_H
#define GATE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"
#include "../utils/Timestamp.h"
#include <thread>

class Gate {
public:
    Gate(int gateID, int sensorA, int sensorB);
    void simulate(EventQueue& eventQueue);

private:
    int gateID;
    int sensorA;
    int sensorB;
};

#endif // GATE_H