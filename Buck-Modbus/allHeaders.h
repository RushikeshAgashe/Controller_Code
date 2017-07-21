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

#ifndef ALLHEADERS_H_
#define ALLHEADERS_H_

#define DSP1        1
#define DSP2        2
#define DSP3        3
#define DSPtest     4

#define CAN_TEST                1
#define TXCOUNT                 100
#define CONTROLLER_ID           3
//#define MB_SLAVE_ID             0x01  //Defined in ModbusSettings.h


#endif /* ALLHEADERS_H_ */
