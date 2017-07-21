################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
contrib/dspProfiling/Profiling.obj: ../contrib/dspProfiling/Profiling.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.12.0.STS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O2 --include_path="C:/Users/ragashe/workspace_v7/Modbus_Slave" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.12.0.STS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="contrib/dspProfiling/Profiling.d" --obj_directory="contrib/dspProfiling" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


