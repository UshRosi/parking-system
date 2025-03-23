#include "StateMachine.h"

StateMachine::StateMachine(EventQueue& eventQueue)
    : eventQueue(eventQueue) {
    // Initialize any other members if needed
}

void StateMachine::processEvents()
{
    Parking& parking = Parking::getInstance();

    while (true) {
        
        SensorEvent event = eventQueue.pop();

        std::cout << "New event found! sensor, gate id: "<< event.gateID  << std::endl;

        processEvent(event, parking);
    }
}

    void StateMachine::processEvent(const SensorEvent& event, Parking& parking) 
    {
        std::cout << "Processing event - Sensor ID: " << event.sensorID
              << ", State: " << event.state 
              << ", Gate ID: " << event.gateID << std::endl;

        switch (currentState[event.gateID])
        {
        case STATE_IDLE:
            if (event.state == 1) {
                currentState[event.gateID] = (event.sensorID == 0) ? STATE_SENSOR_A_ENGAGED : STATE_SENSOR_B_ENGAGED;
            }
            break;

        case STATE_SENSOR_A_ENGAGED:
            if (event.sensorID == 1 && event.state == 1) {
                currentState[event.gateID] = STATE_IDLE;
                handleParkingEvent(event, parking, true);  // Vehicle entering
            }
            break;

        case STATE_SENSOR_B_ENGAGED:
            if (event.sensorID == 0 && event.state == 1) {
                currentState[event.gateID] = STATE_IDLE;
                handleParkingEvent(event, parking, false);  // Vehicle exiting
            }
            break;
        }
    }

   
    void StateMachine::handleParkingEvent(const SensorEvent& event, Parking& parking, bool isEntry) {
        std::cout << (isEntry ? "Car entering" : "Car exiting")
            << " at Gate: " << event.gateID << std::endl;

        ParkingEvent parkingEvent{ event.gateID, event.timestamp, isEntry };

        if (isEntry) {
            parking.confirmEntry(parkingEvent);
        }
        else {
            parking.confirmExit(parkingEvent);
        }
    }