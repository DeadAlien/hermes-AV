#ifndef PWM_H
#define PWM_H

#include <stdint.h>

/* ERROR HANDLING: All APIs return PWM_Status_t */
typedef enum {
    PWM_OK = 0,
    PWM_ERR_INVALID_CHANNEL,
    PWM_ERR_INVALID_FREQ,
    PWM_ERR_INVALID_DUTY,
    PWM_ERR_TIMER_BUSY,
    PWM_ERR_INVALID_STATE,
    PWM_ERR_HW_FAILURE
} PWM_Status_t;

/* SUPPORTED CHANNEL MAPPING */
typedef enum {
    PWM_CH0 = 0, /* Timer0 - OC0A (PD6) */
    PWM_CH1,     /* Timer0 - OC0B (PD5) */
    PWM_CH2,     /* Timer1 - OC1A (PB1) */
    PWM_CH3,     /* Timer1 - OC1B (PB2) */
    PWM_CH4,     /* Timer2 - OC2A (PB3) */
    PWM_CH5,     /* Timer2 - OC2B (PD3) */
    PWM_CHANNEL_MAX
} PWM_Channel_t;

/* API FUNCTIONS (Public Interface) */
PWM_Status_t PWM_Init(uint8_t channel, uint32_t freq_hz, uint8_t duty);
PWM_Status_t PWM_Start(uint8_t channel);
PWM_Status_t PWM_Stop(uint8_t channel);
PWM_Status_t PWM_SetDutyCycle(uint8_t channel, uint8_t duty);
PWM_Status_t PWM_SetFrequency(uint8_t channel, uint32_t freq_hz);
PWM_Status_t PWM_GetDutyCycle(uint8_t channel, uint8_t *duty);
PWM_Status_t PWM_GetFrequency(uint8_t channel, uint32_t *freq_hz);

#endif /* PWM_H */