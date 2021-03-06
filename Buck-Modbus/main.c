/*
 * test_main.c
 *
 *  Created on: Jul 16, 2017
 *      Author: ragashe
 */
#include "allHeaders.h"

ModbusSlave mb;

volatile int RX_Flag = 0;
volatile int pass_flag = 0;
unsigned int *txBufferPointer = (unsigned int *)&mb.passedDataResponse;
unsigned int *recBufferPointer = (unsigned int *)&mb.passedDataRequest;

#if CAN_TEST
struct ECAN_REGS ECanaShadow;   //CAN
#endif

void InitVariable(void);

void check_modbus_query(unsigned int *message){
    while(1){
        mb.holdingRegisters.dummy1 = *message;
        mb.loopStates(&mb);
    }
}

void main(void)
{
    InitSysCtrl();
    InitECanGpio();                 //CAN
    Gpio_select();
    InitPieCtrl();                  // Disable PIE and clear PIEIER and PIEIFR registers
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();             // Initialize and enable PIE vector table
    InitECana();                    //CAN
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);  // Required while using F28335.cmd
    InitFlash();
    TOGGLE_DEBUG_BIT;

#if CAN_TEST
/*----------------------------------------- CAN test code--------------------------------*/

    ECanaRegs.CANME.all = 0x00000000;                   // Disable all MBOXs

    /*----------Configuring MBOX0 for Tx----------*/
    ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
    ECanaShadow.CANTRS.bit.TRS0 = 1;
    ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME0 = 0;                      // MBOX0 Disable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX0.MSGID.bit.AAM = 0;
    ECanaMboxes.MBOX0.MSGID.bit.AME = 0;
    ECanaMboxes.MBOX0.MSGID.all = MBOX0_MSGID;        // MSGID for MBOX0
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;              // 8 bits will be Tx'ed
    ECanaMboxes.MBOX0.MSGCTRL.bit.RTR = 0;              // Clear RTR flag-- No remote Transmit
    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD0 = 0;                      // MBOX0 Direction Tx
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME0 = 1;                      // MBOX0 Enable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    /*----------Configuring MBOX1 for Rx----------*/
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME1 = 0;                      // MBOX1 Disable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;
    ECanaMboxes.MBOX1.MSGID.all = MBOX1_MSGID;          // MSGID for MBOX1
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;              // 8 bits will be Rx'ed
    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD1 = 1;                      // MBOX1 Direction Rx
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME1 = 1;                      // MBOX1 Enable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    EALLOW;
    PieVectTable.ECAN1INTA = &ecan1inta_isr;
    EDIS;
    /*--------------------------------------*/
#endif

    InitEPWM();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    //PieVectTable.EPWM2_INT = &epwm2_timer_isr;
    PieVectTable.ADCINT = &adc_isr;

    EDIS;

    SetupADC();

#if CAN_TEST
    SetupCAN();
#endif

    IER |= M_INT1;
    IER |= M_INT3;
    IER |= M_INT9;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  //EPWM1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;  //ADC
    PieCtrlRegs.PIEIER9.bit.INTx6 = 1;  //CAN

    EINT;
    construct_ModbusSlave(&mb);
#if CONTROLLER_ID == 1 || CONTROLLER_ID == 2
    while(1){
        while(RX_Flag == 0);
        recBufferPointer = (unsigned int *)&mb.passedDataRequest;  //Re-initialize pointer to base address of passedDataRequest
        mb.passedDataRequest.completed = 0;
        RX_Flag = 0;
        mb.process(&mb);
        mb.passedDataRequest.clear(&mb.passedDataRequest);
        mb.dataRequest.clear(&mb.dataRequest);
        mb.dataResponse.clear(&mb.dataResponse);
    }
#endif
#if CAN_TEST && CONTROLLER_ID == 3
    unsigned int *p = (unsigned int *)&mb.dataRequest;
    check_modbus_query(p);
#endif
}
void InitVariable(void)
{
   // Tsampcc=0.0001;
}
//===========================================================================
// No more.
//===========================================================================
