# FREEDM_Controller_Code
This repository contains the source code for the Control Code on TMS320F28335 with MODBUS communication
 Buck-Modbus has fully functional MODBUS and CAN communication codes, verified on 03/27/2018.
 
 NOTES:
 
 Only Controller with 'Controller_ID == 3' is capable of performing direct MODBUS communication on its serial port.
 To set up MODBUS RTU communication from a MODBUS master on PC, select COM port corresponding to DSP3. (See LEDs RX3 TX3 on Typhoon's 'uGrid DSP Interface 2.0 Board' to check)
 
 Controllers with 'Controller ID == 1' or 'Controller_ID ==2' are capable of MODBUS communication indirectly.
 The PC must communicate with Controller3, requesting for messages for any SLAVE ID.
 The Controller3 compares the incoming message's slave ID with it's own. If match, Controller3 responds back. If mismatch see below,
 
 Controller3 --> Broadcasts MODBUS message encapsulated in a CAN frame to all other controllers connected on the CAN Bus. 
 Each controller decapsulates the CAN header to see SLAVE ID in MODBUS message. If no match, ignore message. 
 If it matches, the controller constructs a MODBUS reply message and encapsulates it in a CAN frame outbound to Controller 3.
 Controller3 decapsulates the CAN header and replies back to the PC.
 
 In summary, Controller3 acts as the agent and passes the MODBUS messages to other nodes. The PC is oblivious to this, and communicates with each SLAVE just on the basis of its SLAVE ID.
 The PC however, is physically connected to only one SLAVE. In this implementation, Controller3.
