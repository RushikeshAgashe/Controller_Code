/*
 * can.h
 *
 *  Created on: Jul 25, 2017
 *      Author: ragashe
 */

#ifndef INCLUDE_CAN_H_
#define INCLUDE_CAN_H_

#include "ModbusData.h"

void CAN_transmit(ModbusData *self);
extern ModbusData passedDataRequest, passedDataResponse;


#endif /* INCLUDE_CAN_H_ */
