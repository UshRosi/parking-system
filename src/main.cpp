#include "config.h"
#include <iostream>
#include "gate/Gate.h"
#include "event/EventQueue.h"
#include "state_machine/StateMachine.h"
#include "parking/Parking.h"
#include <thread>

int main() {
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
    Gate gate1(1, 0, 1); // Gate 1 with Sensor A (ID 0) and Sensor B (ID 1)
    Gate gate2(2, 0, 1); // Gate 2 with Sensor A (ID 2) and Sensor B (ID 3)


    gate1.simulate();
    gate2.simulate();

    // Wait indefinitely (or implement a shutdown mechanism)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}
