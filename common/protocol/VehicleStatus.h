#ifndef VEHICLE_STATUS_H
#define VEHICLE_STATUS_H

#include <stdint.h>

typedef struct
{
    int16_t actualSpeed;
    int16_t steeringPosition;

    uint16_t batteryVoltage_mV;

    uint8_t systemHealthy;

    uint16_t activeFault;

} VehicleStatus_t;

#endif