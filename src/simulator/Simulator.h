#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RED_TEXT "\033[1;31m" 
#define RESET_TEXT "\033[0m" 

#include "../event/EventQueue.h"
#include "../parking/Parking.h"
#include "../utils/Timestamp.h"
#include "../config.h"
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

class Simulator {
public:

    explicit Simulator(EventQueue& eventQueue);
    ~Simulator();
    void start();
    void stop();

private:

    EventQueue& eventQueue; 
    std::thread simulationThread;
    std::atomic<bool> running{ false };
    std::condition_variable cv;
    std::mutex cvMutex;


    void generateSensorEvents();
};

#endif // SIMULATOR_H