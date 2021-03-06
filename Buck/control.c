#include "DSP2833x_Device.h"     // DSP2833x Header file Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"     // Device Header file and Examples Include File
#include "serial_api.h"
#include "string.h"

FLT32 Duty_A,Duty_B,Duty_C;
FLT32 V_out=0,V_ref1=0, V_ref2=0, I_L1, I_L2;
FLT32 Ki_vc1,Kp_vc1,Integ_v1=0, Kp_ic1, Ki_ic1, Integ_i1=0;
FLT32 Ki_vc2,Kp_vc2,Integ_v2=0, Kp_ic2, Ki_ic2, Integ_i2=0;
FLT32 Ki_vc3,Kp_vc3,Integ_v3=0, Kp_ic3, Ki_ic3, Integ_i3=0;

FLT32 err_v1=0, err_i1=0;
FLT32 err_v2=0, err_i2=0;

FLT32 V_C2=0, V_2;

FLT32 Control_V1=0, Control_I1;
FLT32 Control_V2=0, Control_I2;

// MPPT Converter Variables

FLT32 Control_V3, Control_I3;
FLT32 err_v3=0, err_i3=0;
volatile FLT32 V_ref3=800;
volatile FLT32 I_L3, V_C3=0, V_In3, P_3, avg_P_3, sum_P_3 = 0, prev_P_3 = 0, diff = 0, Battery1_SoC_out=0, Battery2_SoC_out=0, AverageSoC;
volatile UINT16 MPPT_counter = 0;


// Droop Control Variables

FLT32 Vdc_max1, Vdc_min1;
FLT32 Idis_max1, Icharge_max1;


FLT32 Vdc_max2, Vdc_min2;
FLT32 Idis_max2, Icharge_max2;

UINT16 V_1;
UINT16 I_1;
UINT16 I_2;
UINT16 V_3;
UINT16 I_3;
UINT16 V_In_pv;
int buff_size = 10.0;
FLT32 buff_size_f = 10.0;
UINT16 Battery1_SoC, Battery1_SoC_buffer[10]= {0};
UINT16 Battery2_SoC, Battery2_SoC_buffer[10]= {0};
unsigned int Battery1_SoC_f;
unsigned int Battery2_SoC_f;


//interrupt void xint1_isr(void);
//interrupt void xint2_isr(void);
interrupt void epwm1_timer_isr(void);
interrupt void  adc_isr(void);

DQS Is_abc2dqs(ABC *abc);
DQE Is_dqs2dqe(DQS *dqs, FLT32 COSTH, FLT32 SINTH);
DQS Is_dqe2dqs(DQE *dqe, FLT32 Theta_Q15_Ori);
ABC Is_dqs2abc(DQS *dqs);
void Is_SVPWM(void);


// Battery Converter 1

void CurrentControl_1(void)
{

    Kp_ic1=5;
    Ki_ic1=8;
    err_i1 = Control_V1-I_L1;

   Integ_i1 = (Integ_i1 + Ki_ic1*Tsampcc*err_i1);
   Control_I1 = Kp_ic1*err_i1 + Integ_i1 ;

}

void VoltageControl_1(void)
{
    FLT32 beta;
    static FLT32 Rd1 = 0.25;
    static int count=0;
    enum Flags{CHARGE,DISCHARGE};

    static enum Flags flag;

    beta = AverageSoC/Battery1_SoC_out;
    if(I_L1 < 0 && I_L2 < 0){
            if(flag == CHARGE)
                Rd1 = Rd1 / beta;
            else if (flag == DISCHARGE){
                count --;           // This is the hysteresis period for which the code must
                if (count < -10000){   // wait, until we are sure that the batteries are
                    flag = CHARGE;  // charging.
                    count = 0;
                }
            }
        }
        else if(I_L1 > 0 && I_L2 > 0){
            if(flag == DISCHARGE)
                Rd1 = Rd1 * beta;
            else if (flag == CHARGE){
                count ++;           // This is the hysteresis period for which the code must
                if (count > 10000){   // wait, until we are sure that the batteries are
                    flag = DISCHARGE;   // discharging.
                    count = 0;
                }
            }
        }
    if (Rd1 > 0.5)
        Rd1 = 0.5;
    else if (Rd1 < 0.25)
        Rd1 = 0.25;
    else
        Rd1 = Rd1;

	V_ref1=(380-Rd1*I_L1);
	Kp_vc1=0.01;
	Ki_vc1=2;
	err_v1 = V_ref1-V_out;

	Integ_v1 = (Integ_v1 + Ki_vc1*Tsampcc*err_v1);
	Control_V1 = Kp_vc1*err_v1+Integ_v1;

}

// Battery Converter 2

void CurrentControl_2(void)
{

        Kp_ic2=5;
        Ki_ic2=8;
        err_i2 = Control_V2-I_L2;

       Integ_i2 = (Integ_i2 + Ki_ic2*Tsampcc*err_i2);
       Control_I2 = Kp_ic2*err_i2 + Integ_i2;

}

void VoltageControl_2(void)
{
    FLT32 beta;
    static FLT32 Rd2 = 0.25;
    static int count=0;
    enum Flags{CHARGE,DISCHARGE};

    static enum Flags flag;
//    Virtual Resistance Calculator
//    Vdc_max2=400;
//    Vdc_min2=360;
//    Idis_max2=80;
//    Icharge_max2=80;
//    Rd2= (Vdc_max2-Vdc_min2)/(Idis_max2+Icharge_max2);
    beta = AverageSoC/Battery2_SoC_out;

    if(I_L1 < 0 && I_L2 < 0){
        if(flag == CHARGE)
            Rd2 = Rd2 / beta;
        else if (flag == DISCHARGE){
            count --;           // This is the hysteresis period for which the code must
            if (count < -10000){   // wait, until we are sure that the batteries are
                flag = CHARGE;  // charging.
                count = 0;
            }
        }
    }
    else if(I_L1 > 0 && I_L2 > 0){
        if(flag == DISCHARGE)
            Rd2 = Rd2 * beta;
        else if (flag == CHARGE){
            count ++;           // This is the hysteresis period for which the code must
            if (count > 10000){   // wait, until we are sure that the batteries are
                flag = DISCHARGE;   // discharging.
                count = 0;
            }
        }
    }

    if (Rd2 > 0.5)
        Rd2 = 0.5;
    else if (Rd2 < 0.25)
        Rd2 = 0.25;
    else
        Rd2 = Rd2;

    V_ref2=(380-Rd2*I_L2);
    Kp_vc2=0.01;
    Ki_vc2=2;
    err_v2 = V_ref2-V_out;

    Integ_v2 = (Integ_v2 + Ki_vc2*Tsampcc*err_v2);
    Control_V2 = Kp_vc2*err_v2 + Integ_v2;

}

// Buck MPPT Converter

void CurrentControl_3(void)
{

    Kp_ic3=3;
    Ki_ic3=8;
    err_i3 = Control_V3-I_L3;

   Integ_i3 = (Integ_i3 + Ki_ic3*Tsampcc*err_i3);
   Control_I3 = Kp_ic3*err_i3 + Integ_i3;

}

void VoltageControl_3(void)
{

   // V_ref3=25; Moved to Init.c
    Kp_vc3=0.5;
    Ki_vc3=1.5;
    err_v3 = V_In3-V_ref3;

    Integ_v3 = (Integ_v3 + Ki_vc3*Tsampcc*err_v3);
    Control_V3 = Kp_vc3*err_v3 + Integ_v3;

}

void MPPT(FLT32 P_3)
{
    enum Directions{POSITIVE, NEGATIVE};
    volatile static enum Directions direction  = NEGATIVE;
    static int starter_bump = 1;
    if (starter_bump ==1 ){
        V_ref3 = V_ref3 + 50;
        starter_bump = 0;
        return;
    }
    diff = P_3 - prev_P_3;
    switch(direction){
    case POSITIVE:
        if (P_3 > prev_P_3){
            V_ref3 = V_ref3 + 2;
            direction = POSITIVE;
        }
        else if (P_3 < prev_P_3){
            V_ref3 = V_ref3 - 2;
            direction = NEGATIVE;
        }

    case NEGATIVE:
        if (P_3 < prev_P_3){
            V_ref3 = V_ref3 + 2;
            direction = POSITIVE;
        }
        else if (P_3 > prev_P_3){
            V_ref3 = V_ref3 - 2;
            direction = NEGATIVE;
        }
    }
    prev_P_3 = P_3;
}
void PWM_Duty(void)
{

 Duty_A =(signed int)3750*(Control_I1/100);
 Duty_B =(signed int)3750*(Control_I2/100);
 Duty_C =(signed int)3750*(Control_I3/100);


}



void Is_SVPWM(void)
{

	EPwm1Regs.CMPA.half.CMPA    = Duty_A;		//PWM1A
	EPwm1Regs.CMPB              = Duty_B;      //PWM1B
	//EPwm2Regs.CMPA.half.CMPA   = Duty_B;		//PWM2A
	EPwm2Regs.CMPA.half.CMPA   = Duty_C;        //PWM2A
	//EPwm3Regs.CMPA.half.CMPA    = Duty_C;		//PWM3A

}


// Interrupt routines uses in this example:
interrupt void epwm1_timer_isr(void)
{

	// Clear INT flag for this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

	// Acknowledge this interrupt to receive more interrupts from group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

unsigned int filter_SoC(UINT16 SoC, UINT16 SoC_buffer[buff_size])
{
    int i;
    FLT32 SoC_add=0.0;
    for (i=0;i<buff_size-1;i++){
        SoC_buffer[i]=SoC_buffer[i+1];
        SoC_add += SoC_buffer[i]/buff_size_f;
    }
    SoC_buffer[buff_size-1] = SoC;
    SoC_add += SoC_buffer[buff_size-1]/buff_size_f;
    return ((unsigned int)SoC_add);
}


interrupt void  adc_isr(void)
{

    V_1  = AdcMirror.ADCRESULT0;
    V_out = ((FLT32)(V_1-2047.5)*1000)/(2047.5); //

    I_1  = AdcMirror.ADCRESULT1;
    I_L1 = ((FLT32)(I_1-2047.5)*150)/(2047.5); //

    I_2  = AdcMirror.ADCRESULT2;
    I_L2 = ((FLT32)(I_2-2047.5)*150)/(2047.5); //

    V_3 = AdcMirror.ADCRESULT3;
    V_C3 = ((FLT32)(V_3-2047.5)*1000)/(2047.5); //

    I_3 = AdcMirror.ADCRESULT3;
    I_L3 = ((FLT32)(I_3-2047.5)*100)/(2047.5); //

    V_In_pv = AdcMirror.ADCRESULT4;
    V_In3 = ((FLT32)(V_In_pv-2047.5)*1100)/(2047.5); //

    Battery1_SoC  = AdcMirror.ADCRESULT5;
    Battery1_SoC_f  = filter_SoC(Battery1_SoC,Battery1_SoC_buffer);
    //Battery1_SoC_f = Battery1_SoC;
    Battery1_SoC_out = ((FLT32)(Battery1_SoC_f-2047.5)*500)/(2047.5); //

    Battery2_SoC  = AdcMirror.ADCRESULT6;
    Battery2_SoC_f  = filter_SoC(Battery2_SoC,Battery2_SoC_buffer);
    //Battery2_SoC_f = Battery2_SoC;
    Battery2_SoC_out = ((FLT32)(Battery2_SoC_f-2047.5)*500)/(2047.5); //

    AverageSoC = (Battery1_SoC_out + Battery2_SoC_out)/2;
    VoltageControl_1();
    CurrentControl_1();

    VoltageControl_2();
    CurrentControl_2();

    //P_3 = V_C3*V_C3;
    P_3 = V_out*I_L3;
    MPPT_counter++;
    if (MPPT_counter < 50000)
        sum_P_3 += P_3;
    if (MPPT_counter > 50000){
       avg_P_3 = sum_P_3 / 50000;
        MPPT(avg_P_3);
       MPPT_counter = 0;
       sum_P_3 = 0;
   }

   VoltageControl_3();
   CurrentControl_3();

    PWM_Duty();

	Is_SVPWM();


// Reinitialize for next ADC sequence
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

//===========================================================================
// No more.
//===========================================================================
