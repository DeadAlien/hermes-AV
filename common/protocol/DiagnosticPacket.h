#ifndef DIAGNOSTIC_PACKET_H
#define DIAGNOSTIC_PACKET_H

#include <stdint.h>

typedef enum
{
    DIAG_READ_VERSION = 1U,
    DIAG_READ_FAULTS  = 2U,
    DIAG_CLEAR_FAULTS = 3U,
    DIAG_ECU_RESET    = 4U,
    DIAG_HEALTH_CHECK = 5U
} DiagnosticService_t;

typedef struct
{
    DiagnosticService_t serviceId;
    uint32_t            parameter;
} DiagnosticPacket_t;

#endif /* DIAGNOSTIC_PACKET_H */