import sqlite3
import random
from pyModbusTCP.client import ModbusClient
import win_inet_pton
from struct import *
import time

def create_table():
    conn = sqlite3.connect('modbusdata2.db')
    c= conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS stuffToPlot(value1 REAL,value2 REAL,value3 REAL,value4 REAL, value5 REAL, value6 REAL, value7 REAL, value8 REAL, value9 REAL,value10 REAL,value11 REAL, value12 REAL)")
    c.execute("INSERT INTO stuffToPlot VALUES(500,2,3,4,5,6,7,8,9,10,11,12)")
    conn.commit()
    c.close()
    conn.close()
    
def read_from_db():
    conn = sqlite3.connect('modbusdata2.db')
    c= conn.cursor()
    c.execute('SELECT * FROM stuffToPlot')
    data = c.fetchall()
    for x in data:
        row = x
    conn.commit()
    c.close()
    conn.close()
    return row
    

def data_entry():
    conn = sqlite3.connect('modbusdata2.db', timeout=15)
    c= conn.cursor()
    c.execute("INSERT INTO stuffToPlot VALUES(?,?,?,?,?,?,?,?,?,?,?,?);",(DC_Bus_Voltage,Battery_1,Battery_2,PV,Current_Battery_1,Current_Battery_2,0,0,0,0,0,0))
    conn.commit()
    c.close()
    conn.close()
    
create_table()
true = 1
DC_Bus_Voltage = 0.0
PV = 0.0
Battery_1 = 0.0
Battery_2 = 0.0
Inverter  = 0.0
Current_Battery_1 = 0.0
Current_Battery_2 = 0.0
data_entry()

while true is 1:
    c = ModbusClient(host = "10.76.56.2", port=8899, unit_id = 3, auto_open=False)
    c.open()
    regs = c.read_holding_registers(0,16)
    if regs is None:
        error = True
    else:
        DC_Bus_Voltage = round(unpack('f',pack('<HH',regs[1],regs[0]))[0],4)
        Current_Battery_1 = round(unpack('f',pack('<HH',regs[3],regs[2]))[0],4)
        Current_Battery_2 = round(unpack('f',pack('<HH',regs[5],regs[4]))[0],4)
        #Inverter = round(unpack('f',pack('<HH',regs[7],regs[6]))[0],4)
        PV = round(unpack('f',pack('<HH',regs[11],regs[10]))[0],4)
        Battery_1 = round(unpack('f',pack('<HH',regs[13],regs[12]))[0],4)
        Battery_2 = round(unpack('f',pack('<HH',regs[15],regs[14]))[0],4)
        data_entry()
        all_data= [DC_Bus_Voltage,Current_Battery_1,Current_Battery_2, PV, Battery_1,Battery_2]
        row = read_from_db()
        print DC_Bus_Voltage, PV ,Battery_1 , Battery_2, Current_Battery_1,Current_Battery_2
    c.close()
    time.sleep(0.7)