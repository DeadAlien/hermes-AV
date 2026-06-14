#ifndef DIAGNOSTIC_PACKET_H
#define DIAGNOSTIC_PACKET_H

#include <stdint.h>

typedef enum
{
    DIAG_READ_VERSION = 1,
    DIAG_READ_FAULTS,
    DIAG_CLEAR_FAULTS,
    DIAG_ECU_RESET,
    DIAG_HEALTH_CHECK
} DiagnosticService_t;

typedef struct
{
    DiagnosticService_t serviceId;
    uint32_t parameter;
} DiagnosticPacket_t;

#endif