#include "StateMachine.h"

//#include "utils/Logger.h"
#include <iostream>

StateMachine::StateMachine(EventQueue& eventQueue) : eventQueue(eventQueue) {}
void StateMachine::processEvents() {
    Parking& parking = Parking::getInstance();
    while (true) {
        SensorEvent event = eventQueue.pop();
        processEvent(event, parking);
    }
}

    void StateMachine::processEvent(const SensorEvent& event, Parking& parking) 
    {

        long long timestampA = 0;

        long long timestampB = 0;

             

            std::cout << "New event found, sensor id :  " << event.sensorID << "Current state " << event.state << std::endl;

            // Update state machine based on the event
            switch (currentState) {
            case STATE_IDLE:
                if (event.sensorID == 0 && event.state == 1) {
                    currentState = STATE_SENSOR_A_ENGAGED;
                    timestampA = event.timestamp;
                }
                else if (event.sensorID == 1 && event.state == 1) {
                    currentState = STATE_SENSOR_B_ENGAGED;
                    timestampB = event.timestamp;
                }
                break;

            case STATE_SENSOR_A_ENGAGED:
                if (event.sensorID == 1 && event.state == 1) {
                    currentState = STATE_IDLE;
                    timestampB = event.timestamp;
                    if (timestampA < timestampB) {
                        // Vehicle is entering
                        std::cout << "Car is entering " << std::endl;
                        parking.updateVehicleCount(1);
                    }
                }
                break;

            case STATE_SENSOR_B_ENGAGED:
                if (event.sensorID == 0 && event.state == 1) {
                    currentState = STATE_IDLE;
                    timestampA = event.timestamp;
                    if (timestampB < timestampA) {
                        // Vehicle is exiting
                        std::cout << "Car is exiting " << std::endl;
                        parking.updateVehicleCount(-1);
                    }
                }
                break;

            
    }

   
}