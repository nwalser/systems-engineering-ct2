/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module hal_fmc.
 *
 *  The hardware abstraction layer for the memory controller.
 *
 *  $Id$
 * ------------------------------------------------------------------------- */

/* User includes */
#include "hal_fmc.h"
#include "reg_stm32f4xx.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define MASK_PERIPH_FMC     (0x00000001u)
#define MASK_SRAM_ENABLE    (0x00000001u)


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void hal_fmc_reset(hal_fmc_bank_t bank)
{
    assert(bank == HAL_FMC_SRAM_BANK1 || bank == HAL_FMC_SRAM_BANK2 || 
            bank == HAL_FMC_SRAM_BANK3 || bank == HAL_FMC_SRAM_BANK4);
    switch (bank) {
        case HAL_FMC_SRAM_BANK1:
            FMC->SRAM.BCR1 = 0x000030dbu;
            FMC->SRAM.BTR1 = 0x0fffffffu;
            break;
        
        case HAL_FMC_SRAM_BANK2:
            FMC->SRAM.BCR2 = 0x000030d2u;
            FMC->SRAM.BTR2 = 0x0fffffffu;
            break;
        
        case HAL_FMC_SRAM_BANK3:
            FMC->SRAM.BCR3 = 0x000030d2u;
            FMC->SRAM.BTR3 = 0x0fffffffu;
            break;
        
        case HAL_FMC_SRAM_BANK4:
            FMC->SRAM.BCR4 = 0x000030d2u;
            FMC->SRAM.BTR4 = 0x0fffffffu;
            break;
    }
}


/*
 * See header file
 */
void hal_fmc_init_sram(hal_fmc_bank_t bank, 
                       hal_fmc_sram_init_t init, 
                       hal_fmc_sram_timing_t timing)
{
    uint32_t reg_cr = 0, reg_tr = 0;
    
    /* Input check */
    timing.address_setup &= 0xfu;
    timing.address_hold &= 0xfu;
    if (timing.address_hold < 1u) timing.address_hold = 1u;
    timing.data_setup &= 0xffu;
    if (timing.data_setup < 1u) timing.data_setup = 1u;
    timing.bus_turnaround &= 0xfu;
    
    /* Input check clock divider (2..16) */
    if (timing.clk_divider > 16u) timing.clk_divider = 16u;
    if (timing.clk_divider < 2u) timing.clk_divider = 2u;
    timing.clk_divider -= 1u;   /**< 0b0001 -> clk / 2 */
    
    /* Input check data latency (2..17) */
    if (timing.data_latency > 17u) timing.data_latency = 17u;
    if (timing.data_latency < 2u) timing.data_latency = 2u;
    timing.data_latency -= 2u;  /**< 0b0000 -> latency = 2 */
    
    /* Process boolean parameter */
    if (init.address_mux == ENABLE)     reg_cr |= (1u << 1u);
    if (init.read_burst == ENABLE)      reg_cr |= (1u << 8u);
    if (init.write_enable == ENABLE)    reg_cr |= (1u << 12u);
    if (init.write_burst == ENABLE)     reg_cr |= (1u << 19u);
    if (init.continous_clock == ENABLE) reg_cr |= (1u << 20u);
    
    /* Process non boolean parameter */
    reg_cr |= ((uint32_t) init.type << 2u);
    reg_cr |= ((uint32_t) init.width << 4u);
    
    /* Process timing for async. SRAM */
    if (init.type == HAL_FMC_TYPE_SRAM) {
        reg_tr |= ((uint32_t) timing.address_setup << 0u);
        reg_tr |= ((uint32_t) timing.address_hold << 4u);
        reg_tr |= ((uint32_t) timing.data_setup << 8u);
        reg_tr |= ((uint32_t) timing.mode << 28u);
    }
    /* Process timing for sync. PSRAM */
    else if (init.type == HAL_FMC_TYPE_PSRAM) {
        reg_tr |= ((uint32_t) timing.clk_divider << 20u);
        reg_tr |= ((uint32_t) timing.data_latency << 24u);
    }
    /* Process bus turnaround time */
    reg_tr |= ((uint32_t) timing.bus_turnaround << 16u);
    
    /* Write register */
    assert(bank == HAL_FMC_SRAM_BANK1 || bank == HAL_FMC_SRAM_BANK2 || 
            bank == HAL_FMC_SRAM_BANK3 || bank == HAL_FMC_SRAM_BANK4);
    switch (bank) {
        case HAL_FMC_SRAM_BANK1:
            FMC->SRAM.BCR1 = reg_cr;
            FMC->SRAM.BTR1 = reg_tr;
            FMC->SRAM.BCR1 |= MASK_SRAM_ENABLE;
            break;
        
        case HAL_FMC_SRAM_BANK2:
            FMC->SRAM.BCR2 = reg_cr;
            FMC->SRAM.BTR2 = reg_tr;
            FMC->SRAM.BCR2 |= MASK_SRAM_ENABLE;
            break;
        
        case HAL_FMC_SRAM_BANK3:
            FMC->SRAM.BCR3 = reg_cr;
            FMC->SRAM.BTR3 = reg_tr;
            FMC->SRAM.BCR3 |= MASK_SRAM_ENABLE;
            break;
        
        case HAL_FMC_SRAM_BANK4:
            FMC->SRAM.BCR4 = reg_cr;
            FMC->SRAM.BTR4 = reg_tr;
            FMC->SRAM.BCR4 |= MASK_SRAM_ENABLE;
            break;
    }
}

