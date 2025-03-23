#include "Gate.h"


Gate::Gate(StateMachine& stateMachine)
    :  stateMachine(stateMachine) {
}

Gate::~Gate() {
    stop(); 
}

void Gate::start() {
    if (running) return;
    running = true;
    processingThread = std::thread(&Gate::processEvents, this);
}

void Gate::stop() {
    running = false;
    if (processingThread.joinable()) processingThread.join();
}

void Gate::processEvents() {
    while (running) {
        // Process events using the state machine
        stateMachine.processEvents();
    }
}