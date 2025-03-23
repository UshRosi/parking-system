#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include "../observer/ParkingObserver.h"
#include "../event/ParkingEvent.h"

class Parking {
public:
    static Parking& getInstance(); // Singleton accessor
    static void initialize(int& maxCapacity);

    bool canEnter();
    bool canExit();
    void confirmEntry(const ParkingEvent& event);
    void confirmExit(const ParkingEvent& event);

    void addObserver(std::shared_ptr<ParkingObserver> observer);
private:

    Parking(int& maxCapacity); 
    ~Parking() = default; // Default destructor

    Parking(const Parking&) = delete; // Disable copy constructor
    Parking& operator=(const Parking&) = delete; // Disable assignment

    mutable std::mutex mutex;

    int vehicleCount; // Stores the vehicle count
    const int maxCapacity; 

    
    std::atomic<int> tempVehicleCount{ 0 }; // Temporary count for vehicles entering
    std::atomic<int> tempExitCount{ 0 };   // Temporary count for vehicles exiting
    std::mutex tempCountMutex;

    std::vector<std::shared_ptr<ParkingObserver>> observers;
    void notifyObservers(const ParkingEvent& event);

    // Static instance pointer
    static Parking* instance;
};

#endif // PARKINGLOT_H
