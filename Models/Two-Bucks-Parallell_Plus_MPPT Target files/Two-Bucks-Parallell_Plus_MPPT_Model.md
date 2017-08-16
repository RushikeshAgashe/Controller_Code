Model 77f446deb8f711e7b164d4bed9984596 

REM *****************************************: 
REM * Common entries:
REM *****************************************:

REM Setting the simulation time step... 
rtds_write 0x00000000 0x96

REM Machine block inputs... 
rtds_write 0x00000003 0x0

REM LUT solver inputs... 
rtds_write 0x01000000 0x3
rtds_write 0x01000080 0x203
rtds_write 0x010000C0 0.000000e+000
rtds_write 0x01000100 1.000000e+000
rtds_write 0x01000180 498.0
rtds_write 0x01000081 0x204
rtds_write 0x010000C1 0.000000e+000
rtds_write 0x01000101 1.000000e+000
rtds_write 0x01000181 498.0
rtds_write 0x01000082 0x20B
rtds_write 0x010000C2 0.000000e+000
rtds_write 0x01000102 1.000000e+000
rtds_write 0x01000182 498.0

REM *****************************************: 
REM * SPC1 entries:
REM *****************************************:
 
REM SPC1 Topology Selector (TS) initialization... 
rtds_file_write 0x08180000 SPC1_red_table.txt
rtds_write 0x08100004 0x0
rtds_write 0x0810000B 0x0
rtds_write 0x0810000C 0x0
rtds_write 0x08100010 0x0
rtds_write 0x08100018 0x0
rtds_write 0x08100020 0x1
rtds_write 0x08100021 0x0
rtds_write 0x08100023 0x0
rtds_write 0x08100024 0x0
rtds_write 0x08100025 0x0
rtds_write 0x08100026 0x0
rtds_write 0x08100027 0x0
rtds_file_write 0x08140000 trivial_imem.txt 
rtds_file_write 0x08142000 trivial_lut.txt 
rtds_write 0x08100011 0x0
rtds_write 0x08100019 0x0
rtds_write 0x08100030 0x1
rtds_write 0x08100031 0x0
rtds_write 0x08100033 0x0
rtds_write 0x08100034 0x0
rtds_write 0x08100035 0x0
rtds_write 0x08100036 0x0
rtds_write 0x08100037 0x0
rtds_file_write 0x08148000 trivial_imem.txt 
rtds_file_write 0x0814A000 trivial_lut.txt 
rtds_write 0x08100012 0x0
rtds_write 0x0810001A 0x0
rtds_write 0x08100040 0x1
rtds_write 0x08100041 0x0
rtds_write 0x08100043 0x0
rtds_write 0x08100044 0x0
rtds_write 0x08100045 0x0
rtds_write 0x08100046 0x0
rtds_write 0x08100047 0x0
rtds_file_write 0x08150000 trivial_imem.txt 
rtds_file_write 0x08152000 trivial_lut.txt 

REM SPC1 Variable Delay initialization... 

REM SPC1 Matrix multiplier initialization... 
rtds_file_write 0x08000000 SPC1_Com_Word.txt
rtds_file_write 0x08020000 SPC1_Com_LUT.txt
rtds_file_write 0x08080000 SPC1_MAC1_Val.txt
rtds_file_write 0x08082000 SPC1_MAC1_Col.txt
rtds_file_write 0x08084000 SPC1_MAC2_Val.txt
rtds_file_write 0x08086000 SPC1_MAC2_Col.txt
rtds_file_write 0x08088000 SPC1_MAC3_Val.txt
rtds_file_write 0x0808A000 SPC1_MAC3_Col.txt
rtds_file_write 0x0808C000 SPC1_MAC4_Val.txt
rtds_file_write 0x0808E000 SPC1_MAC4_Col.txt

REM SPC1 Contactors initialization... 

REM SPC1 GDS compensation settings... 
rtds_write 0x080C0000 0x1
rtds_write 0x080C0001 0x0
rtds_write 0x080C0004 0x3CA3D70A
rtds_write 0x080C0005 0x3D710000
rtds_write 0x08100000 0x32

REM SPC1 FSM digital input pin assignments... 

REM SPC1 Comparators initialization... 

REM SPC1 DTSM initialization... 

REM *****************************************: 
REM * SPC2 entries:
REM *****************************************:
 
REM SPC2 Topology Selector (TS) initialization... 
rtds_file_write 0x08580000 SPC2_red_table.txt
rtds_write 0x08500004 0x0
rtds_write 0x0850000B 0x0
rtds_write 0x0850000C 0x0
rtds_write 0x08500010 0x0
rtds_write 0x08500018 0x0
rtds_write 0x08500020 0x1
rtds_write 0x08500021 0x0
rtds_write 0x08500023 0x0
rtds_write 0x08500024 0x0
rtds_write 0x08500025 0x0
rtds_write 0x08500026 0x0
rtds_write 0x08500027 0x0
rtds_file_write 0x08540000 trivial_imem.txt 
rtds_file_write 0x08542000 trivial_lut.txt 
rtds_write 0x08500011 0x0
rtds_write 0x08500019 0x0
rtds_write 0x08500030 0x1
rtds_write 0x08500031 0x0
rtds_write 0x08500033 0x0
rtds_write 0x08500034 0x0
rtds_write 0x08500035 0x0
rtds_write 0x08500036 0x0
rtds_write 0x08500037 0x0
rtds_file_write 0x08548000 trivial_imem.txt 
rtds_file_write 0x0854A000 trivial_lut.txt 
rtds_write 0x08500012 0x0
rtds_write 0x0850001A 0x0
rtds_write 0x08500040 0x1
rtds_write 0x08500041 0x0
rtds_write 0x08500043 0x0
rtds_write 0x08500044 0x0
rtds_write 0x08500045 0x0
rtds_write 0x08500046 0x0
rtds_write 0x08500047 0x0
rtds_file_write 0x08550000 trivial_imem.txt 
rtds_file_write 0x08552000 trivial_lut.txt 

REM SPC2 Variable Delay initialization... 

REM SPC2 Matrix multiplier initialization... 
rtds_file_write 0x08400000 SPC2_Com_Word.txt
rtds_file_write 0x08420000 SPC2_Com_LUT.txt
rtds_file_write 0x08480000 SPC2_MAC1_Val.txt
rtds_file_write 0x08482000 SPC2_MAC1_Col.txt
rtds_file_write 0x08484000 SPC2_MAC2_Val.txt
rtds_file_write 0x08486000 SPC2_MAC2_Col.txt
rtds_file_write 0x08488000 SPC2_MAC3_Val.txt
rtds_file_write 0x0848A000 SPC2_MAC3_Col.txt
rtds_file_write 0x0848C000 SPC2_MAC4_Val.txt
rtds_file_write 0x0848E000 SPC2_MAC4_Col.txt

REM SPC2 Contactors initialization... 

REM SPC2 GDS compensation settings... 
rtds_write 0x084C0000 0x1
rtds_write 0x084C0001 0x0
rtds_write 0x084C0004 0x3CA3D70A
rtds_write 0x084C0005 0x3D710000
rtds_write 0x08500000 0x32

REM SPC2 FSM digital input pin assignments... 

REM SPC2 Comparators initialization... 

REM SPC2 DTSM initialization... 

REM *****************************************: 
REM * SPC3 entries:
REM *****************************************:
 
REM SPC3 Topology Selector (TS) initialization... 
rtds_file_write 0x08980000 SPC3_red_table.txt
rtds_write 0x08900004 0x0
rtds_write 0x0890000B 0x0
rtds_write 0x0890000C 0x0
rtds_write 0x08900010 0x0
rtds_write 0x08900018 0x0
rtds_write 0x08900020 0x4
rtds_write 0x08900021 0x2
rtds_write 0x08900023 0x0
rtds_write 0x08900024 0x0
rtds_write 0x08900025 0x0
rtds_write 0x08900026 0x4
rtds_write 0x08900027 0x0
rtds_file_write 0x08940000 igbt_leg_imem.txt 
rtds_file_write 0x08942000 igbt_leg_lut.txt 
rtds_write 0x08900011 0x0
rtds_write 0x08900019 0x0
rtds_write 0x08900030 0x4
rtds_write 0x08900031 0x3
rtds_write 0x08900033 0x1
rtds_write 0x08900034 0x0
rtds_write 0x08900035 0x0
rtds_write 0x08900036 0x0
rtds_write 0x08900037 0x0
rtds_file_write 0x08948000 igbt_leg_imem.txt 
rtds_file_write 0x0894A000 igbt_leg_lut.txt 
rtds_write 0x08900012 0x0
rtds_write 0x0890001A 0x0
rtds_write 0x08900040 0x4
rtds_write 0x08900041 0x3
rtds_write 0x08900043 0x1
rtds_write 0x08900044 0x0
rtds_write 0x08900045 0x0
rtds_write 0x08900046 0x0
rtds_write 0x08900047 0x0
rtds_file_write 0x08950000 igbt_leg_imem.txt 
rtds_file_write 0x08952000 igbt_leg_lut.txt 

REM SPC3 Variable Delay initialization... 
rtds_write 0x08900001 0x0

REM SPC3 Matrix multiplier initialization... 
rtds_file_write 0x08800000 SPC3_Com_Word.txt
rtds_file_write 0x08820000 SPC3_Com_LUT.txt
rtds_file_write 0x08880000 SPC3_MAC1_Val.txt
rtds_file_write 0x08882000 SPC3_MAC1_Col.txt
rtds_file_write 0x08884000 SPC3_MAC2_Val.txt
rtds_file_write 0x08886000 SPC3_MAC2_Col.txt
rtds_file_write 0x08888000 SPC3_MAC3_Val.txt
rtds_file_write 0x0888A000 SPC3_MAC3_Col.txt
rtds_file_write 0x0888C000 SPC3_MAC4_Val.txt
rtds_file_write 0x0888E000 SPC3_MAC4_Col.txt

REM SPC3 Contactors initialization... 

REM SPC3 GDS compensation settings... 
rtds_write 0x088C0000 0x1
rtds_write 0x088C0001 0x9
rtds_write 0x088C0004 0x3CA3D70A
rtds_write 0x088C0005 0x3D710000
rtds_write 0x08900000 0x32

REM SPC3 FSM digital input pin assignments... 
rtds_write 0x08900028 0x0 
rtds_write 0x08900029 0x0 
rtds_write 0x0890002A 0x0 
rtds_write 0x0890002B 0x0 
rtds_write 0x0890002C 0x11 
rtds_write 0x0890002D 0x0 
rtds_write 0x08900022 0x0 
rtds_write 0x08900038 0x0 
rtds_write 0x08900039 0x0 
rtds_write 0x0890003A 0x0 
rtds_write 0x0890003B 0x0 
rtds_write 0x0890003C 0x1f 
rtds_write 0x0890003D 0x1f 
rtds_write 0x08900032 0x1 
rtds_write 0x08900048 0x0 
rtds_write 0x08900049 0x0 
rtds_write 0x0890004A 0x0 
rtds_write 0x0890004B 0x0 
rtds_write 0x0890004C 0x19 
rtds_write 0x0890004D 0x19 
rtds_write 0x08900042 0x1 

REM SPC3 Comparators initialization... 

REM SPC3 DTSM initialization... 

REM *****************************************: 
REM * SPC4 entries:
REM *****************************************:
 
REM SPC4 Topology Selector (TS) initialization... 
rtds_file_write 0x08D80000 SPC4_red_table.txt
rtds_write 0x08D00004 0x0
rtds_write 0x08D0000B 0x0
rtds_write 0x08D0000C 0x0
rtds_write 0x08D00010 0x0
rtds_write 0x08D00018 0x0
rtds_write 0x08D00020 0x0
rtds_write 0x08D00021 0x0
rtds_write 0x08D00023 0x0
rtds_write 0x08D00024 0x0
rtds_write 0x08D00025 0x0
rtds_write 0x08D00026 0x4
rtds_write 0x08D00027 0x0
rtds_file_write 0x08D40000  
rtds_file_write 0x08D42000  
rtds_write 0x08D00011 0x0
rtds_write 0x08D00019 0x0
rtds_write 0x08D00030 0x0
rtds_write 0x08D00031 0x0
rtds_write 0x08D00033 0x0
rtds_write 0x08D00034 0x0
rtds_write 0x08D00035 0x0
rtds_write 0x08D00036 0x0
rtds_write 0x08D00037 0x0
rtds_file_write 0x08D48000  
rtds_file_write 0x08D4A000  
rtds_write 0x08D00012 0x0
rtds_write 0x08D0001A 0x0
rtds_write 0x08D00040 0x0
rtds_write 0x08D00041 0x0
rtds_write 0x08D00043 0x0
rtds_write 0x08D00044 0x0
rtds_write 0x08D00045 0x0
rtds_write 0x08D00046 0x0
rtds_write 0x08D00047 0x0
rtds_file_write 0x08D50000  
rtds_file_write 0x08D52000  

REM SPC4 Variable Delay initialization... 

REM SPC4 Matrix multiplier initialization... 
rtds_file_write 0x08C00000 SPC4_Com_Word.txt
rtds_file_write 0x08C20000 SPC4_Com_LUT.txt
rtds_file_write 0x08C80000 SPC4_MAC1_Val.txt
rtds_file_write 0x08C82000 SPC4_MAC1_Col.txt
rtds_file_write 0x08C84000 SPC4_MAC2_Val.txt
rtds_file_write 0x08C86000 SPC4_MAC2_Col.txt
rtds_file_write 0x08C88000 SPC4_MAC3_Val.txt
rtds_file_write 0x08C8A000 SPC4_MAC3_Col.txt
rtds_file_write 0x08C8C000 SPC4_MAC4_Val.txt
rtds_file_write 0x08C8E000 SPC4_MAC4_Col.txt

REM SPC4 Contactors initialization... 
rtds_write 0x08E40003 0x0 
rtds_write 0x08E40013 0x0 
rtds_write 0x08E40023 0x0 
rtds_write 0x08E40033 0x0 
rtds_write 0x08E40043 0x0 
rtds_write 0x08E40053 0x0 
rtds_write 0x08E40063 0x0 
rtds_write 0x08E40073 0x0 

REM SPC4 GDS compensation settings... 
rtds_write 0x08CC0000 0x0
rtds_write 0x08CC0001 0x0
rtds_write 0x08CC0004 0x0
rtds_write 0x08CC0005 0x0

REM SPC4 FSM digital input pin assignments... 

REM SPC4 Comparators initialization... 

REM SPC4 DTSM initialization... 

REM *****************************************: 
REM * SPC5 entries:
REM *****************************************:
 
REM SPC5 Topology Selector (TS) initialization... 
rtds_file_write 0x09180000 SPC5_red_table.txt
rtds_write 0x09100004 0x0
rtds_write 0x0910000B 0x0
rtds_write 0x0910000C 0x0
rtds_write 0x09100010 0x0
rtds_write 0x09100018 0x0
rtds_write 0x09100020 0x0
rtds_write 0x09100021 0x0
rtds_write 0x09100023 0x0
rtds_write 0x09100024 0x0
rtds_write 0x09100025 0x0
rtds_write 0x09100026 0x4
rtds_write 0x09100027 0x0
rtds_file_write 0x09140000  
rtds_file_write 0x09142000  
rtds_write 0x09100011 0x0
rtds_write 0x09100019 0x0
rtds_write 0x09100030 0x0
rtds_write 0x09100031 0x0
rtds_write 0x09100033 0x0
rtds_write 0x09100034 0x0
rtds_write 0x09100035 0x0
rtds_write 0x09100036 0x0
rtds_write 0x09100037 0x0
rtds_file_write 0x09148000  
rtds_file_write 0x0914A000  
rtds_write 0x09100012 0x0
rtds_write 0x0910001A 0x0
rtds_write 0x09100040 0x0
rtds_write 0x09100041 0x0
rtds_write 0x09100043 0x0
rtds_write 0x09100044 0x0
rtds_write 0x09100045 0x0
rtds_write 0x09100046 0x0
rtds_write 0x09100047 0x0
rtds_file_write 0x09150000  
rtds_file_write 0x09152000  

REM SPC5 Variable Delay initialization... 

REM SPC5 Matrix multiplier initialization... 
rtds_file_write 0x09000000 SPC5_Com_Word.txt
rtds_file_write 0x09020000 SPC5_Com_LUT.txt
rtds_file_write 0x09080000 SPC5_MAC1_Val.txt
rtds_file_write 0x09082000 SPC5_MAC1_Col.txt
rtds_file_write 0x09084000 SPC5_MAC2_Val.txt
rtds_file_write 0x09086000 SPC5_MAC2_Col.txt
rtds_file_write 0x09088000 SPC5_MAC3_Val.txt
rtds_file_write 0x0908A000 SPC5_MAC3_Col.txt
rtds_file_write 0x0908C000 SPC5_MAC4_Val.txt
rtds_file_write 0x0908E000 SPC5_MAC4_Col.txt

REM SPC5 Contactors initialization... 
rtds_write 0x09240003 0x0 
rtds_write 0x09240013 0x0 
rtds_write 0x09240023 0x0 
rtds_write 0x09240033 0x0 
rtds_write 0x09240043 0x0 
rtds_write 0x09240053 0x0 
rtds_write 0x09240063 0x0 
rtds_write 0x09240073 0x0 

REM SPC5 GDS compensation settings... 
rtds_write 0x090C0000 0x0
rtds_write 0x090C0001 0x0
rtds_write 0x090C0004 0x0
rtds_write 0x090C0005 0x0

REM SPC5 FSM digital input pin assignments... 

REM SPC5 Comparators initialization... 

REM SPC5 DTSM initialization... 

REM *****************************************: 
REM * SPC6 entries:
REM *****************************************:
 
REM SPC6 Topology Selector (TS) initialization... 
rtds_file_write 0x09580000 SPC6_red_table.txt
rtds_write 0x09500004 0x0
rtds_write 0x0950000B 0x0
rtds_write 0x0950000C 0x0
rtds_write 0x09500010 0x0
rtds_write 0x09500018 0x0
rtds_write 0x09500020 0x0
rtds_write 0x09500021 0x0
rtds_write 0x09500023 0x0
rtds_write 0x09500024 0x0
rtds_write 0x09500025 0x0
rtds_write 0x09500026 0x4
rtds_write 0x09500027 0x0
rtds_file_write 0x09540000  
rtds_file_write 0x09542000  
rtds_write 0x09500011 0x0
rtds_write 0x09500019 0x0
rtds_write 0x09500030 0x0
rtds_write 0x09500031 0x0
rtds_write 0x09500033 0x0
rtds_write 0x09500034 0x0
rtds_write 0x09500035 0x0
rtds_write 0x09500036 0x0
rtds_write 0x09500037 0x0
rtds_file_write 0x09548000  
rtds_file_write 0x0954A000  
rtds_write 0x09500012 0x0
rtds_write 0x0950001A 0x0
rtds_write 0x09500040 0x0
rtds_write 0x09500041 0x0
rtds_write 0x09500043 0x0
rtds_write 0x09500044 0x0
rtds_write 0x09500045 0x0
rtds_write 0x09500046 0x0
rtds_write 0x09500047 0x0
rtds_file_write 0x09550000  
rtds_file_write 0x09552000  

REM SPC6 Variable Delay initialization... 

REM SPC6 Matrix multiplier initialization... 
rtds_file_write 0x09400000 SPC6_Com_Word.txt
rtds_file_write 0x09420000 SPC6_Com_LUT.txt
rtds_file_write 0x09480000 SPC6_MAC1_Val.txt
rtds_file_write 0x09482000 SPC6_MAC1_Col.txt
rtds_file_write 0x09484000 SPC6_MAC2_Val.txt
rtds_file_write 0x09486000 SPC6_MAC2_Col.txt
rtds_file_write 0x09488000 SPC6_MAC3_Val.txt
rtds_file_write 0x0948A000 SPC6_MAC3_Col.txt
rtds_file_write 0x0948C000 SPC6_MAC4_Val.txt
rtds_file_write 0x0948E000 SPC6_MAC4_Col.txt

REM SPC6 Contactors initialization... 
rtds_write 0x09640003 0x0 
rtds_write 0x09640013 0x0 
rtds_write 0x09640023 0x0 
rtds_write 0x09640033 0x0 
rtds_write 0x09640043 0x0 
rtds_write 0x09640053 0x0 
rtds_write 0x09640063 0x0 
rtds_write 0x09640073 0x0 

REM SPC6 GDS compensation settings... 
rtds_write 0x094C0000 0x0
rtds_write 0x094C0001 0x0
rtds_write 0x094C0004 0x0
rtds_write 0x094C0005 0x0

REM SPC6 FSM digital input pin assignments... 

REM SPC6 Comparators initialization... 

REM SPC6 DTSM initialization... 

REM DI active level settings... 
rtds_write 0x00F00000 0x0 

REM HSSL configuration files... 
rtds_file_write 0x01C80000 hssl_tx_config.txt
rtds_file_write 0x01D00000 hssl_rx_config.txt
*****************************************:


REM SP data configuration...
*****************************************:


REM Setting the capture sample step...
rtds_write 0x00000027 0x00000096


REM post SP Init calculation...
rtds_write 0x00000040 0x002FFFFF
rtds_write 0x00000041 0x000001C1
rtds_write 0x00000005 0x00000000
glbl_write 0x41200048 0x00000000
glbl_write 0x42200048 0x00000000
rtds_write 0x00000043 0x59682F00
rtds_write 0x00000042 0x047868BF
rtds_write 0x0000000A 0x00000000


REM CoProcessors uBlaze_1, uBlaze_2 and uBlaze_3 configuration
glbl_write 0x40800000 0x7
glbl_write 0x40800000 0x7