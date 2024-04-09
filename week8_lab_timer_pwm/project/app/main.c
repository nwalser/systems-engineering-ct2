/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 lab - Timer PWM
 * -- Description : Main program and interrupt service routine
 * --
 * --               Task 1: - Setup timer TIM4 to 1s.
 * --                       - Setup interrupt to toggle LED
 * --               Task 2: - Setup timer TIM3 to PWM mode
 * --                       - Read DIP switches to set duty cycles of channels
 * --               Task 3: - Use interrupt of TIM4 to create a transition
 * --                         from one colour to another
 * --
 * -- $Id: main.c 5605 2023-01-05 15:52:42Z frtt $
 * ------------------------------------------------------------------------- */

/* standard includes */
#include <stdint.h>
#include <reg_stm32f4xx.h>
#include <reg_ctboard.h>

/* user includes */
#include "timer.h"


/* -- Macros used as by student code
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed



/// END: To be programmed

/* -- Function prototypes
 * ------------------------------------------------------------------------- */
 void TIM4_IRQHandler(void);
 

/* -- global variables visible only within this module
 * ------------------------------------------------------------------------- */

/* cyclic counter value between 0 and 0xF */
static uint16_t cycle_counter_4bit = 0;

/* -- M A I N
 * ------------------------------------------------------------------------- */

int main(void)
{
    /// STUDENTS: To be programmed
	
		CT_LED->BYTE.LED31_24 = 0x0; // reset led values

		tim3_init();
		tim4_init();
	
		while(1) {
			if(CT_DIPSW->BYTE.S31_24 & 0b10000000){
				tim3_set_compare_register(PWM_CH1, cycle_counter_4bit);
				tim3_set_compare_register(PWM_CH2, 0xF - cycle_counter_4bit);
			}
			else{
				tim3_set_compare_register(PWM_CH1, CT_DIPSW->BYTE.S7_0 & 0b1111);
				tim3_set_compare_register(PWM_CH2, CT_DIPSW->BYTE.S15_8 & 0b1111);
			}
			
			tim3_set_compare_register(PWM_CH3, CT_DIPSW->BYTE.S23_16 & 0b1111);
		}

    /// END: To be programmed
}


/* -- Interrupt service routine
 * ------------------------------------------------------------------------- */

void TIM4_IRQHandler(void)
{
    /// STUDENTS: To be programmed

		tim4_reset_uif();
		CT_LED->BYTE.LED31_24 = ~CT_LED->BYTE.LED31_24;

		cycle_counter_4bit++;
		if(cycle_counter_4bit > 15){
			cycle_counter_4bit=0;
		}
	
    /// END: To be programmed
}
