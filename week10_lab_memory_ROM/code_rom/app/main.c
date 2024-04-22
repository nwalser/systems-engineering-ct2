/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Application for testing external memory
 * --
 * -- $Id: main.c 5605 2023-01-05 15:52:42Z frtt $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdint.h>
#include "hal_ct_buttons.h"
#include "hal_ct_seg7.h"
#include "hal_gpio.h"
#include <reg_ctboard.h>


/// STUDENTS: To be programmed

#define array (*((volatile uint8_)

uint8_t* start = (uint8_t *) 0x64000400;
uint32_t range = 0xFF;
	
/// END: To be programmed

int main(void)
{
	/// STUDENTS: To be programmed
	uint8_t index = 0;
	uint16_t num_errors = 0;

	while(1){
		while(!hal_ct_button_is_pressed(HAL_CT_BUTTON_T0)){}
	
		while(1){
			uint8_t value = *(start + index);
			
			CT_LED->BYTE.LED7_0 = value;
			CT_LED->BYTE.LED23_16 = index;
			
			if(value != index){
				index++;
				num_errors++;
				CT_SEG7->BIN.HWORD = num_errors;
				break;
			}
			else{
				index++;
			}
		}
	}
	/// END: To be programmed
}
