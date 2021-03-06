extern FLT32 a,b;
extern LPFF LPF1[10];
extern UINT16 		da1 , da2 , da3 , da4 ;     
extern UINT16 		da1_type , da2_type , da3_type , da4_type ;     
extern FLT32 		da1_rng , da1_scale , da1_val , da1_data , da1_mid ;
extern FLT32 		da2_rng , da2_scale , da2_val , da2_data , da2_mid ;
extern FLT32 		da3_rng , da3_scale , da3_val , da3_data , da3_mid ;
extern FLT32 		da4_rng , da4_scale , da4_val , da4_data , da4_mid ;
extern UINT16 DAC_CH;
extern FLT32 DAC_scale;
extern FLT32 DifferenceHE;
extern FLT32 HTheta,HTheta_D0,HTheta_D1;
extern FLT32 ETheta,EThetaM;
extern FLT32 Theta,Theta_old,ThetaM,ThetaEstHall,ThetaEstHallError;
extern FLT32 ThetaEstH;
extern FLT32 IntegrationEstHall,Ki_EstHall;
extern FLT32 SpeedEstHall,SpeedEstHallRpm,AccSpdEstHall,SpeedEstHallOld, SpeedEstHall_m;
extern FLT32 Fc_SpdEstHall;
extern FLT32 ETheta_old;
extern FLT32 Vdc;
extern FLT32 Sin_Theta,Cos_Theta;
extern FLT32 Tsampcc,Tsampsc;
extern FLT32 fVF_freq,fVF_freq_set,fVF_freq_slope,fVF_freq_rad,fVF_theta;
extern FLT32 Rs,Ld,Lq,Ke,Integ_d,Integ_q,Kp_d_cc,Kp_q_cc,Ki_d_cc,Ki_q_cc;
extern FLT32 Wc_cc,Wc_spd;
extern FLT32 Icmd_target;
extern FLT32 SpeedCmdRpm,SpeedCmdRpm1,Integ_spd,Kp_sc,Ki_sc;

extern signed int ThetaQ15,ThetaMQ15;
extern UINT16 count,op_mode;
extern UINT16 HallSignal,HallSignalM;
extern signed int qep_count;
extern UINT16 InitFlag,IPM_FaultFlag,IPM_FaultCount,IPM_Status,Ireal_FaultCount;
extern UINT16 CurrentOffsetCount,Iu_offset,Iv_offset,Iw_offset,Vdc_offset;
extern signed int Iu,Iv,Iw, AD_Vdcf;
extern FLT32  fIu,fIv,fIw,fVdc,fCommand;
extern FLT32  fVdcfOld,fVdcf,lfVdc,Low_fvdc;
extern UINT16 AD_Iu,AD_Iv,AD_Iw,AD_Vdc,AD_Command;
extern signed int DutyA,DutyB,DutyC,Duty;//KBL
extern UINT16 count_pwm,count_start,count_pwm_set,count_pwm_clear;
extern FLT32 Vset,Vslope;
extern FLT32 speed_m,speed_e,speed_rpm;
extern FLT32 Id,Iq;
extern FLT32 Vd,Vq;
extern FLT32 AdjAngle;
extern UINT16 AngleControl;
extern FLT32 I_inv;//KBL
extern FLT32 AntiWindUp_Iqe,AntiGain,AntiWindUp_Vqe,AntiWindUp_Vde, AlphaCurr,AlphaVdc,AlphaTheta;//KBL
extern FLT32 lI_inv,I_invOld,I_invf;
extern UINT16 nDir;//KBL
extern ABC Vcmd,Vcmdn,Ireal;
extern DQS Vcmds,Ireals;
extern DQE Vcmde,Ireale,Icmde;
extern UINT16 aaa,bbb,ccc,ddd,eee,fff;
extern FLT32 kbl1,kbl2,kbl3,kbl4;
extern FLT32 lId,Id_Old,Idf;
extern FLT32 lIq,Iq_Old,Iqf;
extern FLT32 lTheta,Theta_Old,Thetaf;
extern UINT16 P_Status;
extern signed int PulseRPM;
extern FLT32 PulseRef;
extern UINT16 SpeedDown;
//extern FLT32 Control_Vd, Control_Vq,err_d,err_q;
//extern UINT16 RamfuncsLoadStart;
//extern UINT16 RamfuncsLoadEnd;
//extern UINT16 RamfuncsRunStart;

extern FLT32 Theta_Pre;
extern FLT32 ThetaInc;
extern FLT32 T,Freq_Ref;
extern UINT16 NumberOfPole;

extern UINT16 Motor_Add, Comm_Type, Comm_Speed;

extern char test_rx[2];
extern char test_tx[2];

extern void sci_debug_init(long bps);

extern void InitXINT1(Uint16 wPort,Uint16 wPolarity);
extern void InitXINT2(Uint16 keyPolarity);
extern void Gpio_select(void);
extern void InitSPI_DAC(void);
extern void InitEPWM();
extern void InitQEP(void);
extern void SetupADC(void);
extern void InitECAP1(void);
extern void InitECAP2(void);
extern void RunECAP1Timer(void);
extern void RunECAP2Timer(void);
extern void SetPWM(Uint16 Sector);//KBL

extern void LedControl(int nLedSelect,int nControl);
extern void RelayControl(int nControl);
extern void PWMControl(int nControl);
extern void OutputDAC(int nChannel, int nData);
extern void DA_OUT(void);
extern void BootStrap(void);
extern void EnableXINT1(void);
extern void EnableXINT2(void);
extern void DisableXINT1(void);
extern void DisableXINT2(void);
extern void SetCaptureHall(int nDirection);
extern void GateOff();

extern interrupt void xint1_isr(void);
extern interrupt void xint2_isr(void);
extern interrupt void epwm1_timer_isr(void);
extern interrupt void  adc_isr(void);

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);


//---------------------------------------------------------------------------
// External symbols created by the linker cmd file
// DSP28 examples will use these to relocate code from one LOAD location
// in either Flash or XINTF to a different RUN location in internal
// RAM
//extern unsigned int RamfuncsLoadStart;
//extern unsigned int RamfuncsLoadEnd;
//extern unsigned int RamfuncsRunStart;

//===========================================================================
// No more.
//===========================================================================
