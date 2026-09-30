// Ivan Jimenez Pineda
// ijimenezpineda@g.hmc.edu
// September 29, 2025
// FLASH.h sets up the memory mapped register structures to interact with the microcontroller's flash memory

#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

#define __IO volatile

// Base addresses for GPIO ports
#define FLASH_BASE (0x40022000UL) // base address of flash

// map the individual 32-bit flash registers to their offsets (each uint32_t is 4 bytes long)
typedef struct {
  __IO uint32_t ACR;      /*!< FLASH access control register,   Address offset: 0x00 */
  __IO uint32_t KEYR;     /*!< FLASH key register,              Address offset: 0x04 */
  __IO uint32_t OPTKEYR;  /*!< FLASH option key register,       Address offset: 0x08 */
  __IO uint32_t SR;       /*!< FLASH status register,           Address offset: 0x0C */
  __IO uint32_t CR;       /*!< FLASH control register,          Address offset: 0x10 */
  __IO uint32_t OPTCR;    /*!< FLASH option control register ,  Address offset: 0x14 */
  __IO uint32_t OPTCR1;   /*!< FLASH option control register 1, Address offset: 0x18 */ 
} FLASH_TypeDef;

#define FLASH ((FLASH_TypeDef *) FLASH_BASE) 

void configureFlash(void);

#endif