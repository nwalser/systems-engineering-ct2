/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 Lab GPIO
 * -- Description : Configure and use GPIO port B as output and 
 * --               GPIO port A is input.
 * --               Lab version without additional hardware 
 * --               except for three wires.
 * --
 * -- $Id: main.c ostt $
 * ------------------------------------------------------------------------- */

#include <stdint.h>
#include <reg_stm32f4xx.h>

#include "reg_ctboard.h"
#include "gpiocheck.h"

/* user macros */

#define MASK_3_BITS  0x0007

void reset_GPIO(void);


/* ----------------------------------------------------------------------------
 * Main
 * ------------------------------------------------------------------------- */

int main(void)
{
    uint16_t data_gpio_in;              // use to read input values from gpio
    uint8_t data_dip_switch;            // use to read values from dip switches
		uint8_t state_gpio;

    GPIOA_ENABLE();                     // peripheral clk enable
    GPIOB_ENABLE();                     // peripheral clk enable
		
		//Reset the GPIOA and GPIOB to it's base value
		reset_GPIO();


    /// STUDENTS: To be programmed

		// A----------
		GPIOA->MODER &= 	~((uint32_t)0b00111111);
		GPIOA->MODER |= 	 ((uint32_t)0b00000000);
		
		GPIOA->PUPDR &= 	~((uint32_t)0b00111111);
		GPIOA->PUPDR |= 	 ((uint32_t)0b00000110);
		//
		//// B-----------
		GPIOB->MODER &= 	~((uint32_t)0b00111111);
		GPIOB->MODER |= 	 ((uint32_t)0b00010101);
		
		GPIOB->OTYPER &= 	~((uint32_t)0b00000111);
		GPIOB->OTYPER |= 	 ((uint32_t)0b00000110);
		
		GPIOB->PUPDR &= 	~((uint32_t)0b00111111);
		GPIOB->PUPDR |= 	 ((uint32_t)0b00010000);
		
		GPIOB->OSPEEDR &= ~((uint32_t)0b00111111);
		GPIOB->OSPEEDR |=	 ((uint32_t)0b00110100);


    /// END: To be programmed
		
    while (1) {
			/* implement tasks 6.1 to 6.2 below */
			/// STUDENTS: To be programmed

			// write
			uint8_t switches = CT_DIPSW->BYTE.S15_8; // read sw15..8
			CT_LED->BYTE.LED15_8 = switches; // write led 15..8
			GPIOB->ODR = (uint32_t)switches; // write ORD B

			// read
			uint32_t odrB = GPIOB->ODR; // read ODR B
			CT_LED->BYTE.LED7_0 = odrB; // write led 7..0
			
			uint32_t inputA = GPIOA->IDR; // read IDR A
			CT_LED->BYTE.LED23_16 = (uint8_t)inputA; // write LED23..16

			/// END: To be programmed

    }
}
void reset_GPIO(void)
{
    /* Reset GPIOA specific values */
    GPIOA->MODER = 0xa8000000;           // mode register
    GPIOA->OSPEEDR = 0x00000000;         // output speed register
    GPIOA->PUPDR = 0x64000000;           // pull resistor register
    GPIOA->OTYPER = 0x00000000;          // type register (pp / f. gate)
    GPIOA->AFRL = 0x00000000;
    GPIOA->AFRH = 0x00000000;
    GPIOA->ODR = 0x00000000;             // output data register
    
    /* Reset GPIOB specific values */
    GPIOB->MODER = 0x00000280;           // mode register
    GPIOB->OSPEEDR = 0x000000c0;         // output speed register
    GPIOB->PUPDR = 0x00000100;           // pull resistor register
    GPIOB->OTYPER = 0x00000000;          // type register (pp / f. gate)
    GPIOB->AFRL = 0x00000000;
    GPIOB->AFRH = 0x00000000;
    GPIOB->ODR = 0x00000000;             // output data register	
}
