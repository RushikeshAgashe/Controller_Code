/*
 * serial_api.h
 *
 *  Created on: 24-Mar-2015
 *      Author: JIMIT
 */

#ifndef SERIAL_API_H_
#define SERIAL_API_H_

#include "port.h"

#define RX_PACKET_SIZE	(0x02)

void SerialTransmit (char* tx_arr, char tx_arr_size);
void SerialReceive_Cb (void);
void SerialTransmit_Cb (void);
_Bool CheckAndRecvSerialData (char* serial_rx_ptr);

#endif /* SERIAL_API_H_ */
