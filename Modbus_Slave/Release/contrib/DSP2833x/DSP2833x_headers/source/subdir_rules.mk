################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
contrib/DSP2833x/DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.obj: ../contrib/DSP2833x/DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.12.0.STS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O2 --include_path="C:/Users/ragashe/Github/FREEDM_Controller_Code/Modbus_Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.12.0.STS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="contrib/DSP2833x/DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.d" --obj_directory="contrib/DSP2833x/DSP2833x_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


