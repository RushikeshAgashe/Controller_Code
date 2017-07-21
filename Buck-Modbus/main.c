/*
 * test_main.c
 *
 *  Created on: Jul 16, 2017
 *      Author: ragashe
 */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"
#include "string.h"
#include "ModbusSlave.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"

#define CAN_TEST 0
ModbusSlave mb;

#if CAN_TEST
#define TXCOUNT  100
long      i;                    //CAN
long      loopcount = 0;        //CAN
struct ECAN_REGS ECanaShadow;   //CAN
Uint32  ErrorCount;
Uint32  PassCount;
Uint32  MessageReceivedCount;

Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

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
    for(i=0; i < TXCOUNT; i++)
       {
           ECanaRegs.CANTRS.all = 0x0FFFFFFF;  // Set TRS for all transmit mailboxes
           ECanaRegs.CANTRS.bit.TRS25 = 1;             // Set TRS for mailbox under test
           //ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
           while(ECanaRegs.CANTA.all != 0x0FFFFFFF );
           ECanaRegs.CANTA.all = 0x0FFFFFFF;   // Clear all TAn
           mailbox_read(1); //Read MBOX1
           mailbox_check(TestMbox1,TestMbox2,TestMbox3);
        }

}
#endif

void InitVariable(void);
void check_modbus_query(void){
    mb = construct_ModbusSlave();
    mb.holdingRegisters.dummy1 = 0xF;
    while(1) {
        mb.loopStates(&mb);
    }
}

void main(void)
{
    InitSysCtrl();
    //InitECanGpio();                 //CAN
    Gpio_select();
    InitPieCtrl();  // Disable PIE and clear PIEIER and PIEIFR registers
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();  // Initialize and enable PIE vector table
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();

#if CAN_test
    /*------ CAN test code------------------*/
    ECanaMboxes.MBOX0.MSGID.all = 0x9555AAA0;  // Tx MBOX0 MSGID xx0
    ECanaMboxes.MBOX1.MSGID.all = 0x9555AAA1;  // Rx MBOX1 MSGID xx1
    ECanaRegs.CANMD.all = 0x80000000;          // Config MBOX0 as Tx and MBOX1 as Rx
    ECanaRegs.CANME.all = 0xC0000000;          // Enable MBOX0 and MBOX1
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx/Tx
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;     // 8 bits will be Rx/Tx
    ECanaMboxes.MBOX0.MDL.all = 0x9555AAA0;    // Message Data Reg Low - MSGID
    ECanaMboxes.MBOX0.MDH.all = 0xF0F0F0F0;    //Constant TEST DATA
    EALLOW;
    ECanaRegs.CANMIM.all = 0xC0000000;         //Enable interrupts for MBX00 and MBX1
    EALLOW;
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    EDIS;
    /*--------------------------------------*/
#endif

    InitEPWM();

    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    PieVectTable.ADCINT = &adc_isr;

    EDIS;

    SetupADC();

    IER |= M_INT1;
    IER |= M_INT3;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  //EPWM1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;  //ADC

    EINT;
    check_modbus_query();

#if CAN_TEST
    can_transmit();
#endif
}
void InitVariable(void)
{
   // Tsampcc=0.0001;

}



//===========================================================================
// No more.
//===========================================================================




