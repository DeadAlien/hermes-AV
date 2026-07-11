#include "pwm.h"
#include "pwm_private.h"
#include <stddef.h>

/* Internal Driver State Tracking */
typedef struct {
    uint32_t frequency;
    uint8_t  duty_cycle;
    uint8_t  is_running;
    uint8_t  prescaler_mask;
} PWM_Channel_State_t;

static PWM_Channel_State_t g_channels[PWM_CHANNEL_MAX];

/* Internal Helper: Select optimal Prescaler and determine TOP value */
static PWM_Status_t CalculateTimerSettings(uint8_t channel, uint32_t freq_hz, uint32_t *out_top, uint8_t *out_mask) {
    uint32_t top = 0;
    uint8_t mask = 0;

    if (channel == PWM_CH0 || channel == PWM_CH1) {
        /* Timer 0 (8-bit): Prescaler choices 1, 8, 64, 256, 1024 */
        uint16_t prescalers[] = {1, 8, 64, 256, 1024};
        uint8_t masks[] = {0x01, 0x02, 0x03, 0x04, 0x05};
        
        for (int i = 0; i < 5; i++) {
            top = (F_CPU / (prescalers[i] * freq_hz)) - 1;
            if (top <= 255) {
                mask = masks[i];
                break;
            }
        }
        if (top > 255 || top == 0) return PWM_ERR_INVALID_FREQ;
    } 
    else if (channel == PWM_CH2 || channel == PWM_CH3) {
        /* Timer 1 (16-bit Fast PWM Mode 14 using ICR1 as TOP) */
        uint16_t prescalers[] = {1, 8, 64, 256, 1024};
        uint8_t masks[] = {0x01, 0x02, 0x03, 0x04, 0x05};
        
        for (int i = 0; i < 5; i++) {
            top = (F_CPU / (prescalers[i] * freq_hz)) - 1;
            if (top <= 65535) {
                mask = masks[i];
                break;
            }
        }
        if (top > 65535 || top == 0) return PWM_ERR_INVALID_FREQ;
    } 
    else {
        /* Timer 2 (8-bit): Different prescaler selection rules mapping */
        uint16_t prescalers[] = {1, 8, 32, 64, 128, 256, 1024};
        uint8_t masks[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
        
        for (int i = 0; i < 7; i++) {
            top = (F_CPU / (prescalers[i] * freq_hz)) - 1;
            if (top <= 255) {
                mask = masks[i];
                break;
            }
        }
        if (top > 255 || top == 0) return PWM_ERR_INVALID_FREQ;
    }

    *out_top = top;
    *out_mask = mask;
    return PWM_OK;
}

PWM_Status_t PWM_Init(uint8_t channel, uint32_t freq_hz, uint8_t duty) {
    /* Parameter Validation */
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    if (duty > 100) return PWM_ERR_INVALID_DUTY;

    uint32_t top = 0;
    uint8_t clk_mask = 0;
    PWM_Status_t status = CalculateTimerSettings(channel, freq_hz, &top, &clk_mask);
    if (status != PWM_OK) return status;

    /* Mode Configuration (Fast PWM) & Channel Mapping */
    switch (channel) {
        case PWM_CH0:
            DDRD_REG |= (1 << PD6_OC0A);
            TCCR0A_REG |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // Fast PWM, non-inverting
            break;
        case PWM_CH1:
            DDRD_REG |= (1 << PD5_OC0B);
            TCCR0A_REG |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
            break;
        case PWM_CH2:
            DDRB_REG |= (1 << PB1_OC1A);
            TCCR1A_REG |= (1 << COM1A1) | (1 << WGM11);
            TCCR1B_REG |= (1 << WGM13) | (1 << WGM12); // Mode 14: Fast PWM with TOP = ICR1
            ICR1_REG = (uint16_t)top;
            break;
        case PWM_CH3:
            DDRB_REG |= (1 << PB2_OC1B);
            TCCR1A_REG |= (1 << COM1B1) | (1 << WGM11);
            TCCR1B_REG |= (1 << WGM13) | (1 << WGM12);
            ICR1_REG = (uint16_t)top;
            break;
        case PWM_CH4:
            DDRB_REG |= (1 << PB3_OC2A);
            TCCR2A_REG |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20); // Fast PWM
            break;
        case PWM_CH5:
            DDRD_REG |= (1 << PD3_OC2B);
            TCCR2A_REG |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
            break;
    }

    g_channels[channel].frequency = freq_hz;
    g_channels[channel].prescaler_mask = clk_mask;
    g_channels[channel].is_running = 0;

    /* Duty Cycle Update */
    return PWM_SetDutyCycle(channel, duty);
}

PWM_Status_t PWM_Start(uint8_t channel) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    
    // Apply Clock source selections to activate the timers
    if (channel == PWM_CH0 || channel == PWM_CH1) {
        TCCR0B_REG |= g_channels[channel].prescaler_mask;
    } else if (channel == PWM_CH2 || channel == PWM_CH3) {
        TCCR1B_REG |= g_channels[channel].prescaler_mask;
    } else {
        TCCR2B_REG |= g_channels[channel].prescaler_mask;
    }
    
    g_channels[channel].is_running = 1;
    return PWM_OK;
}

PWM_Status_t PWM_Stop(uint8_t channel) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;

    // Zero out the clock selection bits (CSn2:0) to pause execution
    if (channel == PWM_CH0 || channel == PWM_CH1) {
        TCCR0B_REG &= ~0x07;
    } else if (channel == PWM_CH2 || channel == PWM_CH3) {
        TCCR1B_REG &= ~0x07;
    } else {
        TCCR2B_REG &= ~0x07;
    }

    g_channels[channel].is_running = 0;
    return PWM_OK;
}

PWM_Status_t PWM_SetDutyCycle(uint8_t channel, uint8_t duty) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    if (duty > 100) return PWM_ERR_INVALID_DUTY;

    uint32_t top = 0;
    uint8_t dummy_mask = 0;
    CalculateTimerSettings(channel, g_channels[channel].frequency, &top, &dummy_mask);

    /* Formula Reference from Diagram: Duty% = (OCRnx / (TOP + 1)) * 100 */
    uint32_t ocr_val = ((uint32_t)duty * (top + 1)) / 100;
    if (ocr_val > 0) ocr_val -= 1; // Align boundaries

    switch (channel) {
        case PWM_CH0: OCR0A_REG = (uint8_t)ocr_val; break;
        case PWM_CH1: OCR0B_REG = (uint8_t)ocr_val; break;
        case PWM_CH2: OCR1A_REG = (uint16_t)ocr_val; break;
        case PWM_CH3: OCR1B_REG = (uint16_t)ocr_val; break;
        case PWM_CH4: OCR2A_REG = (uint8_t)ocr_val; break;
        case PWM_CH5: OCR2B_REG = (uint8_t)ocr_val; break;
    }

    g_channels[channel].duty_cycle = duty;
    return PWM_OK;
}

PWM_Status_t PWM_SetFrequency(uint8_t channel, uint32_t freq_hz) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    
    uint32_t top = 0;
    uint8_t clk_mask = 0;
    PWM_Status_t status = CalculateTimerSettings(channel, freq_hz, &top, &clk_mask);
    if (status != PWM_OK) return status;

    // Cache run state, temporarily isolate running state clock
    uint8_t running = g_channels[channel].is_running;
    if (running) PWM_Stop(channel);

    g_channels[channel].frequency = freq_hz;
    g_channels[channel].prescaler_mask = clk_mask;

    // Reconfigure TOP values
    if (channel == PWM_CH2 || channel == PWM_CH3) {
        ICR1_REG = (uint16_t)top;
    }

    // Recalculate OCR configurations for new scale
    PWM_SetDutyCycle(channel, g_channels[channel].duty_cycle);

    if (running) PWM_Start(channel);
    return PWM_OK;
}

PWM_Status_t PWM_GetDutyCycle(uint8_t channel, uint8_t *duty) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    if (duty == NULL) return PWM_ERR_INVALID_PARAM;
    
    *duty = g_channels[channel].duty_cycle;
    return PWM_OK;
}

PWM_Status_t PWM_GetFrequency(uint8_t channel, uint32_t *freq_hz) {
    if (channel >= PWM_CHANNEL_MAX) return PWM_ERR_INVALID_CHANNEL;
    if (freq_hz == NULL) return PWM_ERR_INVALID_PARAM;

    *freq_hz = g_channels[channel].frequency;
    return PWM_OK;
}