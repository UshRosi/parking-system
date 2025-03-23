#ifndef GATE_H
#define GATE_H

#include "../state_machine/StateMachine.h"
#include <thread>
#include <atomic>

class Gate {
public:
    Gate(StateMachine& stateMachine);
    ~Gate();
    void start();
    void stop();

private:

    StateMachine& stateMachine; 
    std::thread processingThread;
    std::atomic<bool> running{ false };

    void processEvents();
};

#endif // GATE_H