#ifndef PARKINGOBSERVER_H
#define PARKINGOBSERVER_H

#include <memory> // For std::shared_ptr

// Observer Interface
class ParkingObserver {
public:
    virtual ~ParkingObserver() = default;

    // Pure virtual method to be implemented by concrete observers
    virtual void onVehicleCountChanged(int vehicleCount) = 0;
};

#endif // PARKINGOBSERVER_H