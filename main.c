#include "Peripheral_Setup.h"

/**
 * main.c
 */
uint32_t count = 0;
int main(void){
    InitSysCtrl();          // Initialize System Control
    DINT;                   // Disable CPU interrupts
    InitPieCtrl();          // Initialize the PIE control to the default state
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // clear all CPU interrupt flags
    InitPieVectTable();     // Initialize the PIE vector table

    Setup_GPIO();

    EINT;                   //Enable Global interrupt INTM
    ERTM;                   // Enable Global realtime interrupt DBGM

    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;

    // GpioDataRegs.GPASET.bit.GPIO31 = 1;
    // GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
    // GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

    while(1){
        for(count = 0; count < 0x000FFFFFF; count++);
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

    }
	return 0;
}
