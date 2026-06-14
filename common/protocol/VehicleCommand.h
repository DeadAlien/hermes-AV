#ifndef VEHICLE_COMMAND_H
#define VEHICLE_COMMAND_H

#include <stdint.h>

typedef enum
{
    MODE_INIT = 0U,
    MODE_IDLE,
    MODE_MANUAL,
    MODE_AUTONOMOUS,
    MODE_FAULT
} VehicleMode_t;

typedef struct
{
    int16_t       targetSpeed;
    int16_t       steeringAngle;
    VehicleMode_t mode;
    uint8_t       emergencyStop;
    uint8_t       reserved;
} VehicleCommand_t;

#endif /* VEHICLE_COMMAND_H */