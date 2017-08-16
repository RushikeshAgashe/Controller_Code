#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"

void LedControl(int nLedSelect,int nControl);
void RelayControl(int nControl);
void PWMControl(int nControl);
void OutputDAC(int nChannel, int nData);
void DA_OUT(void);
void BootStrap(void);
void EnableXINT1(void);
void EnableXINT2(void);
void DisableXINT1(void);
void DisableXINT2(void);
void SetCaptureHall(int nDirection);
void GateOff();
void RunECAP1Timer(void);
void RunECAP2Timer(void);

void RunECAP1Timer(void)
{
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;	//Run time stamp counter
}

void RunECAP2Timer(void)
{
   ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;	//Run time stamp counter
}

void SetCaptureHall(int nDirection)
{
	if(nDirection)
	{
		switch(HallSignal)
		{
			case 5 : InitXINT1(HALL3,BOTH);break;
			case 1 : InitXINT1(HALL2,BOTH); break;
			case 3 : InitXINT1(HALL1,BOTH);break;
			case 2 : InitXINT1(HALL3,BOTH); break;
			case 6 : InitXINT1(HALL2,BOTH);break;
			case 4 : InitXINT1(HALL1,BOTH); break;
			default: break;
		}
	}
	else
	{
		switch(HallSignal)
		{
			case 5 : InitXINT1(HALL1,BOTH);break;
			case 1 : InitXINT1(HALL3,BOTH); break;
			case 3 : InitXINT1(HALL2,BOTH);break;
			case 2 : InitXINT1(HALL1,BOTH); break;
			case 6 : InitXINT1(HALL3,BOTH);break;
			case 4 : InitXINT1(HALL2,BOTH); break;
			default: break;
		}
	}

	EnableXINT1();	
}


void GateOff()
{
	PWMControl(PWM_OFF);
	EPwm1Regs.CMPA.half.CMPA = 0;		//PWMC+
	EPwm2Regs.CMPA.half.CMPA = 7500;	//PWMC-
	EPwm3Regs.CMPA.half.CMPA = 0;		//PWMB+
	EPwm4Regs.CMPA.half.CMPA = 7500;	//PWMB-
	EPwm5Regs.CMPA.half.CMPA = 0;		//PWMA+
	EPwm6Regs.CMPA.half.CMPA = 7500;	//PWMA-
}

void BootStrap(void)
{
	PWMControl(PWM_ON);
	EPwm1Regs.CMPA.half.CMPA = 10;
	EPwm2Regs.CMPA.half.CMPA = 10;
	EPwm3Regs.CMPA.half.CMPA = 10;
	DELAY_US(1000000L);
	PWMControl(PWM_OFF);
}


void EnableXINT1(void)
{
   XIntruptRegs.XINT1CR.bit.ENABLE = 1;
}

void DisableXINT1(void)
{
   XIntruptRegs.XINT1CR.bit.ENABLE = 0;
}

void EnableXINT2(void)
{
   XIntruptRegs.XINT2CR.bit.ENABLE = 1;
}

void DisableXINT2(void)
{
   XIntruptRegs.XINT2CR.bit.ENABLE = 0;
}


void LedControl(int nLedSelect,int nControl)
{
	if(nControl == LED_OFF)
	{
		switch(nLedSelect)
		{
		case LED1:		GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; break;
		case LED2:		GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1; break;
		case LED3:		GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; break;
		case LED4:		GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1; break;
		case LED_ALL:	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
						GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
						GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;
						GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1; break;
		}
	}
	else
	{
		switch(nLedSelect)
		{
		case LED1:		GpioDataRegs.GPASET.bit.GPIO31 = 1; break;
		case LED2:		GpioDataRegs.GPBSET.bit.GPIO32 = 1; break;
		case LED3:		GpioDataRegs.GPBSET.bit.GPIO33 = 1; break;
		case LED4:		GpioDataRegs.GPBSET.bit.GPIO38 = 1; break;
		case LED_ALL:	GpioDataRegs.GPASET.bit.GPIO31 = 1;
						GpioDataRegs.GPBSET.bit.GPIO32 = 1;
						GpioDataRegs.GPBSET.bit.GPIO33 = 1;
						GpioDataRegs.GPBSET.bit.GPIO38 = 1; break;
		}
	}
}


void RelayControl(int nControl)
{
	GpioDataRegs.GPADAT.bit.GPIO27 = nControl;
}

void PWMControl(int nControl)
{
	if(nControl == PWM_ON) GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
	else GpioDataRegs.GPBSET.bit.GPIO49 = 1;
//	if(nControl == PWM_ON) GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;
//	else GpioDataRegs.GPASET.bit.GPIO13 = 1;

}

void OutputDAC(int nChannel, int nData)
{	
	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG);
	switch(nChannel)
	{
//		case 1: SpiaRegs.SPITXBUF = ((nData&0xFFF) | 0x1000);break;
//		case 2: SpiaRegs.SPITXBUF = ((nData&0xFFF) | 0x5000);break;
//		case 3: SpiaRegs.SPITXBUF = ((nData&0xFFF) | 0x9000);break;
//		case 4: SpiaRegs.SPITXBUF = ((nData&0xFFF) | 0xD000);break;
		case 1: SpiaRegs.SPITXBUF = ((nData&0x1FFF) | 0x0000);break;
		case 2: SpiaRegs.SPITXBUF = ((nData&0x1FFF) | 0x4000);break;
		case 3: SpiaRegs.SPITXBUF = ((nData&0x1FFF) | 0x8000);break;
		case 4: SpiaRegs.SPITXBUF = ((nData&0x1FFF) | 0xC000);break;
	}
	while(!SpiaRegs.SPISTS.bit.INT_FLAG);
	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
	SpiaRegs.SPIRXBUF;		
	GpioDataRegs.GPASET.bit.GPIO17 = 1;
}


void DA_OUT(void)
{	
//	OutputDAC(1,((SINT16)((da1_mid-da1_val) * da1_scale * 2./2.5) + 0x7FF));
//	OutputDAC(2,((SINT16)((da2_mid-da2_val) * da2_scale * 2./2.5) + 0x7FF));
//	OutputDAC(3,((SINT16)((da3_mid-da3_val) * da3_scale * 2./2.5) + 0x7FF));
//	OutputDAC(4,((SINT16)((da4_mid-da4_val) * da4_scale * 2./2.5) + 0x7FF));
	da1_data = (SINT16)(((da1_val-da1_mid) * da1_scale * 2./2.2) + 0x80);
	da2_data = (SINT16)(((da2_val-da2_mid) * da2_scale * 2./2.2) + 0x80);
//	da3_data = (SINT16)(((da3_val-da3_mid) * da3_scale * 2./2.2) + 0x80);
//	da4_data = (SINT16)(((da4_val-da4_mid) * da4_scale * 2./2.2) + 0x80);
	//GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
	//DELAY_US(1);
	//GpioDataRegs.GPASET.bit.GPIO17 = 1;
	if(da1_data > 255.0)	da1_data = 255.0;
	else if(da1_data<0)		da1_data = 0.;
	else 					da1_data = da1_data;
	if(da2_data > 255.0)	da2_data = 255.0;
	else if(da2_data<0)		da2_data = 0.;
	else					da2_data = da2_data;
//	if(da3_data > 255.0)	da3_data = 255.0;
//	else if(da3_data<0)		da3_data = 0.;
//	else					da3_data = da3_data;
//	if(da4_data > 255.0)	da4_data = 255.0;
//	else if(da4_data<0)		da4_data = 0.;
//	else					da4_data = da4_data;

	OutputDAC(1,(SINT16)da1_data<<5);
	OutputDAC(2,(SINT16)da2_data<<5);
//	OutputDAC(3,(SINT16)da3_data<<5);
//	OutputDAC(4,(SINT16)da4_data<<5);
}

//===========================================================================
// No more.
//===========================================================================

