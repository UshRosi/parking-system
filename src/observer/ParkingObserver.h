#ifndef PARKINGOBSERVER_H
#define PARKINGOBSERVER_H

#include <memory> 

#include "../event/ParkingEvent.h"

class ParkingObserver {
public:
    virtual ~ParkingObserver() = default;

    virtual void onVehicleCountChanged(int vehicleCount, const ParkingEvent& event) = 0;
};

#endif // PARKINGOBSERVER_H