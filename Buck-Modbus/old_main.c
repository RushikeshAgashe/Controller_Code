#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"
#include "string.h"
#include "ModbusSlave.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"

ModbusSlave mb;

void InitVariable(void);

void check_modbus_query(void){
    mb = construct_ModbusSlave();
    mb.holdingRegisters.dummy1 = 0xF;
    while(1) {
        mb.loopStates(&mb);
    }
}
void main(void)
{
    InitSysCtrl();
	Gpio_select();	  	
	InitPieCtrl();  // Disable PIE and clear PIEIER and PIEIFR registers
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();  // Initialize and enable PIE vector table
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
	InitEPWM();

	EALLOW;
	PieVectTable.EPWM1_INT = &epwm1_timer_isr;	
	PieVectTable.ADCINT = &adc_isr;

	EDIS; 
	
	SetupADC();	 

	IER |= M_INT1;
	IER |= M_INT3;
	
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;	//EPWM1
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	//ADC
	
	EINT;	
	check_modbus_query();
}
void InitVariable(void)
{
   // Tsampcc=0.0001;

}



//===========================================================================
// No more.
//===========================================================================
