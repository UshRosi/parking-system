#include "StateMachine.h"

//#include "utils/Logger.h"
#include <iostream>

StateMachine::StateMachine(EventQueue& eventQueue) : eventQueue(eventQueue) {}

void StateMachine::processEvents() {
    SensorState currentState = STATE_IDLE;
    long long timestampA = 0;
    long long timestampB = 0;

    while (true) {
        SensorEvent event = eventQueue.pop();

        // Update state machine based on the event
        switch (currentState) {
        case STATE_IDLE:
            if (event.sensorID == 0 && event.state == HIGH) {
                currentState = STATE_SENSOR_A_ENGAGED;
                timestampA = event.timestamp;
            }
            else if (event.sensorID == 1 && event.state == HIGH) {
                currentState = STATE_SENSOR_B_ENGAGED;
                timestampB = event.timestamp;
            }
            break;

        case STATE_SENSOR_A_ENGAGED:
            if (event.sensorID == 1 && event.state == HIGH) {
                currentState = STATE_BOTH_ENGAGED;
                timestampB = event.timestamp;
                if (timestampA < timestampB) {
                    // Vehicle is entering
                    Parking::getInstance().updateVehicleCount(1);
                }
            }
            break;

        case STATE_SENSOR_B_ENGAGED:
            if (event.sensorID == 0 && event.state == HIGH) {
                currentState = STATE_BOTH_ENGAGED;
                timestampA = event.timestamp;
                if (timestampB < timestampA) {
                    // Vehicle is exiting
                    Parking::getInstance().updateVehicleCount(-1);
                }
            }
            break;

        case STATE_BOTH_ENGAGED:
            if (event.sensorID == 0 && event.state == LOW) {
                currentState = STATE_IDLE;
            }
            else if (event.sensorID == 1 && event.state == LOW) {
                currentState = STATE_IDLE;
            }
            break;
        }
    }
}

void StateMachine::updateVehicleCount(int delta) {
    static int vehicleCount = 0;
    vehicleCount += delta;
    //Logger::log("Vehicle count updated: " + std::to_string(vehicleCount));
    std::cout << "Vehicle count updated: " << std::to_string(vehicleCount) << std::endl;
}