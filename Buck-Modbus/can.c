/*
 * can.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ragashe
 */
#include "allHeaders.h"
#include "extern_variable.h"

Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

Uint32  ErrorCount = 0;
Uint32  PassCount = 0;
Uint32  MessageReceivedCount = 0;

void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
   TestMbox1 = Mailbox->MDL.all;            // = 0x15AC000n (n is the MBX number)
   TestMbox2 = Mailbox->MDH.all;            // = 0xF0F0F0F0 (a constant)
   TestMbox3 = Mailbox->MSGID.all;          // = 0x15AC000n (n is the MBX number)

} // MSGID of a rcv MBX is transmitted as the MDL data.

void mailbox_check(int32 T1, int32 T2, int32 T3)
{
    if((T1 != T3) || ( T2 != 0xF0F0F0F0))
    {
       ErrorCount++;
    }
    else
    {
       PassCount++;
    }
}

interrupt void ecan0inta_isr(void){
    mailbox_read(1);                                //Read MBOX1
    mailbox_check(TestMbox1,TestMbox2,TestMbox3);
}



