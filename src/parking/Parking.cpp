#include "ParkingLot.h"

// Singleton instance method
Parking& Parking::getInstance() {
    static Parking instance; // Local static ensures single instance
    return instance;
}

Parking::Parking(int maxCapacity) : vehicleCount(0), maxCapacity(maxCapacity) {}

// Updates vehicle count
void Parking::updateVehicleCount(int delta) {
    std::lock_guard<std::mutex> lock(mutex);
    vehicleCount += delta;
}

int Parking::getVehicleCount() {
    std::lock_guard<std::mutex> lock(mutex);
    return vehicleCount;
}

int Parking::getMaxCapacity() const {
    return maxCapacity;
}

bool Parking::isFull() const
{
    return vehicleCount == maxCapacity; 
}