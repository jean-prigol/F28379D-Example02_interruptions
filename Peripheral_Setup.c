/*
 * Peripheral_Setup.c
 *
 *  Created on: 14 de fev de 2022
 *      Author: jeanp
 */
#include "Peripheral_Setup.h"
void Setup_GPIO(void){
    EALLOW;     // for enable to edit protect register
    // LED 31 group A, 2  -  configurando como GPIO
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0; // grupamento
    GpioCtrlRegs.GPAMUX2.bit.GPIO31  = 0;

    // LED 34 group B, 1  - configurando como GPIO
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0; // grupamento
    GpioCtrlRegs.GPBMUX1.bit.GPIO34  = 0;

    // configurando sem pull-up
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;


    // configurando a direção 1 - saída  0 - entrada
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    EDIS;

}


