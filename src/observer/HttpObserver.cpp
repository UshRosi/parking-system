#include "HttpObserver.h"


    HttpObserver::HttpObserver(int maxCapacity, std::string& url, int port) : maxCapacity(maxCapacity), port(port), url(url), running(true) {
        workerThread = std::thread(&HttpObserver::worker, this);
    }

    HttpObserver::~HttpObserver() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            running = false;
        }
        queueCond.notify_all();
        if (workerThread.joinable()) workerThread.join();
    }

    void HttpObserver::onVehicleCountChanged(int vehicleCount, const ParkingEvent& event) {
        

        // Convert timestamp to a human-readable format
        std::string timestampStr  = getString(event.timestamp);

        // Description 
        std::string description = createDescription(event); 

        // Create JSON message
        nlohmann::json jsonMessage;        
        
        jsonMessage["occupied"] = vehicleCount;
        jsonMessage["remaining"] = maxCapacity - vehicleCount;
        jsonMessage["description"] = description;
        jsonMessage["timestamp"] = timestampStr;

        // Convert JSON to string
        std::string jsonData = jsonMessage.dump();

        // Add the task to the queue
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            taskQueue.push([this, jsonData]() { sendHttpRequest(jsonData); });
        }
        queueCond.notify_one(); 
    }

    void HttpObserver::worker() {
        while (running) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                queueCond.wait(lock, [this] { return !taskQueue.empty() || !running; });

                if (!running && taskQueue.empty()) break;

                if (!taskQueue.empty()) {
                    task = taskQueue.front();
                    taskQueue.pop();
                }
            }

            if (task) {
                task(); 
            }
        }
    }

    void HttpObserver::sendHttpRequest(const std::string& jsonData) {
        CURL* curl = curl_easy_init();
        if (curl) {
            std::string fullUrl = url + ":" + std::to_string(port); 

            curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

            // Set the Content-Type header
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


            // Perform the request
           curl_easy_perform(curl);
            
            // Clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    }

    std::string HttpObserver::createDescription(const ParkingEvent& event) {
        std::string description = event.isEntry ? "Entry" : "Exit";
        description += " at Gate " + std::to_string(event.gateID);
        return description;
    }

