#include "config.h"
#include <iostream>
#include "gate/Gate.h"
#include "event/EventQueue.h"
#include "state_machine/StateMachine.h"
#include "parking/Parking.h"
#include "simulator/Simulator.h"
#include "observer/HttpObserver.h"
#include <thread>
#include <csignal>

std::atomic<bool> running{ true };


int main() {

    Config loader("../appconfig.json");

    if (!loader.loadConfig()) {
        return 1; 
    }

    Configs& config = loader.getConfig();


    Parking::initialize(config.max_capacity); 

    auto httpObserver = std::make_shared<HttpObserver>(config.max_capacity, config.server_ip, config.server_port);

    Parking::getInstance().addObserver(httpObserver);


    EventQueue eventQueue;

    Simulator simulator(eventQueue );

    
    StateMachine stateMachine(eventQueue); 


    std::array<std::unique_ptr<Gate>, NUM_GATES> gates;

    //  Initialize each Gate object
    for (int i = 0; i < NUM_GATES; ++i) {
        gates[i] = std::make_unique<Gate>(stateMachine);
    }

    //  Start simulator and all gates
    simulator.start();
    for (auto& gate : gates) {
        gate->start();
    }

    
    // Wait for shutdown signal
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Stopping simulator and gates..." << std::endl;
    simulator.stop();
    for (auto& gate : gates) {
        gate->stop();
    }

    std::cout << "Shutting down..." << std::endl;

    return 0;
}
