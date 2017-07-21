28335ModbusSlave
================

MODBUS implementation for F28335 DSP. This was developed by Bruno Luiz (@brunoluiz) to a project for TRACTEBEL in partnership with CERTI Foundation.

Installing
==========

Structure
---------
All modbus implementation are at ```contrib/modbus``` folder. We suggest you to put all your code at source folder.

If you need any DSP2833x header file you can find it at ```contrib/DSP2833x```

Include paths
-------------
If you use Code Composer 4 (or later), import the C/C++ Project Settings from ```ccs_configs/28335ModbusCSettings.xml``` file.

Another way to include the right paths is changing the "Include Options". At CCS 6.x you have to go to Project Settings (ALT+ENTER), then Build ``` C200 Compiler ``` Include Options. You've to include the following paths:

* ```contrib/modbus/include```
* ```contrib/modbus/plataform/ DSP2833x/include```
* ```contrib/DSP2833x/DSP2833x_common/include```
* ```contrib/DSP2833x/DSP2833x_headers/include```
 
If your project uses custom DSP2833x headers/files you don't need the two last paths.

Don't forget to exclude from compilation the ```contrib/dspProfiling``` and ```contrib/DSP2833x``` (right mouse click ``` Exclude from Build).

Code Composers 3 or ealier versions
-----------------------------------
If you use CodeComposer v3.x or earlier, probably your directory structure uses PROJECT/Source and PROJECT/Include to control the src and header files. To make it more easier for your use, you can run makeCSSv3.bat (or makeCSSv3.sh if you use Linux) to create a folder with the same structure of CCSv3.

At the batch file you can configure a different folder (CCSv3OutputDir), but the default action is create a "CCSv3" folder at the MODBUS root folder. If you don't have the serial and timer headers from Texas, I suggest you to enable their copy process changing the "CopySerialTimerHeader" variable.
 
Implementing
============
 
Normally this code will be implemented at ```main.c```
 
1. Include the ModbusSlave.h header 
2. Change the configuration files:
 	a. ```ModbusSettings.h```: baudrate, parity, debug modes, buffer size (the max size of a frame)...
 	b. ```Serial.c``` & ```Timer.c```: if your CLOCK or LSPCLK are different from 150 e 37500000, change those files
3. Declare the modbus object with ```ModbusSlave mb;```
4. Initialize modbus object with ```mb = construct_ModbusSlave();```
5. At some loop, call modbus object with ```mb.loopStates(&mb);```
 
Using memory map
================  

To use the memory map you will need to change the ```ModbusDataMap.h``` file with the variables that you want.
 
Don't forget that coils/inputs are Uint8 values! By default, the holding registers are meant to be 32 bits (long or float). If you want to use 16 bits variables you can enable that disabling MB_32_BITS_REGISTERS on ```ModbusSettings.h```.

Observation: the data map is specified at ```ModbusDataMap.h``` but if you want to hold different data maps and just change them before compile the code, you can change the ```MB_DATA_MAP``` constant at ```ModbusSettings.h```. By default it is ```ModbusDataMap.h```.
