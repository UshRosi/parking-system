#include "Simulator.h"
#include "../utils/Timestamp.h"
#include <cstdlib>
#include <unistd.h>

Simulator::Simulator(EventQueue& eventQueue)
    : eventQueue(eventQueue) {}

void Simulator::start() {
    running = true;
    simulationThread = std::thread(&Simulator::generateSensorEvents, this);
}

void Simulator::stop() {
    running = false;
    if (simulationThread.joinable()) simulationThread.join();
}


void Simulator::generateSensorEvents() {
    Parking& parking = Parking::getInstance(); 
    while (running) {
        // Simulate sensor events for all gates
        for (int gateID = 0; gateID <= 3; ++gateID) { // Example: 2 gates

            // Simulate a random event: entry or exit
            bool isEntry = rand() % 2; // 50% chance of entry or exit
            if (isEntry && !parking.canEnter()) {
                // Parking lot is full, skip generating entrance event
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Parking lot is full.Skipping entrance event for, GATE " << gateID << std::endl;
                usleep(100000); // Simulate delay before next event
                continue;
            }

            if (!isEntry && !parking.canExit()) {
                // Parking lot is full, skip generating entrance event
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Parking lot is empty.Skipping exit event, GATE " << gateID << std::endl;
                usleep(100000); // Simulate delay before next event
                continue;
            }

            // Generate sensor events based on direction (entry or exit)
            if (isEntry) {
                std::cout << "################################## Event is created, car is entring, GATE " << gateID << std::endl;
                // Simulate vehicle entering: Sensor A -> Sensor B
                eventQueue.push({ gateID, 0, 1, getTimestamp() });
                usleep(50000); // Simulate delay between sensors
                eventQueue.push({ gateID, 1, 1, getTimestamp() });
            }
            else {
                std::cout << "##################################  Event is created, car is exiting, GATE " << gateID << std::endl;
                // Simulate vehicle exiting: Sensor B -> Sensor A
                eventQueue.push({ gateID, 1, 1, getTimestamp() });
                usleep(50000); // Simulate delay between sensors
                eventQueue.push({ gateID, 0, 1, getTimestamp() });
            }

            //usleep(100000); // Simulate delay between events
        }

        usleep(100000); // Simulate delay between events
    }
}