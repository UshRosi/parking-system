#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "Event.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class EventQueue {
public:
    void push(const SensorEvent& event);
    SensorEvent pop();

private:
    std::queue<SensorEvent> queue;
    std::mutex mutex;
    std::condition_variable cv;
};

#endif 