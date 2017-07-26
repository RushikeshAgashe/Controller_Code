/*
 * can.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ragashe
 */
#include "allHeaders.h"
#include "extern_variable.h"
#include "can.h"
#if CAN_TEST
Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

Uint16  wTestMbox1 = 0;
Uint16  wTestMbox2 = 0;
Uint16  wTestMbox3 = 0;

Uint32  ErrorCount = 0;
Uint32  PassCount = 0;
Uint32  MessageReceivedCount = 0;

ModbusData passedDataRequest,passedDataResponse;
//ModbusSlave mb;
unsigned long *recBufferPointer = (unsigned long *)&passedDataRequest;
unsigned long *txBufferPointer = (unsigned long *)&passedDataResponse;

void construct_message()
{
    *(recBufferPointer++) = TestMbox1;
    *(recBufferPointer++) = TestMbox2;
}

void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   *(recBufferPointer++) = Mailbox->MDL.all;
   *(recBufferPointer++) = Mailbox->MDH.all;
   //wTestMbox1 = (Mailbox->MDL.all & 0x0000FFFF);            // = 0x15AC000n (n is the MBX number)
   //wTestMbox2 = (Mailbox->MDL.all & 0xFFFF0000) >> 16;            // = 0x15AC000n (n is the MBX number)
   TestMbox1 = Mailbox->MDL.all;
   TestMbox2 = Mailbox->MDH.all;            // = 0xF0F0F0F0 (a constant)
   TestMbox3 = Mailbox->MSGID.all;          // = 0x15AC000n (n is the MBX number)
   construct_message();
} // MSGID of a rcv MBX is transmitted as the MDL data.


volatile short status = 5;

void CAN_transmit(ModbusData *self){
    int i;
    unsigned long *bufferPointer = (unsigned long *)self;
    //check_modbus_query(*bufferPointer);
    //int message = 0x01;
    for(i=0; i < sizeof(ModbusData); i+=2)
        {
           status = 0;
           ECanaMboxes.MBOX0.MDL.all = *(bufferPointer++);    // Message Data Reg Low - MSGID
           ECanaMboxes.MBOX0.MDH.all = *(bufferPointer++);    // Constant TEST DATA

           ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
           ECanaShadow.CANTRS.bit.TRS0 = 1;             // Begin Transmission
           ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
           while(status != 1);
        }
}

void delay(){
    unsigned long long int i=0;
    for(i = 0; i< 500000;i++);
}
interrupt void ecan1inta_isr(void){

    ECanaShadow.CANGIF1.all = ECanaRegs.CANGIF1.all;
    //TOGGLE_DEBUG_BIT;
    /* MBOX0 Caused Interrupt*/
    if (ECanaShadow.CANGIF1.bit.MIV1 == 0)
    {
        // Message Handling Code goes here
        ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
        ECanaShadow.CANTA.bit.TA0 = 1;                 // Clear TA0 by writing a 1 to TA0
        ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
        status = 1;
    }

    /* MBOX1 Caused Interrupt*/
    else if (ECanaShadow.CANGIF1.bit.MIV1 == 1)
    {
        // Message Handling Code goes here
        int i=0;
        mailbox_read(ECanaShadow.CANGIF1.bit.MIV1);

#if CONTROLLER_ID == 1 || CONTROLLER_ID ==2
      // slave->receive function
        i = passedDataRequest.slaveAddress;
        while(i>0){
            TOGGLE_DEBUG_BIT;
            delay();
            TOGGLE_DEBUG_BIT;
            delay();
            i--;
        }
        //TOGGLE_DEBUG_BIT;
        //mb = construct_ModbusSlave();
        //mb.receive(&mb);
#endif
#if CONTROLLER_ID == 3
      // slave->transmit function
      //TOGGLE_DEBUG_BIT;
#endif
        //unsigned long *testPointer = (unsigned long *)&passedDataRequest;
        //i = passedDataRequest.functionCode+1;


        ECanaRegs.CANRMP.all = 0x00000002;
    }

    /* MBOX2 Caused Interrupt*/
    else if (ECanaShadow.CANGIF1.bit.MIV1 == 2)
    {
        // Message Handling Code goes here
        mailbox_read(ECanaShadow.CANGIF1.bit.MIV1);
        ECanaRegs.CANRMP.all = 0x00000002;
    }

    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
    IER |= 0x0100;

    //mailbox_read(1);                                //Read MBOX1
    //mailbox_check(TestMbox1,TestMbox2,TestMbox3);
}
#endif



