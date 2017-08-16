#include "motor_control.h"



FLT32 Tsampcc=10e-5;








//===========================================================================
// No more.
//===========================================================================

FLT32 a,b;
LPFF LPF1[10];
UINT16          da1 = 0, da2 = 0 , da3 = 0, da4 = 0;
UINT16          da1_type = 0 , da2_type = 0 , da3_type = 0 , da4_type = 0;
FLT32           da1_rng = 0. , da1_scale = 0. , da1_val = 0. , da1_data = 0. , da1_mid = 0.;
FLT32           da2_rng = 0. , da2_scale = 0. , da2_val = 0. , da2_data = 0. , da2_mid = 0.;
FLT32           da3_rng = 0. , da3_scale = 0. , da3_val = 0. , da3_data = 0. , da3_mid = 0.;
FLT32           da4_rng = 0. , da4_scale = 0. , da4_val = 0. , da4_data = 0. , da4_mid = 0.;

FLT32 DifferenceHE;
FLT32 HTheta,HTheta_D0,HTheta_D1;
FLT32 ETheta,EThetaM;
FLT32 Theta_old,ThetaM,ThetaEstHall,ThetaEstHallError;
FLT32 ThetaEstH;
FLT32 IntegrationEstHall,Ki_EstHall;
FLT32 ETheta_old;
FLT32 SpeedEstHall,SpeedEstHallRpm,AccSpdEstHall,SpeedEstHallOld,SpeedEstHall_m;
FLT32 Fc_SpdEstHall;
FLT32 fVF_freq,fVF_freq_set,fVF_freq_slope,fVF_freq_rad,fVF_theta;
FLT32 Rs,Ld,Lq,Ke,Kp_d_cc,Kp_q_cc,Ki_d_cc,Ki_q_cc;
FLT32 Wc_cc,Wc_spd;
FLT32 Icmd_target;
FLT32 SpeedCmdRpm,SpeedCmdRpm1,Integ_spd,Kp_sc,Ki_sc;



FLT32 ThetaInc;
FLT32 T,Freq_Ref;


UINT16 DAC_CH;
FLT32 DAC_scale;
signed int ThetaQ15,ThetaMQ15;
UINT16 count;
UINT16 op_mode;
UINT16 HallSignal,HallSignalM;
signed int qep_count;
UINT16 InitFlag,IPM_FaultFlag,IPM_FaultCount,IPM_Status,Ireal_FaultCount;
UINT16 CurrentOffsetCount,Iu_offset,Iv_offset,Iw_offset;
signed int Iu,Iv,Iw;
FLT32  fIu,fIv,fIw,fVdc,fCommand;
FLT32  fVdcfOld,fVdcf,lfVdc,Low_fvdc;
UINT16 AD_Iu,AD_Iv,AD_Iw,AD_Vdc,AD_Command;
signed int DutyA,DutyB,DutyC;
UINT16 count_pwm=0,count_start = 0;
FLT32 Vset,Vslope;
FLT32 speed_m,speed_e,speed_rpm;
FLT32 Id,Iq;
FLT32 AdjAngle;
FLT32 kbl1,kbl2,kbl3,kbl4;
FLT32 lI_inv,I_invOld,I_invf;
FLT32 AlphaCurr,AlphaVdc,AlphaTheta;
UINT16 AngleControl;
UINT16 aaa,bbb,ccc,ddd,eee,fff;

UINT16 nDir;//KBL
FLT32 lId,Id_Old,Idf;
FLT32 lIq,Iq_Old,Iqf;
FLT32 lTheta,Theta_Old,Thetaf;
FLT32 AntiWindUp_Iqe,AntiWindUp_Vde,AntiWindUp_Vqe,AntiGain;
UINT16 P_Status;
signed int PulseRPM;
FLT32 PulseRef;
UINT16 SpeedDown;



//FLT32 Control_Vd, Control_Vq,err_d,err_q;
//struct I2CMSG *CurrentMsgPtr;
//unsigned int RamfuncsLoadStart;
//unsigned int RamfuncsLoadEnd;
//unsigned int RamfuncsRunStart;


UINT16 Motor_Add, Comm_Type, Comm_Speed;
char test_rx[2];
char test_tx[2];
//===========================================================================
// No more.
//===========================================================================
