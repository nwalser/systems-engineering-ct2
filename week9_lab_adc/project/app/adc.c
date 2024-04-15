/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module adc.
 * --
 * --
 * -- $Id: adc.c 5610 2023-02-03 09:22:02Z frtt $
 * ------------------------------------------------------------------------- */

/* standard includes */
#include <stdint.h>
#include <reg_stm32f4xx.h>

/* user includes */
#include "adc.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define PERIPH_GPIOF_ENABLE (0x00000020)
#define PERIPH_ADC3_ENABLE  (0x00000400)

/* Configuring pin for ADC: PF.6 */
#define GPIOF_MODER_ANALOG (0x3 << 12)

#define RING_BUFF_SIZE 64

/* -- Macros used by student code
 * ------------------------------------------------------------------------- */

/// STUDENTS: To be programmed

uint8_t adc_ringbuffer_position = 0;
uint16_t adc_ringbuffer[RING_BUFF_SIZE]; 

/// END: To be programmed


/* Public function definitions
 * ------------------------------------------------------------------------- */

/*
 *  See header file
 */
void adc_init(void)
{
    /* Enable peripheral clocks */
    RCC->AHB1ENR |= PERIPH_GPIOF_ENABLE;
    RCC->APB2ENR |= PERIPH_ADC3_ENABLE;

    /* Configure PF.6 as input */
    GPIOF->MODER |= GPIOF_MODER_ANALOG;

    /* ADC common init */
    ADCCOM->CCR = 0;        // TSVREF = '0'    -> Temp sensor disabled
                            // VBATE = '0'     -> VBAT disabled
                            // ADCPRE = '00'   -> APB2 / 2 -> 21 MHz
                            // DMA = '00'      -> DMA disabled
                            // DELAY = '0000'  -> Delay 5 cycles
                            // MULTI = '00000' -> ADC independent mode

    /* Configure ADC3 */
    
    /// STUDENTS: To be programmed
	
		ADC3->SQR3 |= (4 << 0); // set first channel that gets converted 4
		ADC3->SQR1 |=  (0 << 20); // set only that one channel gets converted
		ADC3->CR2 |= (0b1 << 0); // enable adc

    /// END: To be programmed
}


/*
 *  See header file
 */
uint16_t adc_get_value(adc_resolution_t resolution)
{
    uint16_t adc_value;

    /// STUDENTS: To be programmed
	
		ADC3->CR1 &= ~(0b11 << 24); // reset resolution
		ADC3->CR1 |= resolution; // set resolution
		ADC3->CR2 |= (0b1 << 30); // start conversion
		while (!(ADC3->SR & (0b1 << 1))); // wait until conversion is done
		adc_value = ADC3->DR; // read value

    /// END: To be programmed

    return adc_value;
}


/*
 *  See header file
 */
uint16_t adc_filter_value(uint16_t adc_value)
{
    uint16_t filtered_value = 0;

    /// STUDENTS: To be programmed

		// overwrite old value
		adc_ringbuffer[adc_ringbuffer_position] = adc_value;
		adc_ringbuffer_position++;
		
		if(adc_ringbuffer_position >= RING_BUFF_SIZE) 
			adc_ringbuffer_position = 0;
	
	
		// create sum over ringbuffer
		uint32_t sum = 0;
		for(int i = 0; i < RING_BUFF_SIZE; i++){
			sum += adc_ringbuffer[i];
		}
	
		filtered_value = sum / RING_BUFF_SIZE;

    /// END: To be programmed

    return filtered_value;
}
