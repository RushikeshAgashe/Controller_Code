@echo off
"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" --include_path="C:/Users/klee10/workspace_v5_5/BLDC_Joby/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp"  "../main.c"
