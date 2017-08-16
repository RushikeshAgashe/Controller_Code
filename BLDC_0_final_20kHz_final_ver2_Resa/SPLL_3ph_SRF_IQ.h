#ifndef SPLL_3ph_SRF_IQ_H_
#define SPLL_3ph_SRF_IQ_H_

#define SPLL_SRF_Q _IQ21
#define SPLL_SRF_Qmpy _IQ21mpy

//*********** Structure Definition ********//
typedef struct{
	FLT32	B1_lf;
	FLT32	B0_lf;
	FLT32	A1_lf;
}SPLL_3ph_SRF_IQ_LPF_COEFF;

typedef struct{
	FLT32 v_q[2];
	FLT32 ylf[2];
	FLT32 fo; // output frequency of PLL
	FLT32 fn; //nominal frequency
	FLT32 theta[2];
	FLT32 delta_T;
	SPLL_3ph_SRF_IQ_LPF_COEFF lpf_coeff;
}SPLL_3ph_SRF_IQ;

//*********** Function Declarations *******//
void SPLL_3ph_SRF_IQ_init(int Grid_freq,float DELTA_T, SPLL_3ph_SRF_IQ *spll);
void SPLL_3ph_SRF_IQ_FUNC(SPLL_3ph_SRF_IQ *spll_obj);

//*********** Macro Definition ***********//
#define SPLL_3ph_SRF_IQ_MACRO(spll_obj)																													\
	/*update v_q[0] before calling the routine*/																										\
	/* Loop Filter                     */																												\
	spll_obj.ylf[0]=spll_obj.ylf[1]+(spll_obj.lpf_coeff.B0_lf*spll_obj.v_q[0])+(spll_obj.lpf_coeff.B1_lf*spll_obj.v_q[1]);	\
	spll_obj.ylf[1]=spll_obj.ylf[0];																													\
	spll_obj.v_q[1]=spll_obj.v_q[0];																													\
	spll_obj.ylf[0]=(spll_obj.ylf[0]>(200.0))?(200.0):spll_obj.ylf[0];																\
	/* VCO                             */																												\
	spll_obj.fo=spll_obj.fn+spll_obj.ylf[0];																											\
	spll_obj.theta[0]=spll_obj.theta[1]+((spll_obj.fo*spll_obj.delta_T)*(2*3.1415926));								\
	if(spll_obj.theta[0]>(2*3.1415926))																										\
		spll_obj.theta[0]=spll_obj.theta[0]-(2*3.1415926);																					\
	spll_obj.theta[1]=spll_obj.theta[0];																												\


//*********** Structure Definition ********//
typedef struct{
	FLT32 a;
	FLT32 b;
	FLT32 c;
	FLT32 alpha;
	FLT32 beta;
	FLT32 sin;
	FLT32 cos;
	FLT32 d;
	FLT32 q;
	FLT32 z;
}ABC_DQ0_POS_IQ;

//*********** Function Declarations *******//
void ABC_DQ0_POS_IQ_init(ABC_DQ0_POS_IQ *v);
void ABC_DQ0_POS_IQ_FUNC(ABC_DQ0_POS_IQ *v);

//*********** Macro Definition ************//
#define ABC_DQ0_POS_IQ_MACRO(v) 										\
	v.alpha=(0.6666666667*(v.a-((0.5)*(v.b+v.c))));	\
	v.beta=((0.57735026913)*(v.b-v.c));						\
	v.z=((0.33333333333)*(v.a+v.b+v.c));						\
	v.d=(v.alpha*v.cos)+(v.beta*v.sin);						\
	v.q=-(v.alpha*v.sin)+(v.beta*v.cos);




#endif /* SPLL_3ph_SRF_IQ_H_ */
