#include "Gate.h"
#include <cstdlib>
#include <unistd.h>
#include "../parking/Parking.h"


Gate::Gate(int gateID, int sensorA, int sensorB)
    : gateID(gateID), sensorA(sensorA), sensorB(sensorB) {
}

void Gate::simulate(EventQueue& eventQueue) {
    while (true) {
        // Simulate a random event: entry or exit
        bool isEntry = rand() % 2; // 50% chance of entry or exit

        if (isEntry && Parking::getInstance().isFull()) {
            // Parking lot is full, skip generating entrance event
            Logger::log("Parking lot is full. Skipping entrance event for Gate " + std::to_string(gateID));
            usleep(100000); // Simulate delay before next event
            continue;
        }

        // Generate sensor events based on direction (entry or exit)
        if (isEntry) {
            // Simulate vehicle entering: Sensor A -> Sensor B
            eventQueue.push({ sensorA, HIGH, getTimestamp() });
            usleep(50000); // Simulate delay between sensors
            eventQueue.push({ sensorB, HIGH, getTimestamp() });
        }
        else {
            // Simulate vehicle exiting: Sensor B -> Sensor A
            eventQueue.push({ sensorB, HIGH, getTimestamp() });
            usleep(50000); // Simulate delay between sensors
            eventQueue.push({ sensorA, HIGH, getTimestamp() });
        }

        usleep(100000); // Simulate delay between events
    }
}