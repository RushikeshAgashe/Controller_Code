#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "motor_control.h"
#include "extern_variable.h"
#include "DSP2833x_Project.h"
#include "string.h"
#include "SPLL_3ph_SRF_IQ.h"
#include "math.h"



signed int Duty_A,Duty_B,Duty_C,Duty_L1=3750,Duty_L2=3750,Duty_L3=3750,Duty_DC,pwmc,output4[100];
FLT32 V_out=0,V_ref1=0, V_ref2=0,V_ref4=0, I_L1, I_L2;
FLT32 Ki_vc1,Kp_vc1,Integ_v1=0, Kp_ic1, Ki_ic1, Integ_i1=0;
FLT32 Ki_vc2,Kp_vc2,Integ_v2=0, Kp_ic2, Ki_ic2, Integ_i2=0;
FLT32 Ki_vc3,Kp_vc3,Integ_v3=0, Kp_ic3, Ki_ic3, Integ_i3=0;
FLT32 Ki_vc4,Kp_vc4,Integ_v4=0, Kp_ic4, Ki_ic4, Integ_i4=0;

FLT32 I_a,I_b,I_c;
FLT32 V_a,V_b,V_c;
FLT32 V_DCDC,I_DCDC;
FLT32 output1[100],output2[100],output3[100];

FLT32 err_v1=0, err_i1=0;
FLT32 err_v2=0, err_i2=0;
FLT32 err_v4=0, err_i4=0;

ABC Vgrid_Spll;
DQS Vgrids_Spll;
DQE	Vgride_Spll;
FLT32 err1_Spll=0;
FLT32 V1_Spll=0;
FLT32 Theta=0;
FLT32 Cos_Theta=1;
FLT32 Sin_Theta=0;
FLT32 Integ_Spll=0;
FLT32 Kp_Spll=0.05;
FLT32 Ki_Spll=2.5;
FLT32 fo=0;
FLT32 AlphaV,VfOld,Vf,lfVc,lfV,VOld,Vdc,V1;


FLT32 V_C2=0, V_2;
FLT32 pllk=0.361;
FLT32 Control_V1=0, Control_I1=0;
FLT32 Control_V2=0, Control_I2=0;
FLT32 Control_V4=0, Control_I4=0;
FLT32 Theta_tune=0.55;

// MPPT Converter Variables

FLT32 Control_V3, Control_I3;
FLT32 err_v3=0, err_i3=0;
FLT32 V_ref3=810;
FLT32 I_L3, V_C3=0, V_In3, P_3, prev_P_3 = 0;
UINT16 MPPT_counter = 0;



extern unsigned int RamfuncsLoadStart;
extern unsigned int RamfuncsLoadEnd;
extern unsigned int RamfuncsRunStart;

// Droop Control Variables

FLT32 Vdc_max1, Vdc_min1, Rd1;
FLT32 Idis_max1, Icharge_max1;


FLT32 Vdc_max2, Vdc_min2, Rd2;
FLT32 Idis_max2, Icharge_max2;


FLT32 Vdc_max4, Vdc_min4, Rd4;
FLT32 Idis_max4, Icharge_max4;

UINT16 V_1;
UINT16 I_1;
UINT16 I_2;
UINT16 V_3;
UINT16 I_3;
UINT16 V_In_pv;
UINT16 I_In_a;
UINT16 I_In_b;
UINT16 I_In_c;
UINT16 V_In_a;
UINT16 V_In_b;
UINT16 V_In_c;
UINT16 V_In_DCDC;
UINT16 I_In_DCDC;


FLT32 Theta_ref;

// Inverter Controller

FLT32 Kp_d_1 = 3;
FLT32 Kp_q_1 = 3;
FLT32 Ki_d_1 = 6;
FLT32 Ki_q_1 = 6;

FLT32 Kp_d_2 = 0.8;
FLT32 Ki_d_2 = 2.5;

FLT32 Vd_ref,Vq_ref,V_ref,Vd_ref_r,Vq_ref_r,Theta_ref,omega=TWO_PI*60,L_v,Id_ref_r=0.5,Iq_ref_r;
FLT32 err_d_1=0,err_q_1=0,Integ_d_1=0,Integ_q_1=0,Vd,Vq;
FLT32 err_d_2=0,err_q_2=0,Integ_d_2=0,Integ_q_2=0;
FLT32 err_PD=0,err_QD=0,Integ_PD=0,Integ_QD=0;

FLT32 err_d=0,err_q=0,Integ_d=0,Integ_q=0,Vd,Vq;
FLT32 err_dc=0, Integ_dc=0;


FLT32 Control_Vd=0, Control_Vq=0;

FLT32 Control_Vd_1, Control_Vq_1;
FLT32 Control_Vd_2, Control_Vq_2;



ABC Vcmd,Vcmdn,Ireal,Vgrid;
DQS Vcmds,Ireals,Vgrids;
DQE Vcmde,Ireale,Icmde,Vgride;

int k=0,PWM_Counter,PWM_Count,Sample_Rate=1000;

int ISR_FREQ=10000;
FLT32 GRID_FREQ=60;
int cap_count=0,start_capture=0,ccount=0;
SPLL_3ph_SRF_IQ spll1;

interrupt void epwm1_timer_isr(void);
interrupt void  adc_isr(void);

DQS Is_abc2dqs(ABC *abc);
DQE Is_dqs2dqe(DQS *dqs, FLT32 COSTH, FLT32 SINTH);
DQS Is_dqe2dqs(DQE *dqe, FLT32 Theta_Q15_Ori);
ABC Is_dqs2abc(DQS *dqs);

void S_PLL(void);
void Is_SVPWM(void);
void InitVariable(void);
void SPWM_3ph(void);
void Three_phase_Inverter_Current_Control(void);
void Three_phase_Inverter_Voltage_Control(void);
void main(void)


{

	InitSysCtrl();
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
	InitFlash();
	Gpio_select();	  	
	InitPieCtrl();  // Disable PIE and clear PIEIER and PIEIFR registers
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();  // Initialize and enable PIE vector table


	InitEPWM();

	AlphaV = lpfAlpha(10000., 10.);
	VfOld=0.,Vf=0.;

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

}



// Second Stage

void CurrentControl_1(void)
{


    if( Control_V1 > 130 ) {

        Control_V1=130;

    }
    else if(Control_V1 < -130) {

        Control_V1=-130;

    }

    else  {

        Control_V1 = Control_V1;

    }


    Kp_ic1=1.5;
    Ki_ic1=3.5;
    err_i1 = Control_V1-I_L1;

    Integ_i1 = (Integ_i1 + Ki_ic1*Tsampcc*err_i1);
    Control_I1 = Kp_ic1*err_i1 + Integ_i1 ;

}

void VoltageControl_1(void)
{

    // Virtual Resistance Calculator
    Vdc_max1=387.5;
    Vdc_min1=372.5;
    Idis_max1=130;
    Icharge_max1=130;
    Rd1= (Vdc_max1-Vdc_min1)/(Idis_max1+Icharge_max1);


    V_ref1=(380-Rd1*I_L1);
    Kp_vc1=0.04;
    Ki_vc1=2.5;
    err_v1 = V_ref1-V_out;

    Integ_v1 = (Integ_v1 + Ki_vc1*Tsampcc*err_v1);
//
    if( Integ_v1 > 132 ) {

        Integ_v1 = 132;

        }
        else if(Integ_v1 < -132) {

            Integ_v1 = -132;

        }

        else  {

            Integ_v1 = Integ_v1;

        }

    Control_V1 = Kp_vc1*err_v1+Integ_v1;

}


void PWM_Duty(void)
{

	Duty_DC =(signed int)3750*(Control_I1/100);

}



void Is_SVPWM(void)
{

	EPwm1Regs.CMPA.half.CMPA = Duty_L1;      //PWM1A
	EPwm1Regs.CMPB=Duty_L2;                  //PWM1B
	EPwm2Regs.CMPA.half.CMPA = Duty_L3;      //PWM2A
    EPwm2Regs.CMPB=Duty_DC;                  //PWM2B

}



void SPWM_3ph(void)

{

	Vcmds = Is_dqe2dqs(&Vcmde,Theta);
	Vcmd = Is_dqs2abc(&Vcmds);


	Duty_L1 =(signed int)7000*(0.5-Vcmd.a/V_DCDC);
	Duty_L2 =(signed int)7000*(0.5-Vcmd.b/V_DCDC);
	Duty_L3 =(signed int)7000*(0.5-Vcmd.c/V_DCDC);

}


void Three_phase_Inverter_Voltage_Control(void)
{

    err_dc =  1300 - V_DCDC;

    Integ_dc = (Integ_dc + Ki_d_2*Tsampcc*err_dc);

    Icmde.de = Kp_d_2*err_dc + Integ_dc ;


}


void Three_phase_Inverter_Current_Control(void)
{


	err_d =  Ireale.de - Icmde.de;
	err_q =  Ireale.qe - 0;


	Integ_d = (Integ_d + Ki_d_1*Tsampcc*err_d);


	Control_Vd = Kp_d_1*err_d + Integ_d ;


	Integ_q = (Integ_q + Ki_q_1*Tsampcc*err_q);

	Control_Vq = Kp_q_1*err_q + Integ_q;


	if (Control_Vq > (2*V_DCDC/5))
	{
		Control_Vq=2*V_DCDC/5;
	}
	if (Control_Vq < (-2*V_DCDC/5))
	{
		Control_Vq=-2*V_DCDC/5;
	}

	if (Control_Vd > (2*V_DCDC/5))
	{
		Control_Vd=2*V_DCDC/5;
	}
	if (Control_Vd < (-2*V_DCDC/5))
	{
		Control_Vd=-2*V_DCDC/5;
	}


	  Vcmde.qe= Vd + Control_Vq;
	  Vcmde.de= Vq + Control_Vd;

}



DQS Is_abc2dqs(ABC *abc)
{
	DQS Temp;
	Temp.ds = (2./3.)*(abc->a   -abc->b*0.5-abc->c*0.5);
	Temp.qs = ONE_OVER_ROOT3*(abc->b-abc->c);
	return Temp;
}

DQE Is_dqs2dqe(DQS *dqs, FLT32 COSTH, FLT32 SINTH)
{
	DQE Temp;
	Temp.de = COSTH * dqs->ds+SINTH*dqs->qs;
	Temp.qe = -SINTH *dqs->ds+COSTH*dqs->qs;
	return Temp;
}

DQS Is_dqe2dqs(DQE *dqe, FLT32 Theta_Q15_Ori)
{
	DQS		Temp;
	FLT32	Theta_Off=0.,SinTheta_Off=0.,CosTheta_Off=0.;

	Theta_Off = Theta_Q15_Ori;
	SinTheta_Off = sin(Theta_Off);
	CosTheta_Off = cos(Theta_Off);
	Temp.ds  = CosTheta_Off *dqe->de-SinTheta_Off*dqe->qe;
	Temp.qs  = SinTheta_Off *dqe->de+CosTheta_Off*dqe->qe;
	return Temp;
}

ABC Is_dqs2abc(DQS *dqs)
{
	ABC	Temp;
	Temp.a =  dqs->ds;
	Temp.b = -0.5*(dqs->ds -(1.7)*(dqs->qs));
	Temp.c = -(Temp.a+Temp.b);
	return Temp;
}


// Interrupt routines uses in this example:
interrupt void epwm1_timer_isr(void)
{

	// Clear INT flag for this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

	// Acknowledge this interrupt to receive more interrupts from group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void  adc_isr(void)
{

	PWM_Count++;
	V_1  = AdcMirror.ADCRESULT0;
	V_out = ((FLT32)(V_1-2047.5)*1000)/(2047.5); //

	I_1  = AdcMirror.ADCRESULT1;
	I_L1 = ((FLT32)(I_1-2047.5)*150)/(2047.5); //


	I_In_a = AdcMirror.ADCRESULT5;
	I_a = ((FLT32)(I_In_a-2047.5)*100)/(2047.5); //

	I_In_b = AdcMirror.ADCRESULT6;
	I_b = ((FLT32)(I_In_b-2047.5)*100)/(2047.5); //

	I_In_c = AdcMirror.ADCRESULT7;
	I_c = ((FLT32)(I_In_c-2047.5)*100)/(2047.5); //


	V_a = 3*(float)(AdcMirror.ADCRESULT8)/4096;
	V_b = 3*(float)(AdcMirror.ADCRESULT9)/4096;
	V_c = 3*(float)(AdcMirror.ADCRESULT10)/4096;


	Vgrid.a=(V_a-1.52)/0.003;
	Vgrid.b=(V_b-1.52)/0.003;
	Vgrid.c=(V_c-1.52)/0.003;



	V_In_DCDC = AdcMirror.ADCRESULT11;
	V_DCDC = ((FLT32)(V_In_DCDC-2047.5)*1500)/(2047.5); //

	I_In_DCDC = AdcMirror.ADCRESULT12;
	I_DCDC = ((FLT32)(I_In_DCDC-2047.5)*150)/(2047.5); //

	lfV = lfV + AlphaV*(VfOld + V_DCDC - 2*Vf);
	VOld = Vf;
	Vf = lfV;

	Vdc=lfV;

	//PLL

	Vgrid_Spll.a = (V_a-1.52)*pllk;
	Vgrid_Spll.b = (V_a-1.52)*pllk;
	Vgrid_Spll.c = (V_c-1.52)*pllk;
	S_PLL();

	Ireal.a = I_a;
	Ireal.b = I_b;
	Ireal.c = I_c;

	Ireals = Is_abc2dqs(&Ireal);
	Ireale = Is_dqs2dqe(&Ireals, Cos_Theta, Sin_Theta);
	Id = Ireale.de;
	Iq = Ireale.qe;


	Vgrids = Is_abc2dqs(&Vgrid);
	Vgride = Is_dqs2dqe(&Vgrids, Cos_Theta, Sin_Theta);
	Vd = Vgride.de;
	Vq = Vgride.qe;



	ccount++;
	if(start_capture==1 && ccount==5)
	{
		output1[cap_count]=Vgrid.a;
		output2[cap_count]=Theta;
//		output3[cap_count]=Duty_L1;

		cap_count++;
		ccount=0;
		if(cap_count==100)
		{
			cap_count=0;
			start_capture=0;
		}

	}

    Three_phase_Inverter_Voltage_Control();
	Three_phase_Inverter_Current_Control();
	SPWM_3ph();

    VoltageControl_1();
    CurrentControl_1();
    PWM_Duty();

	Is_SVPWM();


	PWM_Count=0;
	//    }


	// Reinitialize for next ADC sequence
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}


void S_PLL(void)
{


	Vgrids_Spll = Is_abc2dqs(&Vgrid);
	Vgride_Spll = Is_dqs2dqe(&Vgrids_Spll, Cos_Theta, Sin_Theta);

	err1_Spll=-Vgride_Spll.qe;
	Integ_Spll=Integ_Spll+err1_Spll*Tsampcc*Ki_Spll;
	V1_Spll=Kp_Spll*err1_Spll+Integ_Spll;
	Theta=Theta+(V1_Spll+TWO_PI*GRID_FREQ )*Tsampcc;
	fo=(V1_Spll+TWO_PI*GRID_FREQ)/TWO_PI;
	if(Theta>TWO_PI)
	{
		Theta=Theta-TWO_PI;
	}

	Cos_Theta=cos(Theta);
	Sin_Theta=sin(Theta);

}

void InitVariable(void)
{
	// Tsampcc=0.0001;

}

void SPLL_3ph_SRF_IQ_init(int Grid_freq,float DELTA_T, SPLL_3ph_SRF_IQ *spll_obj)
{
	spll_obj->v_q[0]=0;
	spll_obj->v_q[1]=0;
	spll_obj->ylf[0]=0;
	spll_obj->ylf[1]=0;
	spll_obj->fo=0;
	spll_obj->fn=Grid_freq;
	spll_obj->theta[0]=0;
	spll_obj->theta[1]=0;
	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=223.4194;
	spll_obj->lpf_coeff.B1_lf=-220.901;
	spll_obj->lpf_coeff.A1_lf=-1;
	spll_obj->delta_T=DELTA_T;
}
void SPLL_3ph_SRF_IQ_FUNC(SPLL_3ph_SRF_IQ *spll_obj)
{
	//update v_q[0] before calling the routine
	//---------------------------------//
	// Loop Filter //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1]+(spll_obj->lpf_coeff.B0_lf*spll_obj->v_q[0])+(spll_obj->lpf_coeff.B1_lf*spll_obj->v_q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];
	spll_obj->v_q[1]=spll_obj->v_q[0];
	spll_obj->ylf[0]=(spll_obj->ylf[0]>(200.0))?(200.0):spll_obj->ylf[0];
	//---------------------------------//
	// VCO //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];
	spll_obj->theta[0]=spll_obj->theta[1]+(spll_obj->fo*spll_obj->delta_T)*(2*3.1415926);
	if(spll_obj->theta[0]>(2*3.1415926))
		spll_obj->theta[0]=spll_obj->theta[0]-(2*3.1415926);
	spll_obj->theta[1]=spll_obj->theta[0];
}


//===========================================================================
// No more.
//===========================================================================
