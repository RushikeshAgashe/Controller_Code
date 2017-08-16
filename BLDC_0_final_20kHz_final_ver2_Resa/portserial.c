

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
/* ----------------------- Serial Port --------------------------------------*/
volatile struct SCI_REGS* sci_regs_ptr = &SciaRegs;

/* ----------------------- Defines ------------------------------------------*/

/* ----------------------- Start implementation -----------------------------*/
volatile int test = 0;

void
SerialReceiveMode( _Bool xRxEnable)
{

    ENTER_CRITICAL_SECTION();
    if(xRxEnable)
    {
        SciRxSet(sci_regs_ptr, ENABLED);
        SciRxIsrSet(sci_regs_ptr, ENABLED);
    }
    else
    {
        SciRxSet(sci_regs_ptr, DISABLED);
        SciRxIsrSet(sci_regs_ptr, DISABLED);
    }
    EXIT_CRITICAL_SECTION();
}

/*************************************************************************/

void
SerialTransmitMode (_Bool xTxEnable )
{

    ENTER_CRITICAL_SECTION();
    if( xTxEnable )
    {
        SciTxSet(sci_regs_ptr, ENABLED);
        SciTxIsrSet(sci_regs_ptr, ENABLED);
        //SendFirstByte();
    }
    else
    {
        SciTxSet(sci_regs_ptr, DISABLED);
        SciTxIsrSet(sci_regs_ptr, DISABLED);
    }
    EXIT_CRITICAL_SECTION();
}

/*************************************************************************/

_Bool
SerialInit(Uint32 ulBaudRate)
{
	SciInit(sci_regs_ptr,ulBaudRate);

	SerialReceiveMode(TRUE);
	SerialTransmitMode(FALSE);

    return TRUE;
}
/*************************************************************************/
_Bool
SerialPutByte( char ucByte )
{

	SciaRegs.SCITXBUF = ucByte;
    return TRUE;
}
/*************************************************************************/
_Bool
SerialGetByte( char * pucByte )
{

    *pucByte = SciaRegs.SCIRXBUF.all;
    return TRUE;
}

/*************************************************************************/
interrupt void SciRxIsrHandler(void)
{

	SerialReceive_Cb();

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;
}// End of SciRxIsrHandler

/*************************************************************************/


interrupt void SciTxIsrHandler(void)
{
	SerialTransmit_Cb();

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;
}// End of SciTxIsrHandler

/*************************************************************************/
