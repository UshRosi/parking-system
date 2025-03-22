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
