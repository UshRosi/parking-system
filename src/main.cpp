#include "config.h"
#include <iostream>
#include "gate/Gate.h"
#include "event/EventQueue.h"
#include "state_machine/StateMachine.h"
#include "parking/Parking.h"
#include "simulator/Simulator.h"
#include <thread>
#include <atomic>
#include <csignal>
std::atomic<bool> running{ true };

void signalHandler(int signal) {
    running = false;
}

int main() {
    //std::signal(SIGINT, signalHandler);


    Config loader("../appconfig.json");

    if (!loader.loadConfig()) {
        return 1; // Exit if config loading fails
    }

    Configs& config = loader.getConfig();

    // Print the configuration
    std::cout << "Max Capacity: " << config.max_capacity << std::endl;
    std::cout << "Server IP: " << config.server_ip << std::endl;
    std::cout << "Server Port: " << config.server_port << std::endl;

    Parking::initialize(config.max_capacity); 
 

    std::cout << "Correct init Event " << std::endl;

    // Initialize gates
  /*  Gate gate1(1, 0, 1); // Gate 1 with Sensor A (ID 0) and Sensor B (ID 1)
    Gate gate2(2, 0, 1); // Gate 2 with Sensor A (ID 2) and Sensor B (ID 3)


    gate1.simulate();
    gate2.simulate();

    // Wait indefinitely (or implement a shutdown mechanism)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }*/
    EventQueue eventQueue;

    Simulator simulator(eventQueue );

    // Initialize state machines
    StateMachine stateMachine1(eventQueue, simulator.tempVehicleCount, simulator.tempExitCount, simulator.tempCountMutex); // State machine for Gate 1
    //StateMachine stateMachine2(2, eventQueue); // State machine for Gate 2

    // Initialize gates
    Gate gate1(0, stateMachine1); // Gate 1 with its state machine
    Gate gate2(1, stateMachine1); // Gate 2 with its state machine
    // Initialize simulator
    
    

    simulator.start();
    gate1.start();
    gate2.start();

    // Wait for shutdown signal
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Stop simulator, gates, and state machines gracefully
    simulator.stop();
    gate1.stop();
    gate2.stop();

    std::cout << "Shutting down..." << std::endl;

    return 0;
}
