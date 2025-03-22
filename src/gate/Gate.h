#ifndef GATE_H
#define GATE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"
#include "../utils/Timestamp.h"
#include "../logger/Logger.h"
#include "../state_machine/StateMachine.h"
#include <thread>

class Gate {
public:
    Gate(int gateID, int sensorA, int sensorB);
    void simulate();

private:
    int gateID;
    int sensorA;
    int sensorB;

    EventQueue eventQueue;
    StateMachine stateMachine;
    std::thread simulationThread;
    std::thread stateMachineThread;

    void generateSensorEvents();
};

#endif // GATE_H