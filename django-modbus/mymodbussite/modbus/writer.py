import random
from pyModbusTCP.client import ModbusClient
import win_inet_pton
import time
import sys

flagFile = open('modbus/flag', 'w')
value = 1
flagFile.write(str(value))
flagFile.close()

##def main():
##    c = ModbusClient(host = "10.76.56.2", port=8899, auto_open=False, debug=True, timeout = 2)
##    print c.open()
##    c.unit_id(3)
##    c.write_single_register(5,38)
##    #time.sleep(0.7)
##    regs = c.read_holding_registers(0,10)
##    print regs
##    print c.close()
##    flag = 0
##
##if __name__ == "__main__":       
##    main()
