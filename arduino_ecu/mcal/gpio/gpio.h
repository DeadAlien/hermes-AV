#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum {
    PortB = 0,
    PortC,
    PortD
} PortName_t;

typedef enum {
    Pin0 = 0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
} PinName_t;

typedef enum {
    Input = 0,
    Output
} PinDirection_t;

typedef enum {
    Low = 0,
    High
} PinState_t;

typedef enum {
    GPIO_OK = 0,
    GPIO_ERROR_INVALID_PORT,
    GPIO_ERROR_INVALID_PIN,
    GPIO_ERROR_INVALID_DIRECTION,
    GPIO_ERROR_INVALID_STATE
}

GPIO_Status_t GPIO_Init(PortName_t port, PinName_t pin, PinDirection_t direction);
GPIO_Status_t GPIO_Set(PortName_t port, PinName_t pin);
GPIO_Status_t GPIO_Clear(PortName_t port, PinName_t pin);
GPIO_Status_t GPIO_Toggle(PortName_t port, PinName_t pin);
GPIO_Status_t GPIO_Read(PortName_t port, PinName_t pin, PinState_t* state);

#endif /* GPIO_H */