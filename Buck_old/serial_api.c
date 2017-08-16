/*
 * serial_api.c
 *
 *  Created on: 24-Mar-2015
 *      Author: JIMIT
 */

#include "serial_api.h"


static _Bool rx_flag = FALSE;
char rx_buff[RX_PACKET_SIZE];

static int tx_len = 0;
static int tx_ctr = 0;
static char* tx_buff_ptr;

//USER Function:
//Transmits the given number of bytes over UART.
void SerialTransmit (char* tx_arr, char tx_arr_size)
{
	SerialTransmitMode(TRUE);
	tx_len = tx_arr_size;
	tx_buff_ptr = tx_arr;
	tx_ctr++;
	//Transmit the first byte manually, thereafter handled by interrupts
	SerialPutByte(tx_arr[0]);


}
// Call back function from Rx ISR
void SerialReceive_Cb (void)
{
	static int rx_ctr = 0;
	if (rx_ctr == 0)
	{
		rx_flag = FALSE;
	}
	SerialGetByte(&(rx_buff[rx_ctr]));
	rx_ctr ++;
	if (rx_ctr >= RX_PACKET_SIZE )
	{
		rx_ctr = 0;
		rx_flag = TRUE;
	}
}

//Call back function from Tx ISR
void SerialTransmit_Cb (void)
{
	if (tx_ctr >= tx_len)
	{
		//All bytes transmitted, so disable Tx to avoid further interrupts
		SerialTransmitMode(FALSE);
		tx_ctr = 0;
	}
	else
	{
		SerialPutByte(tx_buff_ptr[tx_ctr]);
		tx_ctr++;
	}

}

//User Function:
// Check if the RX_PACKET_SIZE no. of bytes have been received. If so, return TRUE and fill the
// serial_rx_ptr buffer with received data.
//Else, return FALSE
// Interrupts are disabled so that no new data is received during transfer of data to the application/user

_Bool CheckAndRecvSerialData (char* serial_rx_ptr)
{
	_Bool ret_val = FALSE;
	ENTER_CRITICAL_SECTION();
	if (rx_flag == TRUE)
	{
		rx_flag = FALSE;
		memcpy(serial_rx_ptr, rx_buff,RX_PACKET_SIZE );
		ret_val = TRUE;
	}
	EXIT_CRITICAL_SECTION();
	return ret_val;
}


