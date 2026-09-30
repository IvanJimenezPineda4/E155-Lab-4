// Ivan Jimenez Pineda
// ijimenezpineda@g.hmc.edu
// September 29, 2025
// TIM.c contains timer functions

#include "TIM.h"

int clk_freq = 80000000 / (3000 + 1);

// TIM16 is used for outputting audio
// PWM: Period (ARR) and Pulse Width (CCR1)
// int freq is the desired output PWM frequency (Hz)
// int dutyCycle is the desired PWM Duty Cycle (%)

void initializePWM(TIM_TypeDef *TIMx, uint32_t clk, int freq, int dutyCycle) {
    if (freq <= 0) return;
    uint32_t T = clk / (uint32_t)freq;  // T is the timer period

    if (T < 2) {
    T = 2;                              // Avoid dividing by zero
    }

    TIMx->PSC = 79;                     // Set prescaler (PSC) such that 1,000,000 Hz = 80,000,000 Hz / (PSC + 1), PSC = 79
    TIMx->ARR = T - 1;

    // Duty Cycle
    uint32_t ccr = (T * (uint32_t)dutyCycle) / 100;  

    if (ccr >= T) {
    ccr = T - 1;    
    }

    TIMx->CCR1 = ccr;             
    TIMx->CCMR1 &= ~(0x7 << 4);   // PWM mode 1 
    TIMx->CCMR1 |=  (0x6 << 4);   // PWM mode 1
    TIMx->CCMR1 |=  (1 << 3);     // OC1PE = 1
    // enable complementary output (bit 2)
    TIMx->CCER &= ~(1 << 0);      
    TIMx->CCER |=  (1 << 2);      // Enable CC1NE (Channel 1 Complementary Output)
    TIMx->CR1 |= (1 << 7);        // Enable ARR preload
    TIMx->BDTR |= (1 << 15);      // Enable BDTR.MOE for TIM15 and TIM16
    TIMx->EGR |= 1;               // Generate update for preload
    TIMx->CR1 |= 1;               // Start counter
}

// Set PWM freq and duty cycle for the following notes
void configurePWM(TIM_TypeDef *TIMx, uint32_t clk, int freq, int dutyCycle) {
    if (freq <= 0) return;      

    uint32_t T = clk / (uint32_t)freq;  // One full timer period
    if (T < 2) {
    T = 2;                              // Avoid dividing by zero
    }

    uint32_t ccr = (T * (uint32_t)dutyCycle) / 100;     // Capture Compare Register 1 (CCR1) is LOW until end of period T
    if (ccr >= T) {
    ccr = T - 1;      // Ensure Duty Cycle is less than 100%
    }

    TIMx->ARR  = T - 1;            
    TIMx->CCR1 = ccr;
    TIMx->EGR |= 1;             
}

// Use TIM15 to generate microsecond timer
void delay_micros(uint32_t us) {

    TIM15->CNT = 0;             // Reset counter

    // 1MHz is a period of 1 microsecond

    TIM15->PSC = 3000;           

    TIM15->CR1 &= ~1;
    TIM15->ARR = (clk_freq / 1000) * us;            // Set ARR

    TIM15->CR1 |= 1;            // Set counter
    TIM15->EGR |= 1;            
    TIM15->CNT = 0;
    TIM15->SR &= ~1;            
    while (!(TIM15->SR & 1));   // Wait until UIF is set before clearing flag and stopping counter
}