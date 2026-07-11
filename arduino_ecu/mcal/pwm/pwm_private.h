#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H

#include <stdint.h>

#define F_CPU 16000000UL

/* TIMER0 Registers (8-bit) */
#define TCCR0A_REG    (*(volatile uint8_t*)(0x44))
#define TCCR0B_REG    (*(volatile uint8_t*)(0x45))
#define TCNT0_REG     (*(volatile uint8_t*)(0x46))
#define OCR0A_REG     (*(volatile uint8_t*)(0x47))
#define OCR0B_REG     (*(volatile uint8_t*)(0x48))

/* TIMER1 Registers (16-bit) */
#define TCCR1A_REG    (*(volatile uint8_t*)(0x80))
#define TCCR1B_REG    (*(volatile uint8_t*)(0x81))
#define TCNT1_REG     (*(volatile uint16_t*)(0x84))
#define ICR1_REG      (*(volatile uint16_t*)(0x86))
#define OCR1A_REG     (*(volatile uint16_t*)(0x88))
#define OCR1B_REG     (*(volatile uint16_t*)(0x8A))

/* TIMER2 Registers (8-bit) */
#define TCCR2A_REG    (*(volatile uint8_t*)(0xB0))
#define TCCR2B_REG    (*(volatile uint8_t*)(0xB1))
#define TCNT2_REG     (*(volatile uint8_t*)(0xB2))
#define OCR2A_REG     (*(volatile uint8_t*)(0xB3))
#define OCR2B_REG     (*(volatile uint8_t*)(0xB4))

/* GPIO Direction Registers for Pins Mapping */
#define DDRD_REG      (*(volatile uint8_t*)(0x2A))
#define DDRB_REG      (*(volatile uint8_t*)(0x24))

/* Pin Allocations */
#define PD6_OC0A      (6)
#define PD5_OC0B      (5)
#define PB1_OC1A      (1)
#define PB2_OC1B      (2)
#define PB3_OC2A      (3)
#define PD3_OC2B      (3)

/* Bit Definitions */
#define COM0A1   7
#define COM0B1   5
#define WGM01    1
#define WGM00    0
#define COM1A1   7
#define COM1B1   5
#define WGM11    1
#define WGM13    4
#define WGM12    3
#define COM2A1   7
#define COM2B1   5
#define WGM21    1
#define WGM20    0

#endif /* PWM_PRIVATE_H */