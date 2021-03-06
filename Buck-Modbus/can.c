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

Uint32  ErrorCount = 0;
Uint32  PassCount = 0;
Uint32  MessageReceivedCount = 0;

void delay(){
    unsigned long long int i=0;
    for(i = 0; i< 500000;i++);
}

void debug_func(){
    unsigned int i = 2;
    while(i > 0){
        delay();
        TOGGLE_DEBUG_BIT;
        delay();
        TOGGLE_DEBUG_BIT;
        i--;
    }
}
void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
#if CONTROLLER_ID == 1 || CONTROLLER_ID == 2
   *(recBufferPointer++) = Mailbox->MDL.all;
   *(recBufferPointer++) = Mailbox->MDH.all;
#endif
#if CONTROLLER_ID == 3
   *(txBufferPointer++) = Mailbox->MDL.all;
   *(txBufferPointer++) = Mailbox->MDH.all;
#endif
} // MSGID of a rcv MBX is transmitted as the MDL data.


volatile short status = 5;
void CAN_transmit(ModbusData *self){
    unsigned int i, *bufferPointer = (unsigned int *)self;
    self->completed = 1;
    for(i=0; i <= sizeof(ModbusData); i+=2)
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

interrupt void ecan1inta_isr(void){
    ECanaShadow.CANGIF1.all = ECanaRegs.CANGIF1.all;

    /* MBOX0 Caused Interrupt*/
    if (ECanaShadow.CANGIF1.bit.MIV1 == 0)
    {
        ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
        ECanaShadow.CANTA.bit.TA0 = 1;                 // Clear TA0 by writing a 1 to TA0
        ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
        status = 1;
    }

    /* MBOX1 Caused Interrupt*/
    else if (ECanaRegs.CANRMP.all == 0x00000002)
    {
        #if CONTROLLER_ID == 1 || CONTROLLER_ID ==2
        mailbox_read(1);
        if(mb.passedDataRequest.completed == 1){
               delay();  // Don't know why it's required but doesn't work without it
               RX_Flag = 1;
          }
        #endif

        #if CONTROLLER_ID == 3
        mailbox_read(1);
      if(mb.passedDataResponse.completed == 1){
           txBufferPointer = (unsigned int *)&mb.passedDataResponse;  //Re-initialize pointer to base address of passedDataRequest
           mb.passedDataResponse.completed = 0;
           pass_flag = 1;
           mb.transmit(&mb);
          }
        #endif
        ECanaRegs.CANRMP.all = 0x00000002;
    }

    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
    IER |= 0x0100;
}
#endif



