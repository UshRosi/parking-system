#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"

class StateMachine {
public:
    StateMachine(EventQueue& eventQueue);
    void processEvents();

    enum SensorState {
        STATE_IDLE,
        STATE_SENSOR_A_ENGAGED,
        STATE_SENSOR_B_ENGAGED,
        STATE_BOTH_ENGAGED
    };

private:
    EventQueue& eventQueue;
};

#endif // STATE_MACHINE_H