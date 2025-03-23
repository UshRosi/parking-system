#include "Simulator.h"
#include <cstdlib>
#include <unistd.h>

Simulator::Simulator(EventQueue& eventQueue)
    : eventQueue(eventQueue) {}

Simulator::~Simulator() {
    stop();
}

void Simulator::start() {
    running = true;
    simulationThread = std::thread(&Simulator::generateSensorEvents, this);
}

void Simulator::stop() {
    {
        std::lock_guard<std::mutex> lock(cvMutex);
        running = false;
    }
    cv.notify_one(); 
    if (simulationThread.joinable()) simulationThread.join();
}


void Simulator::generateSensorEvents() {
    Parking& parking = Parking::getInstance();
    std::unique_lock<std::mutex> lock(cvMutex, std::defer_lock);

    while (true) {
        lock.lock();
        cv.wait_for(lock, std::chrono::milliseconds(100), [this] { return !running; });
        if (!running) break;
        lock.unlock();

        for (int gateID = 0; gateID < NUM_GATES; ++gateID) {
            bool isEntry = rand() % 2;

            if (isEntry && !parking.greenLight()) {
                std::cout << RED_TEXT
                    << "######################################################\n"
                    << "#                       RED LIGHT                    #\n"
                    << "######################################################\n"
                    << RESET_TEXT << std::endl;
                continue;
            }

            if (!isEntry && !parking.canExit()) {
                continue;
            }

            uint64_t timestamp = getTimestamp();
            // Generate entry event
            if (isEntry) {
                eventQueue.push({ gateID, 0, 1, timestamp });
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                eventQueue.push({ gateID, 1, 1, getTimestamp() });
            }
            // Generate exit event
            else {
                eventQueue.push({ gateID, 1, 1, timestamp });
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                eventQueue.push({ gateID, 0, 1, getTimestamp() });
            }
        }
    }
}