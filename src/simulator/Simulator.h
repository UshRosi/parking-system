#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../event/EventQueue.h"
#include <thread>
#include "../parking/Parking.h"
#include <atomic>
class Simulator {
public:
    Simulator(EventQueue& eventQueue);
    void start();
    void stop();

    std::atomic<int> tempVehicleCount{ 0 };
    std::atomic<int> tempExitCount{ 0 };
    std::mutex tempCountMutex;

private:
    EventQueue& eventQueue; // Reference to the shared event queue
    std::thread simulationThread;
    std::atomic<bool> running{ false };
    bool canEnter(int gateID); 
    bool canExit(int gateID); 
    void generateSensorEvents();
};

#endif // SIMULATOR_H