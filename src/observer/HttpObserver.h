#ifndef HTTPOBSERVER_H
#define HTTPOBSERVER_H

#include "ParkingObserver.h" 
#include "../event/ParkingEvent.h" 
#include "../utils/Timestamp.h" 
#include <nlohmann/json.hpp>     
#include <curl/curl.h>       
#include <thread>            
#include <queue>             
#include <mutex>            
#include <condition_variable> 
#include <functional>         
#include <memory>            
#include <iostream>           
#include <string>

class HttpObserver : public ParkingObserver {
public:
    
    HttpObserver(int maxCapacity, std::string& url, int port);

    ~HttpObserver();

    void onVehicleCountChanged(int vehicleCount,const ParkingEvent& event ) override;

private:

    int maxCapacity;

    int port; 

    std::string& url; 
    
    void worker();
   
    void sendHttpRequest(const std::string& jsonData);

    std::string createDescription(const ParkingEvent& event); 

    std::thread workerThread;

    std::queue<std::function<void()>> taskQueue;

    std::mutex queueMutex;

    std::condition_variable queueCond;

    bool running;
};

#endif // HTTPOBSERVER_H