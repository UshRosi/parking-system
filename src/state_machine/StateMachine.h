#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "../event/EventQueue.h"
#include "../event/Event.h"
#include "../parking/Parking.h"
#include <mutex>
#include <atomic>

class StateMachine {
public:
    StateMachine(EventQueue& eventQueue, std::atomic<int>& tempVehicleCount, std::atomic<int>& tempExitCount, std::mutex& tempCountMutex);

    void processEvents(); 

    enum SensorState {
        STATE_IDLE,
        STATE_SENSOR_A_ENGAGED,
        STATE_SENSOR_B_ENGAGED
    };

private:
    EventQueue& eventQueue;
    void processEvent(const SensorEvent& event,Parking& parking);
    SensorState currentState[2]{ STATE_IDLE, STATE_IDLE };
    std::atomic<int>& tempVehicleCount;
    std::atomic<int>& tempExitCount;
    std::mutex& tempCountMutex;
};

#endif // STATE_MACHINE_H