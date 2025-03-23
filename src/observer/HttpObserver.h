#ifndef HTTPOBSERVER_H
#define HTTPOBSERVER_H

#include "ParkingObserver.h" // Include the base observer interface
#include "../event/ParkingEvent.h" // Include the base observer interface
#include <nlohmann/json.hpp>     // For JSON serialization
#include <curl/curl.h>       // For HTTP requests
#include <thread>            // For background thread
#include <queue>             // For task queue
#include <mutex>             // For thread-safe access
#include <condition_variable> // For thread synchronization
#include <functional>         // For std::function
#include <memory>             // For std::shared_ptr
#include <iostream>           // For logging
#include <string>

class HttpObserver : public ParkingObserver {
public:
    // Constructor and Destructor
    HttpObserver(int maxCapacity, std::string& url, int port);
    ~HttpObserver();

    // Override the onVehicleCountChanged method
    void onVehicleCountChanged(int vehicleCount,const ParkingEvent& event ) override;

private:

    int maxCapacity; 
    int port; 

    std::string& url; 

    // Background worker thread function
    void worker();

    // Helper function to send HTTP requests
    void sendHttpRequest(const std::string& jsonData);

    // Background thread for processing tasks
    std::thread workerThread;

    // Task queue for storing HTTP requests
    std::queue<std::function<void()>> taskQueue;

    // Mutex for thread-safe access to the task queue
    std::mutex queueMutex;

    // Condition variable to notify the worker thread
    std::condition_variable queueCond;

    // Flag to control the worker thread
    bool running;
};

#endif // HTTPOBSERVER_H