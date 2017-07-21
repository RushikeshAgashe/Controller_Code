/*
 * test_main.c
 *
 *  Created on: Jul 16, 2017
 *      Author: ragashe
 */
#include "allHeaders.h"

ModbusSlave mb;

#if CAN_TEST

long      i;                    //CAN
long      loopcount = 0;        //CAN
struct ECAN_REGS ECanaShadow;   //CAN

void check_modbus_query(int);

void can_transmit(void){
    int i;
    int timeout =0;
    short status = 5;
    int message = 0x01;
    for(i=0; i < TXCOUNT; i++)
        {
           ECanaMboxes.MBOX0.MDL.all = 0x15AC0000;    // Message Data Reg Low - MSGID
           ECanaMboxes.MBOX0.MDH.all = 0xF0F0F0F0;    // Constant TEST DATA

           ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
           ECanaShadow.CANTRS.bit.TRS0 = 1;             // Begin Transmission
           ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

           do{
              ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           }while(ECanaShadow.CANTA.bit.TA0 != 1);

           ECanaShadow.CANTA.bit.TA0 = 1;
           ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;

           ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           ECanaShadow.CANTA.bit.TA0 = 1;                 // Clear TA0 by writing a 1 to TA0
           ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
           do{
               ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           }while (ECanaShadow.CANTA.bit.TA0 !=0);         // Wait for TA0 to clear to 0
           status = 1;
        }
    if(status) message = 0xFF; else message = 0xAA;
    check_modbus_query(message);
}
#endif

void InitVariable(void);
void check_modbus_query(int message){
    mb = construct_ModbusSlave();
    mb.holdingRegisters.dummy1 = message;
    while(1) {
        mb.loopStates(&mb);
    }
}

void main(void)
{
    InitSysCtrl();
    InitECanGpio();                 //CAN
    Gpio_select();
    InitPieCtrl();  // Disable PIE and clear PIEIER and PIEIFR registers
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();  // Initialize and enable PIE vector table
    InitECana();                      //CAN
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();

#if CAN_TEST
/*----------------------------------------- CAN test code--------------------------------*/

    ECanaRegs.CANME.all = 0x00000000;          // Disable all MBOXs
    /*----------Configuring MBOX0 for Tx----------*/
    ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
    ECanaShadow.CANTRS.bit.TRS0 = 1;
    ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME0 = 0;                 // MBOX0 Disable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaMboxes.MBOX0.MSGID.bit.AAM = 0;
    ECanaMboxes.MBOX0.MSGID.bit.AME = 0;
    ECanaMboxes.MBOX0.MSGID.all = MBOX_TX_MSGID;  // MSGID for MBOX0
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;     // 8 bits will be Tx'ed
    ECanaMboxes.MBOX0.MSGCTRL.bit.RTR = 0;     // Clear RTR flag-- No remote Transmit

    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD0 = 0;               // MBOX0 Direction Tx
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME0 = 1;               // MBOX0 Enable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    /*----------Configuring MBOX1 for Rx----------*/
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME1 = 0;               // MBOX1 Disable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaMboxes.MBOX1.MSGID.all = MBOX_RX_MSGID;  // MSGID for MBOX0
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx'ed

    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD1 = 1;               // MBOX1 Direction Rx
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME1 = 1;               // MBOX1 Enable
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx'ed/Tx'ed

    EALLOW;
    ECanaRegs.CANMIM.all = 0xC0000000;         //Enable interrupts for MBX00 and MBX1
    EALLOW;

//    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
//    ECanaShadow.CANMC.bit.STM = 1;              // Configure CAN for self-test mode
//    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
    EDIS;
    /*--------------------------------------*/
#endif

    InitEPWM();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    //PieVectTable.EPWM2_INT = &epwm2_timer_isr;
    PieVectTable.ADCINT = &adc_isr;
    PieVectTable.ECAN0INTA = &ecan0inta_isr;

    EDIS;

    SetupADC();

    IER |= M_INT1;
    IER |= M_INT3;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  //EPWM1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;  //ADC

    EINT;

#if CAN_TEST
    can_transmit();
#endif
    check_modbus_query(0xAF);
}
void InitVariable(void)
{
   // Tsampcc=0.0001;

}
//===========================================================================
// No more.
//===========================================================================
