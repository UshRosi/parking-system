#include "config.h"
#include <iostream>
#include "gate/Gate.h"
#include "event/EventQueue.h"
#include "state_machine/StateMachine.h"
#include <thread>

int main() {
    Config loader("../appconfig.json");

    if (!loader.loadConfig()) {
        return 1; // Exit if config loading fails
    }

    Configs config = loader.getConfig();

    // Print the configuration
    std::cout << "Max Capacity: " << config.max_capacity << std::endl;
    std::cout << "Server IP: " << config.server_ip << std::endl;
    std::cout << "Server Port: " << config.server_port << std::endl;

    EventQueue eventQueue;
    StateMachine stateMachine(eventQueue);

    // Initialize gates
    Gate gate1(1, 0, 1); // Gate 1 with Sensor A (ID 0) and Sensor B (ID 1)
    Gate gate2(2, 2, 3); // Gate 2 with Sensor A (ID 2) and Sensor B (ID 3)

    // Start threads for gate simulation and event processing
    std::thread gateThread1(&Gate::simulate, &gate1, std::ref(eventQueue));
    std::thread gateThread2(&Gate::simulate, &gate2, std::ref(eventQueue));
    std::thread eventThread(&StateMachine::processEvents, &stateMachine);

    // Wait for threads to finish (never in this case)
    gateThread1.join();
    gateThread2.join();
    eventThread.join();

    return 0;
}
