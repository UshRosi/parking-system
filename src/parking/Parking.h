#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#define GREEN_TEXT "\033[1;32m" 
#define YELLOW_TEXT "\033[1;33m" 
#define RESET_TEXT "\033[0m"


#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include "../observer/ParkingObserver.h"
#include "../event/ParkingEvent.h"
#include "../utils/Timestamp.h"


class Parking {
public:
    static Parking& getInstance(); 

    ~Parking();

    static void initialize(int& maxCapacity);

    bool greenLight();

    bool canExit();

    void confirmEntry(const ParkingEvent& event);

    void confirmExit(const ParkingEvent& event);

    void addObserver(std::shared_ptr<ParkingObserver> observer);

private:

    Parking(int& maxCapacity); 

    Parking(const Parking&) = delete; 

    Parking& operator=(const Parking&) = delete; 

    mutable std::mutex mutex;

    int vehicleCount; 

    const int maxCapacity; 
    
    std::atomic<int> tempVehicleCount{ 0 }; 

    std::atomic<int> tempExitCount{ 0 };  

    std::mutex tempCountMutex;

    std::vector<std::shared_ptr<ParkingObserver>> observers;

    void notifyObservers(const ParkingEvent& event);

    static Parking* instance;
};

#endif // PARKINGLOT_H
