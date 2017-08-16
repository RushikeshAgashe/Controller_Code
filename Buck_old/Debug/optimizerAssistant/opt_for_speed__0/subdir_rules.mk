################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ControlPeripheral.obj: ../ControlPeripheral.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="ControlPeripheral.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_ADC_cal.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_Adc.obj: ../DSP2833x_Adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_Adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: ../DSP2833x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_DefaultIsr.obj: ../DSP2833x_DefaultIsr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_DefaultIsr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieCtrl.obj: ../DSP2833x_PieCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_PieCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_PieVect.obj: ../DSP2833x_PieVect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_PieVect.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_SysCtrl.obj: ../DSP2833x_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Init.obj: ../Init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

control.obj: ../control.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="control.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

debug_283x.obj: ../debug_283x.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="debug_283x.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal_sci.obj: ../hal_sci.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="hal_sci.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

portserial.obj: ../portserial.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="portserial.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

serial_api.obj: ../serial_api.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="serial_api.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

variable.obj: ../variable.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=0 --include_path="C:/Users/klee10/workspace_v5_2/BLDC_0_final_20kHz_final/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="variable.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


