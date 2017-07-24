/*
 * can.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ragashe
 */
#include "allHeaders.h"
#include "extern_variable.h"
#if CAN_TEST
Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

Uint32  ErrorCount = 0;
Uint32  PassCount = 0;
Uint32  MessageReceivedCount = 0;

/*
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
*/
volatile short status = 5;
void CAN_transmit(void){
    int i;
    int message = 0x01;
    for(i=0; i < TXCOUNT; i++)
        {
           status = 0;
           ECanaMboxes.MBOX0.MDL.all = 0x15AC0000;    // Message Data Reg Low - MSGID
           ECanaMboxes.MBOX0.MDH.all = 0xF0F0F0F0;    // Constant TEST DATA
           //CLEAR_BIT;
           ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
           ECanaShadow.CANTRS.bit.TRS0 = 1;             // Begin Transmission
           ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
           while(status != 1);
        }
/*
           do{
              ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           }while(ECanaShadow.CANTA.bit.TA0 == 0);
           //TOGGLE_DEBUG_BIT;

           ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           ECanaShadow.CANTA.bit.TA0 = 1;                 // Clear TA0 by writing a 1 to TA0
           ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
           do{
               ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
           }while (ECanaShadow.CANTA.bit.TA0 !=0);         // Wait for TA0 to clear to 0

        }
    if(status == 1) message = 0xFF; else message = 0xAA;
    check_modbus_query(message);*/
}

interrupt void ecan1inta_isr(void){
    ECanaShadow.CANGIF1.all = ECanaRegs.CANGIF1.all;
    TOGGLE_DEBUG_BIT;
    /* MBOX0 Caused Interrupt*/
    if (ECanaShadow.CANGIF1.bit.MIV1 == 0)
    {
        // Message Handling Code goes here
//        ECanaShadow.CANGIF1.all = ECanaRegs.CANGIF1.all;
//        ECanaShadow.CANGIF1.bit.GMIF1 = 1;
//        ECanaRegs.CANGIF1.all = ECanaShadow.CANGIF1.all;

        ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
        ECanaShadow.CANTA.bit.TA0 = 1;                 // Clear TA0 by writing a 1 to TA0
        ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
        status = 1;
    }

    /* MBOX1 Caused Interrupt*/
    else if (ECanaShadow.CANGIF1.bit.MIV1 == 1)
    {
        //TOGGLE_DEBUG_BIT;
        // Message Handling Code goes here
        //ECanaRegs.CANRMP.all = 0x00000002;
    }

    /* MBOX2 Caused Interrupt*/
    else if (ECanaShadow.CANGIF1.bit.MIV1 == 2)
    {
        // Message Handling Code goes here
    }

    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
    IER |= 0x0100;

    //mailbox_read(1);                                //Read MBOX1
    //mailbox_check(TestMbox1,TestMbox2,TestMbox3);
}
#endif



