/*
 * common.h
 *
 *  Created on: Jul 20, 2017
 *      Author: ragashe
 */

/* Headers for control.c */
#include "DSP2833x_Device.h"     // DSP2833x Header file Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"     // Device Header file and Examples Include File
#include "serial_api.h"
#include "string.h"
#include "ModbusSlave.h"

/* Headers for main.c */
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"
#include "string.h"
#include "ModbusSlave.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"

#include "can.h"

#ifndef ALLHEADERS_H_
#define ALLHEADERS_H_

#define DSP1        1
#define DSP2        2
#define DSP3        3
#define DSPtest     4


#define TOGGLE_DEBUG_BIT        (GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1)
#define SET_BIT                 (GpioDataRegs.GPBSET.bit.GPIO34 = 1)
#define CLEAR_BIT               (GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1)

#define CONTROLLER_ID           3

#if CONTROLLER_ID == 2
#define MBOX0_MSGID           0x15AC0001    //Tx - MBOX
#define MBOX1_MSGID           0x15AC0000    //Rx - MBOX
#endif

#if CONTROLLER_ID == 1
#define MBOX0_MSGID           0x15AC0001    //Tx - MBOX
#define MBOX1_MSGID           0x15AC0000    //Rx - MBOX
#endif

#if CONTROLLER_ID == 3
#define MBOX0_MSGID           0x15AC0000    //Tx - MBOX
#define MBOX1_MSGID           0x15AC0001    //Rx - MBOX
//#define MBOX2_MSGID           0x15AC0002    //Rx - MBOX
#endif

#define CAN_TEST                1
#define TXCOUNT                 101

extern volatile int RX_Flag;
extern volatile int pass_flag;
extern unsigned int *recBufferPointer;
extern unsigned int *txBufferPointer;

extern void debug_func();

//extern ModbusSlave mb;
//#define MB_SLAVE_ID             0x01  //Defined in ModbusSettings.h

#endif /* ALLHEADERS_H_ */
