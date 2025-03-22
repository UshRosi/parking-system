#ifndef PARKINGLOT_H
#define PARKINGLOT_H
#include <mutex>
#include <iostream>

class Parking {
public:
    static Parking& getInstance(); // Singleton accessor
    static void initialize(int& maxCapacity);

    void updateVehicleCount(int delta);
    int getVehicleCount() const;
    int getMaxCapacity() const;
    bool isFull() const; 
    bool isEmpty() const; 
    std::mutex& getMutex();
private:
    Parking(int& maxCapacity); 
    ~Parking() = default; // Default destructor

    Parking(const Parking&) = delete; // Disable copy constructor
    Parking& operator=(const Parking&) = delete; // Disable assignment

    mutable std::mutex mutex;

    int vehicleCount; // Stores the vehicle count
    const int maxCapacity; 

    // Static instance pointer
    static Parking* instance;
};

#endif // PARKINGLOT_H
