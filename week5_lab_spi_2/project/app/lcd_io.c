/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Project     : CT2 lab - SPI Display
 * -- Description : Contains the implementations of the functions
 * --               to write and read frames from and to the TFT-LCD
 * --               display EAeDIPTFT43-A.
 * --
 * -- $Id: lcd_io.c 4720 2019-03-04 10:11:31Z akdi $
 * ------------------------------------------------------------------
 */
#include "lcd_io.h"
#include "hal_spi.h"
#include "hal_sbuf.h"

#define ACK_CHAR         (uint8_t)0x06
#define DC1_CHAR         (uint8_t)0x11
#define DC2_CHAR         (uint8_t)0x12
#define ESC_CHAR         (uint8_t)0x1B
#define ONE_CHAR         (uint8_t)0x01

#define NOTHING_RECEIVED (uint8_t)0
enum { SUCCESS = 0, ERRORCODE = 1 };

/* ------------------------------------------------------------------
 * -- Function prototypes
 * ------------------------------------------------------------------
 */
static void send_read_display_buffer_request(void);
uint8_t write_cmd(const uint8_t *cmdBuffer, uint8_t length, uint8_t dc);

/* ------------------------------------------------------------------
 * -- Function implementations
 * ------------------------------------------------------------------
 */

/*
 * according to description in header file
 */
void init_display_interface(void)
{
    hal_spi_init();
    hal_sbuf_init();
}


/*
 * according to description in header file
 */
uint8_t read_display_buffer(uint8_t *readBuffer)
{
    /// STUDENTS: To be programmed
		if(!hal_sbuf_get_state())
			return 0;
	
    uint8_t command_buffer[1];
		command_buffer[0] = 0x53;
		uint8_t command_result = write_cmd(command_buffer, 1, 0x12);

		if(command_result != 0)
			return 0;

		uint8_t dc1 = hal_spi_read_write(0x00);
		
		if(dc1 != 0x11)
			return 0;
		
		uint8_t length = hal_spi_read_write(0x00);
		
		for(int i = 0; i < length; i++){
			readBuffer[i] = hal_spi_read_write(0x00);
		}
		
		uint8_t sum = 0;
		for(int i = 0; i < length; i++){
			sum += readBuffer[i];
		}
		uint8_t checksum = sum % 256;
		uint8_t read_checksum = hal_spi_read_write(0x00);

		if(checksum != read_checksum)
			return 0;

		return length;
		
    /// END: To be programmed
}


/*
 * according to description in header file
 */

uint8_t write_cmd_to_display(const uint8_t *cmdBuffer, uint8_t length){
	return write_cmd(cmdBuffer, length, 0x11);
}

uint8_t write_cmd(const uint8_t *cmdBuffer, uint8_t length, uint8_t dc)
{
    /// STUDENTS: To be programmed
	
	
		uint8_t send_buffer_size = length+4;
    uint8_t send_buffer[send_buffer_size];
		
		uint8_t startByte = dc;
		uint8_t lengthByte = length + 1;
		uint8_t escByte = 0x1B;
	
		send_buffer[0] = startByte; 
		send_buffer[1] = lengthByte; 
		send_buffer[2] = escByte; 
	
		for(int i = 0; i < length; i++){
			send_buffer[3+i] = cmdBuffer[i];
		}
	
		// checksum
		uint8_t sum = 0;
		for(int i = 0; i < send_buffer_size-1; i++){
			sum += send_buffer[i];
		}
		
		uint8_t checksum = sum % 256;
		send_buffer[send_buffer_size-1] = checksum; 		
	
		for(int i = 0; i < send_buffer_size; i++){
				hal_spi_read_write(send_buffer[i]);
		}
		
		uint8_t rec_byte = hal_spi_read_write(0x00);
		
		if(rec_byte != 0x06)
			return 1;
		
		return 0;
	
    /// END: To be programmed
}


/*
 * Assemble and send a packet to trigger the reading of the display buffer
 * Uses the sequence "<DC2>, 0x01, 0x53, checksum" according to datasheet
 */
static void send_read_display_buffer_request(void)
{
    /// STUDENTS: To be programmed
		
    /// END: To be programmed
}

