#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"
#include "../event/ParkingEvent.h"
#include "../parking/Parking.h"
#include "../config.h"
#include <iostream>

class StateMachine {
public:
    StateMachine(EventQueue& eventQueue);

    void processEvents(); 

    enum SensorState {
        STATE_IDLE,
        STATE_SENSOR_A_ENGAGED,
        STATE_SENSOR_B_ENGAGED
    };

private:
    EventQueue& eventQueue;
    void processEvent(const SensorEvent& event,Parking& parking);
    void handleParkingEvent(const SensorEvent& event, Parking& parking, bool isEntry);
    SensorState currentState[NUM_GATES]{ STATE_IDLE, STATE_IDLE,STATE_IDLE, STATE_IDLE };
};

#endif // STATE_MACHINE_H