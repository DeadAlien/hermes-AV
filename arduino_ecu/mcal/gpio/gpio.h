#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    PortB = 0,
    PortC,
    PortD
} GPIO_Port_t;

typedef enum {
    Pin0 = 0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
} GPIO_Pin_t;

typedef enum {
    Input = 0,
    Output
} GPIO_Direction_t;

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
} GPIO_Status_t;

GPIO_Status_t GPIO_Init(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Direction_t direction);
GPIO_Status_t GPIO_Set(GPIO_Port_t port, GPIO_Pin_t pin);
GPIO_Status_t GPIO_Clear(GPIO_Port_t port, GPIO_Pin_t pin);
GPIO_Status_t GPIO_Toggle(GPIO_Port_t port, GPIO_Pin_t pin);
GPIO_Status_t GPIO_Read(GPIO_Port_t port, GPIO_Pin_t pin, PinState_t* state);

#endif /* GPIO_H */