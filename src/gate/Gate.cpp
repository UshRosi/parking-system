#include "Gate.h"
#include <cstdlib>
#include <unistd.h>
#include "../parking/Parking.h"


Gate::Gate(int gateID, StateMachine& stateMachine)
    : gateID(gateID), stateMachine(stateMachine) {
}

void Gate::start() {
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