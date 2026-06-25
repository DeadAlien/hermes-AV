#include "gpio.h"
#include <avr/io.h>

#define Is_valid_pin(pin)   (((pin) >= Pin0) && ((pin) <= Pin7))

GPIO_Status_t GPIO_Init(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Direction_t direction)
{
    if(Is_valid_pin(pin) == false)
    {
        return GPIO_ERROR_INVALID_PIN;
    }


    switch(port)
    {
        case PortB:
        if(direction == Output)
        {
            DDRB |= (1 << pin);
        }
        else
        {
            DDRB &= ~(1 << pin);
        }
        break;
        case PortC:
        if(direction == Output)
        {
            DDRC |= (1 << pin);
        }
        else
        {
            DDRB &= ~(1 << pin);
        }
        break;
        case PortD:
        if(direction == Output)
        {
            DDRD |= (1 << pin);
        }
        else
        {
            DDRD &= ~(1 << pin);
        }
        break;
        default:
            return GPIO_ERROR_INVALID_PORT;
    }

    return GPIO_OK;
}

GPIO_Status_t GPIO_Set(GPIO_Port_t port, GPIO_Pin_t pin)
{
    if(Is_valid_pin(pin) == false)
    {
        return GPIO_ERROR_INVALID_PIN;
    }

    switch(port)
    {
        case PortB: pin |= (1 << pin); break;
        case PortC: pin |= (1 << pin); break;
        case PortD: pin |= (1 << pin); break;
        default: return GPIO_ERROR_INVALID_PORT;
    }
    return GPIO_OK;
}

GPIO_Status_t GPIO_Clear(GPIO_Port_t port, GPIO_Pin_t pin)
{
    if(Is_valid_pin(pin) == false)
    {
        return GPIO_ERROR_INVALID_PIN;
    }

    switch(port)
    {
        case PortB: pin &= ~(1 << pin); break;
        case PortC: pin &= ~(1 << pin); break;
        case PortD: pin &= ~(1 << pin); break;
        default: return GPIO_ERROR_INVALID_PORT;
    }
    return GPIO_OK;
}

GPIO_Status_t GPIO_Toggle(GPIO_Port_t port, GPIO_Pin_t pin)
{
    if(Is_valid_pin(pin) == false)
    {
        return GPIO_ERROR_INVALID_PIN;
    }

    switch(port)
    {
        case PortB: pin ^= (1 << pin); break;
        case PortC: pin ^= (1 << pin); break;
        case PortD: pin ^= (1 << pin); break;
        default: return GPIO_ERROR_INVALID_PORT;
    }
    return GPIO_OK;
}

GPIO_Status_t GPIO_Read(GPIO_Port_t port, GPIO_Pin_t pin, PinState_t* state)
{
    switch(port)
    {
        case PortB: *state = (PINB >> pin & 1) ? High : Low; break;
        case PortC: *state = (PINC >> pin & 1) ? High : Low; break;
        case PortD: *state = (PIND >> pin & 1) ? High : Low; break;
        default: return GPIO_ERROR_INVALID_PORT;
    }
    return GPIO_OK;
}