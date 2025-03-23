#include "Parking.h"

Parking* Parking::instance = nullptr;

Parking::Parking(int& maxCapacity)
    : vehicleCount(0), maxCapacity(maxCapacity) {
}

Parking::~Parking() {
    delete instance;
    instance = nullptr;
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
bool Parking::greenLight() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    if (vehicleCount + tempVehicleCount < maxCapacity) {
        tempVehicleCount++; 
        return true;
    }
    return false;
}

// Check if a vehicle can exit
bool Parking::canExit() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    if (vehicleCount - tempExitCount > 0) {
        tempExitCount++; 
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
    std::cout << GREEN_TEXT
        << "  [" << getString(event.timestamp) << "] Vehicle entered from gate " << event.gateID << ". Vehicles inside: " << vehicleCount << "\n"
        << "----------------------------------------------------\n"
        << RESET_TEXT;
}

// Confirm an exit
void Parking::confirmExit(const ParkingEvent& event) {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    tempExitCount--; // Release the reserved spot
    vehicleCount--;  // Decrement the actual vehicle count
    notifyObservers(event);
    std::cout << YELLOW_TEXT
        << "  [" << getString(event.timestamp) << "] Vehicle exited from gate " << event.gateID << ". Vehicles inside: " << vehicleCount << "\n"
        << "----------------------------------------------------\n"
        << RESET_TEXT;
}


void Parking::addObserver(std::shared_ptr<ParkingObserver> observer) {
    observers.push_back(observer);
}

void Parking::notifyObservers(const ParkingEvent& event) {
    for (auto& observer : observers) {
        observer->onVehicleCountChanged(vehicleCount, event);
    }
}