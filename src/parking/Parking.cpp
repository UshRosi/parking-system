#include "Parking.h"

Parking* Parking::instance = nullptr;

Parking::Parking(int& maxCapacity)
    : vehicleCount(0), maxCapacity(maxCapacity) {
}

// Singleton instance method
Parking& Parking::getInstance() {
    if (!instance) {
        throw std::runtime_error("ParkingLot not initialized. Call initialize() first.");
    }
    return *instance;
}

void Parking::initialize(int& maxCapacity) {
    if (!instance) 
    {
        instance = new Parking(maxCapacity);
    }
    else 
    {
        std::cout << "ParkingLot already initialized." << std::endl; 
    }
}


// Check if a vehicle can enter
bool Parking::canEnter() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    if (vehicleCount + tempVehicleCount < maxCapacity) {
        tempVehicleCount++; // Reserve a spot for the entering vehicle
        return true;
    }
    return false;
}

// Check if a vehicle can exit
bool Parking::canExit() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    if (vehicleCount - tempExitCount > 0) {
        tempExitCount++; // Reserve a spot for the exiting vehicle
        return true;
    }
    return false;
}

// Confirm an entry
void Parking::confirmEntry(const ParkingEvent& event) {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    tempVehicleCount--; // Release the reserved spot
    vehicleCount++;     // Increment the actual vehicle count
    notifyObservers(event);
    std::cout << "Confirmed entry. Vehicle count: " << vehicleCount << std::endl;
}

// Confirm an exit
void Parking::confirmExit(const ParkingEvent& event) {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    tempExitCount--; // Release the reserved spot
    vehicleCount--;  // Decrement the actual vehicle count
    notifyObservers(event);
    std::cout << "Confirmed exit. Vehicle count: " << vehicleCount << std::endl;
}

// Add an observer
void Parking::addObserver(std::shared_ptr<ParkingObserver> observer) {
    observers.push_back(observer);
}

// Notify all observers
void Parking::notifyObservers(const ParkingEvent& event) {
    for (auto& observer : observers) {
        observer->onVehicleCountChanged(vehicleCount, event);
    }
}