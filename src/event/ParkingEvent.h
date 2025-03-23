#ifndef PARKINGEVENT_H
#define PARKINGEVENT_H


struct ParkingEvent {
    int gateID;                    
    uint64_t timestamp;
    bool isEntry; 
};

#endif // PARKINGEVENT_H