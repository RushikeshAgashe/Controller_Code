#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"


void Gpio_select(void);
void InitEPWM();
void SetupADC(void);

void SetupADC(void)
{
	// For this example, set HSPCLK to SYSCLKOUT / 12 (12.5Mhz assuming 150Mhz SYSCLKOUT)
	EALLOW;
	SysCtrlRegs.HISPCP.all = 0x6;  // HSPCLK = SYSCLKOUT/12
	EDIS;

	InitAdc();
	
	// Configure ADC
	AdcRegs.ADCMAXCONV.all = 0x0006;       // Setup 3 conv's on SEQ1 (0x0005 corresponds to 6 conversions - 2 per converter)
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; // Setup ADCINA0 as 1st SEQ1 conv.
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1; // Setup ADCINA1 as 2nd SEQ1 conv.
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2; // Setup ADCINA2 as 3rd SEQ1 conv.
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3; // Setup ADCINA3 as 4th SEQ1 conv.
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4; // Setup ADCINA4 as 5th SEQ2 conv.
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5; // Setup ADCINA5 as 6th SEQ2 conv.
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6; // Setup ADCINA5 as 6th SEQ2 conv.

	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = 2;       // Select SOC from from CTR=PRD
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event
}


void Gpio_select(void)
{


	EALLOW;
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

	/* Configure ePWM-1 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B


    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM2B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)

	/* Configure ePWM-3 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
     
}
void InitEPWM()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    // Set timer period, 37.5M/(3750*2) = 20kHz
    EPwm1Regs.TBPRD = 3750;
    EPwm2Regs.TBPRD = 3750;
    EPwm3Regs.TBPRD = 3750;
    EPwm4Regs.TBPRD = 3750;
    EPwm5Regs.TBPRD = 3750;
    EPwm6Regs.TBPRD = 3750;

    EPwm1Regs.TBPHS.half.TBPHS =0;
    EPwm2Regs.TBPHS.half.TBPHS =0;
    EPwm3Regs.TBPHS.half.TBPHS =0;
    EPwm4Regs.TBPHS.half.TBPHS =0;
    EPwm5Regs.TBPHS.half.TBPHS =0;
    EPwm6Regs.TBPHS.half.TBPHS =0;

    // Setup TBCTL of EPWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;         // Enable phase loading
    EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm1Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT. TBCLK = 150M/4 = 37.5MHz
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM2
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm2Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM3
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm3Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM4
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm4Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM5
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm5Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm5Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM6
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm6Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm6Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        // Select INT on PRD event
    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1st event

    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm2Regs.ETSEL.bit.INTEN = 0;                  // Disable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm3Regs.ETSEL.bit.INTEN = 0;
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        // Select INT on PRD event
    EPwm4Regs.ETSEL.bit.INTEN = 0;                  // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1st event

    EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm5Regs.ETSEL.bit.INTEN = 0;                  // Disable INT
    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm6Regs.ETSEL.bit.INTEN = 0;
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;


    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm2Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm3Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm4Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm5Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm6Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm6Regs.CMPCTL.bit.LOADAMODE = 0;


    EPwm1Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm1Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm1Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm2Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm2Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm2Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm3Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm3Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm3Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm4Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm4Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm4Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm4Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm4Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing


    EPwm5Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm5Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm5Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm5Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm5Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm6Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm6Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm6Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm6Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    //
    //
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBRED = DEAD_TIME;
    EPwm1Regs.DBFED = DEAD_TIME;

    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBRED = DEAD_TIME;
    EPwm2Regs.DBFED = DEAD_TIME;
//
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBRED = DEAD_TIME;
    EPwm3Regs.DBFED = DEAD_TIME;

    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm4Regs.DBRED = DEAD_TIME;
    EPwm4Regs.DBFED = DEAD_TIME;
//
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm5Regs.DBRED = DEAD_TIME;
    EPwm5Regs.DBFED = DEAD_TIME;

    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm6Regs.DBRED = DEAD_TIME;
    EPwm6Regs.DBFED = DEAD_TIME;

//  EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm2Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm3Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm4Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm5Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm6Regs.AQSFRC.bit.RLDCSF = 3;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;

    EPwm1Regs.TBCTL.bit.SWFSYNC = 1;

}
/*
void InitEPWM()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    // Set timer period, 37.5M/(3750*2) = 20kHz
    EPwm1Regs.TBPRD = 3750;
    EPwm2Regs.TBPRD = 3750;
    EPwm3Regs.TBPRD = 3750;
    EPwm4Regs.TBPRD = 3750;
    EPwm5Regs.TBPRD = 3750;
    EPwm6Regs.TBPRD = 3750;

    EPwm1Regs.TBPHS.half.TBPHS =0;
    EPwm2Regs.TBPHS.half.TBPHS =0;
    EPwm3Regs.TBPHS.half.TBPHS =0;
    EPwm4Regs.TBPHS.half.TBPHS =0;
    EPwm5Regs.TBPHS.half.TBPHS =0;
    EPwm6Regs.TBPHS.half.TBPHS =0;

    // Setup TBCTL of EPWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;         // Enable phase loading
    EPwm1Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm1Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT. TBCLK = 150M/4 = 37.5MHz
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM2
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm2Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM3
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm3Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM4
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm4Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm4Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM5
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm5Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm5Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup TBCTL of EPWM6
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm6Regs.TBCTL.bit.PHSDIR = TB_UP;
    EPwm6Regs.TBCTL.bit.PRDLD= TB_SHADOW;
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        // Select INT on PRD event
    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1st event

    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm2Regs.ETSEL.bit.INTEN = 0;                  // Disable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm3Regs.ETSEL.bit.INTEN = 0;
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        // Select INT on PRD event
    EPwm4Regs.ETSEL.bit.INTEN = 0;                  // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1st event

    EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm5Regs.ETSEL.bit.INTEN = 0;                  // Disable INT
    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;

    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm6Regs.ETSEL.bit.INTEN = 0;
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;


    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm2Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm3Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm4Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm5Regs.CMPCTL.bit.LOADAMODE = 0;

    EPwm6Regs.CMPCTL.bit.SHDWBMODE = 0;             //Shadow mode
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = 0;             //Load on CTR=ZERO
    EPwm6Regs.CMPCTL.bit.LOADAMODE = 0;


    EPwm1Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm1Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm1Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm2Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm2Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm2Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm3Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm3Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm3Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm4Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm4Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm4Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm4Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm4Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing


    EPwm5Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm5Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm5Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm5Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm5Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm5Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing

    EPwm6Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR ;
    EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;      //Do nothing
    EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;        //Do nothing
    EPwm6Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;
    EPwm6Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;
    EPwm6Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;        //Do nothing
    EPwm6Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;        //Do nothing
    //
    //
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBRED = DEAD_TIME;
    EPwm1Regs.DBFED = DEAD_TIME;

    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBRED = DEAD_TIME;
    EPwm2Regs.DBFED = DEAD_TIME;
//
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBRED = DEAD_TIME;
    EPwm3Regs.DBFED = DEAD_TIME;

    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm4Regs.DBRED = DEAD_TIME;
    EPwm4Regs.DBFED = DEAD_TIME;
//
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm5Regs.DBRED = DEAD_TIME;
    EPwm5Regs.DBFED = DEAD_TIME;

    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm6Regs.DBRED = DEAD_TIME;
    EPwm6Regs.DBFED = DEAD_TIME;

//  EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm2Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm3Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm4Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm5Regs.AQSFRC.bit.RLDCSF = 3;
//  EPwm6Regs.AQSFRC.bit.RLDCSF = 3;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;

    EPwm1Regs.TBCTL.bit.SWFSYNC = 1;

}*/

void InitECAP1(void)
{
// Setup APWM mode on CAP1, set period and compare registers
   ECap1Regs.ECCTL2.bit.CAP_APWM = 1;	//Enable APWM mode
   ECap1Regs.CAP1 = 0xFFFFFFFF;			//Set Period value
   ECap1Regs.CAP2 = 600000L;				//Set Compare value
   ECap1Regs.ECCLR.all = 0x0FF;			//Clear pending interrupts
   ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 0; //Disable compare equal interrupt
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;	//Stop time stamp counter
}

void InitECAP2(void)
{
// Setup APWM mode on CAP1, set period and compare registers
   ECap2Regs.ECCTL2.bit.CAP_APWM = 1;	//Enable APWM mode
   ECap2Regs.CAP1 = 0xFFFFFFFF;			//Set Period value
   ECap2Regs.CAP2 = 600000L;				//Set Compare value
   ECap2Regs.ECCLR.all = 0x0FF;			//Clear pending interrupts
   ECap2Regs.ECEINT.bit.CTR_EQ_CMP = 0; //Disable compare equal interrupt
   ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;	//Stop time stamp counter
}

//===========================================================================
// No more.
//===========================================================================
