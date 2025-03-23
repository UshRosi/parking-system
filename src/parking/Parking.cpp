#include "Parking.h"



Parking* Parking::instance = nullptr;

// Singleton instance method
Parking& Parking::getInstance() {
    if (!instance) {
        std::cout << "Errore" << std::endl; 
        throw std::runtime_error("ParkingLot not initialized. Call initialize() first.");
    }
    return *instance;
}

void Parking::initialize(int& maxCapacity) {
    if (!instance) {
        std::cout << "PMax capacity." << maxCapacity << std::endl;

        instance = new Parking(maxCapacity);
    }
    else {
        std::cout << "ParkingLot already initialized." << std::endl; 
    }
}

// Updates vehicle count
void Parking::updateVehicleCount(int delta) {
   
    std::cout << "------------------------BEFORE UPDATE :Current number of car: " << vehicleCount << std::endl;
    std::unique_lock <std::mutex> lock(mutex);

    vehicleCount += delta;
    

    std::cout << "------------------------AFTER UPDATE :Current number of car: " << vehicleCount << std::endl;
  
}

int Parking::getVehicleCount() const 
{
    std::unique_lock <std::mutex> lock(mutex);
    return vehicleCount;
}

int Parking::getMaxCapacity() const {
    return maxCapacity;
}

bool Parking::isFull() const
{
    return getVehicleCount() == maxCapacity;
}

bool Parking::isEmpty() const
{
    return getVehicleCount() <= 0;
}

Parking::Parking(int& maxCapacity)
    : vehicleCount(0), maxCapacity(maxCapacity) {
}
std::mutex& Parking::getMutex() {
    return mutex;
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
void Parking::confirmEntry() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    tempVehicleCount--; // Release the reserved spot
    vehicleCount++;     // Increment the actual vehicle count
    std::cout << "Confirmed entry. Vehicle count: " << vehicleCount << std::endl;
}

// Confirm an exit
void Parking::confirmExit() {
    std::unique_lock<std::mutex> lock(tempCountMutex);
    tempExitCount--; // Release the reserved spot
    vehicleCount--;  // Decrement the actual vehicle count
    std::cout << "Confirmed exit. Vehicle count: " << vehicleCount << std::endl;
}