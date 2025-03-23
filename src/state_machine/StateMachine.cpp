#include "StateMachine.h"

//#include "utils/Logger.h"
#include <iostream>

StateMachine::StateMachine(EventQueue& eventQueue)
    : eventQueue(eventQueue) {
    // Initialize any other members if needed
}

void StateMachine::processEvents() {
    Parking& parking = Parking::getInstance();
    while (true) {
        
        SensorEvent event = eventQueue.pop();

        std::cout << "New event found! sensor, gate id: "<< event.gateID  << std::endl;

            processEvent(event, parking);
        
    }
}

    void StateMachine::processEvent(const SensorEvent& event, Parking& parking) 
    {

        long long timestampA = 0;

        long long timestampB = 0;          

            std::cout << "New event found, sensor id :  " << event.sensorID << "Current state " << event.state << "Current gate :" << event.gateID << std::endl;

            // Update state machine based on the event
            switch (currentState[event.gateID]) {
            case STATE_IDLE:
                if (event.sensorID == 0 && event.state == 1) {
                    currentState[event.gateID] = STATE_SENSOR_A_ENGAGED;
                    timestampA = event.timestamp;
                }
                else if (event.sensorID == 1 && event.state == 1) {
                    currentState[event.gateID] = STATE_SENSOR_B_ENGAGED;
                    timestampB = event.timestamp;
                }
                break;

            case STATE_SENSOR_A_ENGAGED:
                if (event.sensorID == 1 && event.state == 1) {
                    currentState[event.gateID] = STATE_IDLE;
                    timestampB = event.timestamp;
                    if (timestampA < timestampB) {
                        // Vehicle is entering
                        std::cout << "Car is entering. GATE: "<< event.gateID  <<  std::endl;
                        parking.confirmEntry();
                    }
                }
                break;

            case STATE_SENSOR_B_ENGAGED:
                if (event.sensorID == 0 && event.state == 1) {
                    currentState[event.gateID] = STATE_IDLE;
                    timestampA = event.timestamp;
                    if (timestampB < timestampA) {
                        // Vehicle is exiting
                        std::cout << "Car is exiting GATE: " << event.gateID << std::endl;
                        parking.confirmExit();
                    }
                }
                break;

            
    }

   
}