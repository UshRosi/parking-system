#ifndef PARKINGLOT_H
#define PARKINGLOT_H

class ParkingLot {
public:
    static ParkingLot& getInstance(); // Singleton accessor

    void updateVehicleCount(int delta);
    int getVehicleCount() const;
    int getMaxCapacity() const;
    bool isFull() const; 

private:
    ParkingLot(); // Private constructor
    ~ParkingLot() = default; // Default destructor

    ParkingLot(const ParkingLot&) = delete; // Disable copy constructor
    ParkingLot& operator=(const ParkingLot&) = delete; // Disable assignment

    int vehicleCount; // Stores the vehicle count
    std::mutex mutex;
    const int maxCapacity; 
};

#endif // PARKINGLOT_H
