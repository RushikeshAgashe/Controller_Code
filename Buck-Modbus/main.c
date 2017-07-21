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
Uint32  ErrorCount;
Uint32  PassCount;
Uint32  MessageReceivedCount;

Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;
void check_modbus_query(int);
void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   TestMbox1 = Mailbox->MDL.all; // = 0x9555AAAn (n is the MBX number)
   TestMbox2 = Mailbox->MDH.all; // = 0x89ABCDEF (a constant)
   TestMbox3 = Mailbox->MSGID.all;// = 0x9555AAAn (n is the MBX number)

} // MSGID of a rcv MBX is transmitted as the MDL data.

void mailbox_check(int32 T1, int32 T2, int32 T3)
{
    if((T1 != T3) || ( T2 != 0x89ABCDEF))
    {
       ErrorCount++;
    }
    else
    {
       PassCount++;
    }
}

void can_transmit(void){
    int i;
    int timeout =0;
    short status = 0;
    int message = 0x01;
    for(i=0; i < TXCOUNT; i++)
    //while(1)
        {
           ECanaRegs.CANTRS.all = 0x0FFFFFFF;  // Set TRS for all transmit mailboxes
           //ECanaRegs.CANTRS.bit.TRS1 = 1;             // Set TRS for mailbox under test
           //ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
           while(ECanaRegs.CANTA.all != 0x0FFFFFFF && timeout < 10000) timeout++;
           if (timeout >= 10000){status = 0;timeout = 0;}
           else{
           status = 1;
           ECanaRegs.CANTA.all = 0x0FFFFFFF;   // Clear all TAn
           mailbox_read(1); //Read MBOX1
           mailbox_check(TestMbox1,TestMbox2,TestMbox3);
           }
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
    /*------ CAN test code------------------*/
    ECanaMboxes.MBOX0.MSGID.all = 0x9555AAA0;  // Tx MBOX0 MSGID xx0
    ECanaMboxes.MBOX1.MSGID.all = 0x9555AAA1;  // Rx MBOX1 MSGID xx1
    ECanaRegs.CANMD.all = 0x80000000;          // Config MBOX0 as Tx and MBOX1 as Rx
    ECanaRegs.CANME.all = 0xC0000000;          // Enable MBOX0 and MBOX1
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx'ed/Tx'ed
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx'ed/Tx'ed
    ECanaMboxes.MBOX0.MDL.all = 0x9555AAA0;    // Message Data Reg Low - MSGID
    ECanaMboxes.MBOX0.MDH.all = 0xF0F0F0F0;    //Constant TEST DATA
    EALLOW;
    ECanaRegs.CANMIM.all = 0xC0000000;         //Enable interrupts for MBX00 and MBX1
    EALLOW;
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
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
    //check_modbus_query(0xAF);
}
void InitVariable(void)
{
   // Tsampcc=0.0001;

}



//===========================================================================
// No more.
//===========================================================================
