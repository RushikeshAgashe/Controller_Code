################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ADC_cal.asm \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CSMPasswords.asm \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DBGIER.asm \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DisInt.asm \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_usDelay.asm 

C_SRCS += \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Adc.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CpuTimers.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DMA.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DefaultIsr.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECan.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECap.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EPwm.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EQep.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Gpio.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_I2C.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_McBSP.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_MemCopy.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieCtrl.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieVect.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Sci.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Spi.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SysCtrl.c \
../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Xintf.c 

C_DEPS += \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Adc.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CpuTimers.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DMA.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DefaultIsr.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECan.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECap.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EPwm.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EQep.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Gpio.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_I2C.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_McBSP.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_MemCopy.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieCtrl.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieVect.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Sci.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Spi.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SysCtrl.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Xintf.d 

OBJS += \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ADC_cal.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Adc.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CSMPasswords.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CodeStartBranch.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CpuTimers.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DBGIER.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DMA.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DefaultIsr.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DisInt.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECan.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECap.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EPwm.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EQep.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Gpio.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_I2C.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_McBSP.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_MemCopy.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieCtrl.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieVect.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Sci.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Spi.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SysCtrl.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Xintf.obj \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_usDelay.obj 

ASM_DEPS += \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ADC_cal.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CSMPasswords.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CodeStartBranch.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DBGIER.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DisInt.d \
./contrib/DSP2833x/DSP2833x_common/source/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ADC_cal.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Adc.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CSMPasswords.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CodeStartBranch.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CpuTimers.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DBGIER.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DMA.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DefaultIsr.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DisInt.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ECan.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ECap.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_EPwm.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_EQep.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Gpio.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_I2C.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_McBSP.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_MemCopy.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_PieCtrl.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_PieVect.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SWPrioritizedDefaultIsr.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SWPrioritizedPieVect.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Sci.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Spi.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SysCtrl.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Xintf.obj" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_usDelay.obj" 

C_DEPS__QUOTED += \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Adc.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CpuTimers.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DMA.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DefaultIsr.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ECan.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ECap.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_EPwm.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_EQep.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Gpio.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_I2C.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_McBSP.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_MemCopy.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_PieCtrl.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_PieVect.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SWPrioritizedDefaultIsr.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SWPrioritizedPieVect.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Sci.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Spi.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_SysCtrl.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_Xintf.d" 

ASM_DEPS__QUOTED += \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_ADC_cal.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CSMPasswords.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_CodeStartBranch.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DBGIER.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_DisInt.d" \
"contrib\DSP2833x\DSP2833x_common\source\DSP2833x_usDelay.d" 

ASM_SRCS__QUOTED += \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ADC_cal.asm" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CSMPasswords.asm" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DBGIER.asm" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DisInt.asm" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_usDelay.asm" 

C_SRCS__QUOTED += \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Adc.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_CpuTimers.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DMA.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_DefaultIsr.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECan.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_ECap.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EPwm.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_EQep.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Gpio.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_I2C.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_McBSP.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_MemCopy.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieCtrl.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_PieVect.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedDefaultIsr.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SWPrioritizedPieVect.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Sci.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Spi.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_SysCtrl.c" \
"../contrib/DSP2833x/DSP2833x_common/source/DSP2833x_Xintf.c" 


