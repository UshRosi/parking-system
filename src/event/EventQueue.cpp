#include "EventQueue.h"

void EventQueue::push(const SensorEvent& event) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(event);
    cv.notify_one();
}

SensorEvent EventQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !queue.empty(); });
    SensorEvent event = queue.front();
    queue.pop();
    return event;
}