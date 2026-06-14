#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define HERMES_SOF               (0xAAU)
#define HERMES_MAX_PAYLOAD       (32U)

typedef enum
{
    MSG_VEHICLE_COMMAND   = 0x01,
    MSG_VEHICLE_STATUS    = 0x02,
    MSG_HEARTBEAT         = 0x03,
    MSG_FAULT             = 0x04,
    MSG_DIAGNOSTIC        = 0x05
} MessageId_t;

typedef struct
{
    uint8_t sof;
    uint8_t msgId;
    uint8_t length;
    uint8_t payload[HERMES_MAX_PAYLOAD];
    uint16_t crc;
} Packet_t;

#endif