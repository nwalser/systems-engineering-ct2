/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module lcd
 * --               Performs all the interactions with the lcd
 * --
 * -- $Id: lcd.c 5144 2020-09-01 06:17:21Z ruan $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdio.h>

/* user includes */
#include "lcd.h"
#include "reg_ctboard.h"

/* macros */
#define LCD_ADDR_LINE1      0u
#define LCD_ADDR_LINE2      20u

#define NR_OF_CHAR_PER_LINE 20u

#define LCD_CLEAR           "                    "

#define STR_EXPLANATION  "Total value: "
#define STR_EXPLANATION_SIZE 13

/// STUDENTS: To be programmed

static char buffer[5];


void hal_ct_lcd_clear(void){
	
	//clear each single char from the LCD (no better solution found until now)???????
	for(int i=0; i<20;i++){
		CT_LCD->ASCII[LCD_ADDR_LINE1+i] = LCD_CLEAR[0];	//clear line 1
		CT_LCD->ASCII[LCD_ADDR_LINE2+i] = LCD_CLEAR[0];	//clear line 2
	}
	//background adjustment to full green
	CT_LCD->BG.RED = 0x0000;
	CT_LCD->BG.BLUE = 0x0000;
	CT_LCD->BG.GREEN = 0xFFFF;
}

void lcd_write_value(uint8_t slot_nr, uint8_t value){
	snprintf(buffer, 4, "%d", value); //generate a formatted string to display thte current value
	CT_LCD->ASCII[LCD_ADDR_LINE1 + 3*(slot_nr-1)+2] = buffer[2]; //value output (1x)
	CT_LCD->ASCII[LCD_ADDR_LINE1 + 3*(slot_nr-1)+1] = buffer[1]; //value output (10x)
	CT_LCD->ASCII[LCD_ADDR_LINE1 + 3*(slot_nr-1)] = buffer[0]; //value output (100x)
}

void lcd_write_total(uint8_t total_value){
	for(int i=0; i<STR_EXPLANATION_SIZE; i++){
		CT_LCD->ASCII[LCD_ADDR_LINE2+i] = STR_EXPLANATION[i];
	}
	snprintf(buffer, 5, "%d", total_value);
	CT_LCD->ASCII[LCD_ADDR_LINE2 + STR_EXPLANATION_SIZE+2] = buffer[2]; //total value output (1x)
	CT_LCD->ASCII[LCD_ADDR_LINE2 + STR_EXPLANATION_SIZE+1] = buffer[1]; //total value output (10x)
	CT_LCD->ASCII[LCD_ADDR_LINE2 + STR_EXPLANATION_SIZE] = buffer[0]; //total value output (100x)	
}



/// END: To be programmed
