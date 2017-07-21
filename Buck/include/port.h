
#ifndef _PORT_H
#define _PORT_H

/* ----------------------- Platform includes --------------------------------*/

#include "DSP2833x_Project.h"
#include "hal_sci.h"
#include "stdbool.h"
#include "serial_api.h"




#define ENTER_CRITICAL_SECTION(  )   DINT
#define EXIT_CRITICAL_SECTION(  )    EINT

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif



#define ENABLED		TRUE
#define DISABLED 	FALSE

extern interrupt void SciTxIsrHandler(void);

extern interrupt void SciRxIsrHandler(void);


extern _Bool SerialInit(Uint32 ulBaudRate);


extern void SerialReceiveMode( _Bool xRxEnable);
extern void SerialTransmitMode (_Bool xTxEnable);
extern _Bool SerialInit(Uint32 ulBaudRate);
extern _Bool SerialPutByte( char ucByte );
extern _Bool SerialGetByte( char * pucByte );



#endif
