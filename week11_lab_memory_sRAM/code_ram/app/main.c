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

#include <stdint.h>
#include "hal_rcc.h"
#include "hal_fmc.h"
#include "hal_ct_lcd.h"
#include "reg_ctboard.h"
#include "hal_ct_buttons.h"
#include "hal_ct_seg7.h"

#define NR_OF_DATA_LINES           8
#define NR_OF_ADDRESS_LINES       11
#define CHECKER_BOARD           0xAA
#define INVERSE_CHECKER_BOARD   0x55
#define WALKING_ONES_ADDRESS    0x7FF

/* Set-up the macros (#defines) for your test */
/// STUDENTS: To be programmed

#define START_ADDRESS 0x64000000
#define END_OFFSET 0x0F

/// END: To be programmed

int main(void)
{
    hal_fmc_sram_init_t init;
    hal_fmc_sram_timing_t timing;
    
    /* add your required automatic (local) variables here */ 
    /// STUDENTS: To be programmed


    /// END: To be programmed

    init.address_mux = DISABLE;                             // setup peripheral
    init.type = HAL_FMC_TYPE_SRAM;
    init.width = HAL_FMC_WIDTH_8B;
    init.write_enable = ENABLE;

    timing.address_setup = 0xFF;                            // all in HCLK
                                                            // cycles
    timing.address_hold = 0xFF;
    timing.data_setup = 0xFF;

    hal_fmc_init_sram(HAL_FMC_SRAM_BANK2, init, timing);    // init external bus
                                                            // bank 2 (NE2)
                                                            // asynch
    
    /* Data Bus Test - Walking ONES test */
    /// STUDENTS: To be programmed

		uint8_t errors = 0x00;

		for(int i = 0; i < NR_OF_ADDRESS_LINES; i++){
			uint8_t pattern = 0x01 << i;
			uint8_t* ptr = (uint8_t*)(START_ADDRESS + WALKING_ONES_ADDRESS);

			// write and read pattern
			*ptr = pattern;
			uint8_t value = *ptr;
			
			if(pattern != value)
				errors |= pattern;
		}

		CT_LED->BYTE.LED7_0 = errors;
    
    /* Device Test 
     * (1) Fill the whole memory with known increment pattern.
     *          Address     Data
     *          0x000       0x01
     *          0x001       0x02
     *          .....       ....
     *          0x0FE       0xFF
     *          0x0FF       0x00
     *          0x100       0x01
     *          .....       ....
     *
     * (2) First test: Read back each location and check pattern.
     *     In case of error, write address with wrong data to 7-segment and
     *     wait for press on button T0.
     *     Bitwise invert  the pattern in each location for the second test
     *
     * (3) Second test: Read back each location and check for new pattern.
     *     In case of error, write address with wrong data to 7-segment and
     *     wait for press on button T0.
     */
    /// STUDENTS: To be programmed

		// write normal
		for(uint32_t address = START_ADDRESS; address < (START_ADDRESS+END_OFFSET); address++){
			uint8_t* ptr = (uint8_t*)address;
			uint8_t pattern = (address + 1) % 0xFF;
			
			// write normal
			*ptr = pattern;
		}
		
		// read normal, write inverted
		for(uint32_t address = START_ADDRESS; address < (START_ADDRESS+END_OFFSET); address++){
			uint8_t* ptr = (uint8_t*)address;
			uint8_t pattern = (address + 1) % 0xFF;
			
			// read and test
			uint8_t value = *ptr;
			if(value != pattern){
				CT_SEG7->BIN.HWORD = address;
				while (!hal_ct_button_is_pressed(HAL_CT_BUTTON_T0)) {}
			}
			
			// write inverted
			*ptr = ~pattern;
		}
		
		// read inverted
		for(uint32_t address = START_ADDRESS; address < (START_ADDRESS+END_OFFSET); address++){
			uint8_t* ptr = (uint8_t*)address;
			uint8_t pattern = (address + 1) % 0xFF;
			
			// read and test
			uint8_t value = *ptr;
			uint8_t inverted = ~pattern;
			
			if(value != inverted){
				CT_SEG7->BIN.HWORD = address;
				while (!hal_ct_button_is_pressed(HAL_CT_BUTTON_T0)) {}
			}
		}

    /// END: To be programmed
    
    // Write 'End'
    CT_SEG7->RAW.BYTE.DS0 = 0xA1;
    CT_SEG7->RAW.BYTE.DS1 = 0xAB;
    CT_SEG7->RAW.BYTE.DS2 = 0x86;
    CT_SEG7->RAW.BYTE.DS3 = 0xFF;
    
    while(1){
    }

}
