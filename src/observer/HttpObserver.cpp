#include "HttpObserver.h"


    HttpObserver::HttpObserver(int maxCapacity, std::string& url, int port) : maxCapacity(maxCapacity), url(url) , port(port), running(true)  {
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

    void HttpObserver::onVehicleCountChanged(int vehicleCount) {
        // Create JSON message
        nlohmann::json jsonMessage;
        jsonMessage["vehicleCount"] = vehicleCount;
        jsonMessage["maxCapacity"] = maxCapacity;

        // Convert JSON to string
        std::string jsonData = jsonMessage.dump();

        // Add the task to the queue
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            taskQueue.push([this, jsonData]() { sendHttpRequest(jsonData); });
        }
        queueCond.notify_one(); // Notify the worker thread
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
                task(); // Execute the task
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
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "HTTP request failed: " << curl_easy_strerror(res) << std::endl;
            }
            // Clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    }

