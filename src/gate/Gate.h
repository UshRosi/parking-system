#ifndef GATE_H
#define GATE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"
#include "../utils/Timestamp.h"
#include "../state_machine/StateMachine.h"
#include <thread>
#include <atomic>
class Gate {
public:
    Gate(int gateID, StateMachine& stateMachine);
    void start();
    void stop();

private:
    int gateID;
    StateMachine& stateMachine; // Reference to the gate's state machine
    std::thread processingThread;
    std::atomic<bool> running{ false };

    void processEvents();
};

#endif // GATE_H