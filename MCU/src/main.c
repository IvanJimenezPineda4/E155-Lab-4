// Ivan Jimenez Pineda
// ijimenezpineda@g.hmc.edu
// September 29, 2025
// main.c contains the code to play fur elise and the super mario bros. theme

// Include header files
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "FLASH.h"
#include "fur_elise.h"
#include "mario.h"

int main(void) {
    // Configure flash to add waitstates to avoid timing errors
    configureFlash();

    // Setup the PLL and switch clock source to the PLL
    configureClock();

    // Initialize GPIOB and timers
    RCC->AHB2ENR |= (1 << 1);   // Enable clock for GPIOB (bit 1)
    RCC->APB2ENR |= (1 << 16);  // TIM15
    RCC->APB2ENR |= (1 << 17);  // TIM16

    // Configure PB6 for TIM16_CH1N 
    pinMode(6, GPIO_ALT);       // PB6
    GPIO->AFRL &= ~(0xF << (6 * 4));
    GPIO->AFRL |= (14 << (6 * 4));

    pinMode(3, GPIO_OUTPUT); // Configure PB3 (LD3) as an output

    // initializePWM
    const uint32_t sysClk = 80000000/80;     // 80MHz system clk / 80 = Timer clk
    initializePWM(TIM16, sysClk, 440, 50);         // Tuning A4 (440Hz)

    // Fur Elise
    int i = 0;
    while (fur_elise_notes[i][1] != 0) {
        int freq_fur = fur_elise_notes[i][0];
        int length_fur = fur_elise_notes[i][1];

        togglePin(3); // Blink LD3 on each note
        
        if (freq_fur == 0) {
            TIM16->CCER &= ~(1 << 2);  // Disable CC1NE
            delay_micros(length_fur);
            TIM16->CCER |= (1 << 2);   // Enable CC1NE
        }
        
        else {
            configurePWM(TIM16, sysClk, freq_fur, 50);
            delay_micros(length_fur);  
        }
        i++;
    }

    // Stop for 1 second
    TIM16->CR1 &= ~1;                 // Stop PWM
    delay_micros(1000000);            // 1 second delay

    initializePWM(TIM16, sysClk, 440, 50);   

    // Mario
    i = 0;
    while (mario_notes[i][1] != 0) {
        int freq_mario = mario_notes[i][0];
        int length_mario = mario_notes[i][1];

        togglePin(3); // Blink LD3 on each note

        if (freq_mario == 0) {
            TIM16->CCER &= ~(1 << 2);  // Disable CC1NE
            delay_micros(1.5 * length_mario);        
            TIM16->CCER |= (1 << 2);   // Enable CC1NE
        }
        
        else {
            configurePWM(TIM16, sysClk, freq_mario, 50);
            delay_micros(1.5 * length_mario); 
        }
        i++;
   
    }
 
    // Turn PWM off at the very end to end the music
    TIM16->CR1 &= ~1;
    while (1);
}