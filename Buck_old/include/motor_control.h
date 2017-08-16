#define ADDRESS		0

#define	LED_ON		1
#define LED_OFF		0
#define PWM_ON		1
#define PWM_OFF 	0
#define RELAY_ON	1
#define RELAY_OFF	0
#define	LED1		0x1
#define LED2		0x2
#define LED3		0x4
#define LED4		0x8
#define LED_ALL		0x10

#define BOTH		2
#define RISING		1
#define FALLING		0

#define ZCP1		6
#define HALL1		13		//7
#define ZCP2		8
#define HALL2		14		//9
#define ZCP3		10
#define HALL3		15		//11

#define DEAD_TIME	100		//113*TBCLK(1/37.5MHz) = 1usec


//FILTER
#define LPF_SPEED_EST_HALL		0
#define LPF_SPEED_EST_ENCODER	1
#define LPF_CURRENT				2


typedef		unsigned int	UINT16;
typedef		unsigned char	UCHAR8;
typedef		int 			SINT16;
typedef 	float 			FLT32;

typedef struct _ABC
{
	FLT32	a;
	FLT32	b;
	FLT32	c;
}ABC;

typedef struct _DQE
{
	FLT32	de;
	FLT32	qe;
}DQE;
typedef struct _DQS
{
	FLT32	ds;
	FLT32	qs;
}DQS;


typedef struct _LPFF 
{  
	FLT32	Wc;
	FLT32	Kxn[3];
	FLT32	Kyn[2]; 
	FLT32 	xn[2];
	FLT32	yn[2];
}LPFF;
typedef struct _BPFF
{  
	FLT32	Wc;
	FLT32	Ze;
	FLT32	InvKy;
	FLT32	Kxn[5];
	FLT32	Kyn[5]; 
	FLT32 	xn[5];
	FLT32	yn[5];
}BPFF;

/* Coefficients Define	----------------------------------------*/
#define    	f2     				(1./2.)
#define		f3					(f2/3.)
#define		f4					(f3/4.)
#define		f5					(f4/5.)
#define		f6					(f5/6.)
#define		f7					(f6/7.)
#define		f8					(f7/8.)
#define		f9					(f8/9.)
#define		f10					(f9/10.)
#define		f11					(f10/11.)
#define		f12					(f11/12.)
#define		f13					(f12/13.)
#define		f14					(f13/14.)
#define		f15					(f14/15.)

/* ---- PI Constants Define-------------------------------------*/
#define		PI					3.14159265359 
#define		M_PI				-3.14159265359
#define		TWO_PI				6.28318530718
#define		M_TWO_PI			-6.28318530718
#define		INV_PI				0.3183098862
#define		TWO_3PI			2.09439510239
#define		FOUR_3PI			4.18879020478
#define 	ONE_OVER_ROOT3	0.577350269		
#define 	ROOT3				1.732050808
#define 	PI_OVER_2			1.570796326

// SQRT 
#define		SQRT2				1.414213562
#define		SQRT3				1.732050808
#define		INV_SQRT3			(1./SQRT3)
#define		MI_INV_SQRT3		(-1./SQRT3)

/* Macro functions */
#define		BOUND_PI(x)		( (x)-2.*PI*((SINT16)(((x)+PI) /(2.*PI))))
#define 	SIN(x,x2)   			((x)*(1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
#define 	COS(x2)     			(1.-(x2)*(f2-(x2)*(f4-(x2)*(f6-(x2)*(f8-(x2)*(f10-(x2)*(f12-(x2)*f14)))))))
#define 	SIN_INV_X(x2)   		((1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
#define 	EXP(x)	    			(1.+(x)*(1.+(x)*(f2+(x)*(f3+(x)*(f4+(x)*(f5+(x)*(f6+(x)*f7)))))))
#define 	SAT(x,l)				(((x)>(l))?(l):((x)<-(l))?(-(l)):(x))
#define 	LIMIT(x,s,l)			(((x)>(l))?(l):((x)<(s))?((s)):(x))
#define 	BOUND(x,l) 			((x) + (((x)> (l)) ? (-2.*(l)) : ((x)< (-(l))) ? (2.*(l)) : 0.))


/* Speed Parameter -------------------------------------------*/
#define		RPM2WM			0.10471975512				/* Wm=((2*pi)/60)*Wrpm */
#define 	WM2RPM			9.54929658551				/* Wrpm=(60/(2*pi))*Wm */
#define 	RPM2WR			(RPM2WM*(1./2.))			/* Wr= (P/2)*Wm */

// Filter initialization & 1st and 2nd Filters 
#define	INIT_LPF1(Wcut,Ts,nf)	{LPF1[(nf)].Wc=(Wcut); a=1./(2.+(Ts)*LPF1[(nf)].Wc);\
						LPF1[(nf)].Kxn[0]=(Ts)*LPF1[(nf)].Wc*a;\
						LPF1[(nf)].Kxn[1]=LPF1[(nf)].Kxn[0];\
						LPF1[(nf)].Kyn[0]=(2.-(Ts)*LPF1[(nf)].Wc)*a;\
						LPF1[(nf)].yn[0]=0.;LPF1[(nf)].xn[0]=0.;}

#define	UPDATE_LPF1(Wcut,Ts,nf)	{LPF1[(nf)].Wc=(Wcut); a=1./(2.+(Ts)*LPF1[(nf)].Wc);\
						LPF1[(nf)].Kxn[0]=(Ts)*LPF1[(nf)].Wc*a;\
						LPF1[(nf)].Kxn[1]=LPF1[(nf)].Kxn[0];\
						LPF1[(nf)].Kyn[0]=(2.-(Ts)*LPF1[(nf)].Wc)*a;}

#define	LPF1(x,y,nf)	{a=(x);\
					b=LPF1[(nf)].Kxn[0]*a+LPF1[(nf)].Kxn[1]*LPF1[(nf)].xn[0]+LPF1[(nf)].Kyn[0]*LPF1[(nf)].yn[0];\
					LPF1[(nf)].yn[0]=b;\
					LPF1[(nf)].xn[0]=a;\
					(y)=b;}

#define	INIT_LPF2(Wcut,Ts,nf)	{LPF2[(nf)].Wc=(Wcut); a=1./(2.+(Ts)*LPF2[(nf)].Wc);\
						LPF2[(nf)].Kxn[0]=(Ts)*LPF2[(nf)].Wc*a;\
						LPF2[(nf)].Kxn[1]=LPF2[(nf)].Kxn[0];\
						LPF2[(nf)].Kyn[0]=(2.-(Ts)*LPF2[(nf)].Wc)*a;\
						LPF2[(nf)].yn[0]=0.;LPF2[(nf)].xn[0]=0.;}

#define	UPDATE_LPF2(Wcut,Ts,nf)	{LPF2[(nf)].Wc=(Wcut); a=1./(2.+(Ts)*LPF2[(nf)].Wc);\
						LPF2[(nf)].Kxn[0]=(Ts)*LPF2[(nf)].Wc*a;\
						LPF2[(nf)].Kxn[1]=LPF2[(nf)].Kxn[0];\
						LPF2[(nf)].Kyn[0]=(2.-(Ts)*LPF2[(nf)].Wc)*a;}

#define	LPF2(x,y,nf)	{a=(x);\
					b=LPF2[(nf)].Kxn[0]*a+LPF2[(nf)].Kxn[1]*LPF2[(nf)].xn[0]+LPF2[(nf)].Kyn[0]*LPF2[(nf)].yn[0];\
					LPF2[(nf)].yn[0]=b;\
					LPF2[(nf)].xn[0]=a;\
					(y)=b;}


#define	INIT_BPF(Wcut,Zeta,Ts,nf)	{BPF[(nf)].Wc=(Wcut);BPF[(nf)].Ze=(Zeta);a=1./(4.+4.*BPF[(nf)].Ze*(Ts)*BPF[(nf)].Wc+(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc);\
			BPF[(nf)].Kxn[0]=4.*BPF[(nf)].Ze*BPF[(nf)].Wc*(Ts)*a; BPF[(nf)].Kxn[1]=0.;BPF[(nf)].Kxn[2]=-BPF[(nf)].Kxn[0];\
			BPF[(nf)].Kyn[0]=(8.-2.*(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc)*a;BPF[(nf)].Kyn[1]=(-4.+4.*BPF[(nf)].Ze*(Ts)*BPF[(nf)].Wc-(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc)*a;\
			BPF[(nf)].yn[0]=0.;BPF[(nf)].xn[0]=0.;BPF[(nf)].yn[1]=0.;BPF[(nf)].xn[1]=0.;}

#define	UPDATE_BPF(Wcut,Zeta,Ts,nf)	{BPF[(nf)].Wc=(Wcut);BPF[(nf)].Ze=(Zeta);a=1./(4.+4.*BPF[(nf)].Ze*(Ts)*BPF[(nf)].Wc+(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc);\
			BPF[(nf)].Kxn[0]=4.*BPF[(nf)].Ze*BPF[(nf)].Wc*(Ts)*a; BPF[(nf)].Kxn[1]=0.;BPF[(nf)].Kxn[2]=-BPF[(nf)].Kxn[0];\
			BPF[(nf)].Kyn[0]=(8.-2.*(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc)*a;	BPF[(nf)].Kyn[1]=(-4.+4.*BPF[(nf)].Ze*(Ts)*BPF[(nf)].Wc-(Ts)*(Ts)*BPF[(nf)].Wc*BPF[(nf)].Wc)*a;}

#define	BPF(x,y,nf)	{a=(x);\
		b=BPF[(nf)].Kxn[0]*a+BPF[(nf)].Kxn[1]*BPF[(nf)].xn[0]+BPF[(nf)].Kxn[2]*BPF[(nf)].xn[1]\
		+BPF[(nf)].Kyn[0]*BPF[(nf)].yn[0]+BPF[(nf)].Kyn[1]*BPF[(nf)].yn[1];\
		BPF[(nf)].yn[1]=BPF[(nf)].yn[0];   BPF[(nf)].yn[0]=b;\
		BPF[(nf)].xn[1]=BPF[(nf)].xn[0];   BPF[(nf)].xn[0]=a; (y)=b;}

#define	lpfAlpha(fs, fc)	(1./(fs) / (1./(fs) + 2.*1./(fc)))
//===========================================================================
// No more.
//===========================================================================
