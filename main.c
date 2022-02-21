#include "Peripheral_Setup.h"

/**
 * main.c
 */
uint32_t count = 0;

__interrupt void isr_cpu_timer0(void);

int main(void){
    InitSysCtrl();          // Initialize System Control
    DINT;                   // Disable CPU interrupts
    InitPieCtrl();          // Initialize the PIE control to the default state
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // clear all CPU interrupt flags
    InitPieVectTable();     // Initialize the PIE vector table

    Setup_GPIO();

    // Timer 0 interruption configuration - START
    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;  //& pega o endereço da função a ser executada, se não linkar ele vai para a função padrão em DefaulISR e o programa "trava"
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  //Timer 0 (habilita a "colula dentro da linha" ver p79 worskshop)
    EDIS;
    IER |= M_INT1; // habilita a linha
    // Timer 0 interruption configuration - END

    InitCpuTimers();  //inicializar periférico e suas configurações
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);  // period is in us
    CpuTimer0Regs.TCR.all = 0x4001;        // habilitar a interrupção dentro do periférico Timer

    EINT;                   // Enable Global interrupt INTM
    ERTM;                   // Enable Global real time interrupt DBGM

    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;

    // GpioDataRegs.GPASET.bit.GPIO31 = 1;
    // GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
    // GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

    while(1){
        for(count = 0; count < 0x000FFFFFF; count++);
        //GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

    }
	//return 0;
}

__interrupt void isr_cpu_timer0(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  //acknowledge, clear the IF and return to the main program
}
