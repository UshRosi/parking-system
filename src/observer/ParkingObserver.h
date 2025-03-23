#ifndef PARKINGOBSERVER_H
#define PARKINGOBSERVER_H

#include <memory> // For std::shared_ptr

#include "../event/ParkingEvent.h"

class ParkingObserver {
public:
    virtual ~ParkingObserver() = default;

    // Pure virtual method to be implemented by concrete observers
    virtual void onVehicleCountChanged(int vehicleCount, const ParkingEvent& event) = 0;
};

#endif // PARKINGOBSERVER_H