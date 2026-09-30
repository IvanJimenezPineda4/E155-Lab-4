// Ivan Jimenez Pineda
// ijimenezpineda@g.hmc.edu
// September 29, 2026
// FLASH.c modifies the microcontroller's flash access control register to ensure memory reads at high clock speed

#include "FLASH.h"

void configureFlash() {
    FLASH->ACR |= (0b100); // Set the flash memory to use 4 waitstates
    FLASH->ACR |= (1 << 8); // Set bit 8 of FLASH_ACR register (prefetch enable PRFTEN) to turn on the ART
}