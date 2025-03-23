#include "StateMachine.h"

StateMachine::StateMachine(EventQueue& eventQueue)
    : eventQueue(eventQueue) {
}

void StateMachine::processEvents()
{
    Parking& parking = Parking::getInstance();

    while (true) {
        
        SensorEvent event = eventQueue.pop();

        processEvent(event, parking);
    }
}

    void StateMachine::processEvent(const SensorEvent& event, Parking& parking) 
    {
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

   
    void StateMachine::handleParkingEvent(const SensorEvent& event, Parking& parking, bool isEntry) 
    {
        ParkingEvent parkingEvent{ event.gateID, event.timestamp, isEntry };

        if (isEntry) {
            parking.confirmEntry(parkingEvent);
        }
        else {
            parking.confirmExit(parkingEvent);
        }
    }