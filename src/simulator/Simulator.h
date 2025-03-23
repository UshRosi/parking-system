#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "../event/EventQueue.h"
#include "../parking/Parking.h"
#include "../config.h"
#include <atomic>
#include <thread>

class Simulator {
public:

    Simulator(EventQueue& eventQueue);
    void start();
    void stop();

private:

    EventQueue& eventQueue; // Reference to the shared event queue
    std::thread simulationThread;
    std::atomic<bool> running{ false };
    void generateSensorEvents();
};

#endif // SIMULATOR_H