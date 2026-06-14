#ifndef PROTOCOL_VERSION_H
#define PROTOCOL_VERSION_H

#include <stdint.h>

#define HERMES_PROTOCOL_MAJOR   (1U)
#define HERMES_PROTOCOL_MINOR   (0U)
#define HERMES_PROTOCOL_PATCH   (0U)

#define HERMES_PROTOCOL_VERSION ((uint32_t)((HERMES_PROTOCOL_MAJOR << 16U) | \
                                            (HERMES_PROTOCOL_MINOR << 8U)  | \
                                            (HERMES_PROTOCOL_PATCH)))

#endif /* PROTOCOL_VERSION_H */