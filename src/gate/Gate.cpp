#include "Gate.h"
#include <cstdlib>
#include <unistd.h>
#include "../parking/Parking.h"


Gate::Gate(int gateID, int sensorA, int sensorB)
    : gateID(gateID), sensorA(sensorA), sensorB(sensorB), stateMachine(eventQueue) {
}

void Gate::simulate() {
    simulationThread = std::thread(&Gate::generateSensorEvents, this);
    stateMachineThread = std::thread(&StateMachine::processEvents, &stateMachine);
   // stateMachine.processEvents(); 
}

    void Gate::generateSensorEvents() 
    {
        while (true) {
            // Simulate a random event: entry or exit
            bool isEntry = rand() % 2; // 50% chance of entry or exit
              if (isEntry && Parking::getInstance().isFull()) {
                  // Parking lot is full, skip generating entrance event
                  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Parking lot is full.Skipping entrance event for, GATE " << gateID << std::endl;
                  usleep(100000); // Simulate delay before next event
                  continue;
              }

              if (!isEntry && Parking::getInstance().isEmpty()) {
                  // Parking lot is full, skip generating entrance event
                  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Parking lot is empty.Skipping exit event, GATE " << gateID << std::endl;
                  usleep(100000); // Simulate delay before next event
                  continue;
              }

              // Generate sensor events based on direction (entry or exit)
            if (isEntry) {
                std::cout << "################################## Event is created, car is entring, GATE " << gateID << std::endl;
                // Simulate vehicle entering: Sensor A -> Sensor B
                eventQueue.push({ sensorA, 1, getTimestamp() });
                usleep(50000); // Simulate delay between sensors
                eventQueue.push({ sensorB, 1, getTimestamp() });
            }
            else {
                std::cout << "##################################  Event is created, car is exiting, GATE "<< gateID << std::endl;
                // Simulate vehicle exiting: Sensor B -> Sensor A
                eventQueue.push({ sensorB, 1, getTimestamp() });
                usleep(50000); // Simulate delay between sensors
                eventQueue.push({ sensorA, 1, getTimestamp() });
            }

            usleep(100000); // Simulate delay between events
    }
}