import sqlite3
import random
from pyModbusTCP.client import ModbusClient
import win_inet_pton
from struct import *
import time
import csv 

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
    c.execute("INSERT INTO stuffToPlot VALUES(?,?,?,?,?,?,?,?,?,?,?,?);",(DC_Bus_Voltage,Current_Battery_1,Current_Battery_2,PV,Rd1,Rd2,Battery_1,Battery_2,0,0,0,0))
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
Rd1 = 0.0
Rd2 = 0.0
data_entry()
c = ModbusClient(host = "10.76.56.2", port=8899, auto_open=True,auto_close=True,timeout = 2)

while true == 1:
    #print "c.open\t" , c.open()
    with open('flag.csv', 'rb') as csv_file:
        reader = csv.reader(csv_file)
        mydict = dict(reader)
    flag = mydict["flag"]
    #flagFile = open('flag.txt', 'r')
    #flag = flagFile.read()
    #flagFile.close()
    flag = int(flag)
    if flag == 0:
        c.unit_id(1)
        regs = c.read_holding_registers(0,20)
        print "regs" , regs , "\n"
        if regs is None:
            error = True
            print "Could nor read from DSP1"
        else:
            DC_Bus_Voltage = round(unpack('f',pack('<HH',regs[1],regs[0]))[0],4)
            Current_Battery_1 = round(unpack('f',pack('<HH',regs[3],regs[2]))[0],4)
            Current_Battery_2 = round(unpack('f',pack('<HH',regs[5],regs[4]))[0],4)
            #regs[6] and regs[7] do not contain modbus data
            Rd1 = round(unpack('f',pack('<HH',regs[9],regs[8]))[0],4)
            Rd2 = round(unpack('f',pack('<HH',regs[11],regs[10]))[0],4)
            Battery_1 = round(unpack('f',pack('<HH',regs[13],regs[12]))[0],4)
            Battery_2 = round(unpack('f',pack('<HH',regs[15],regs[14]))[0],4)
            Test = round(unpack('i',pack('<HH',regs[17],regs[16]))[0],4)
            print Test
            c.close()
        c.unit_id(2)
        time.sleep(0.3)
        #    c.open()
        #    c = ModbusClient(host = "10.76.56.2", port=8899, unit_id = 2, auto_open=True, auto_close = True)
        regs1 = c.read_holding_registers(0,16)
        print "regs1" , regs1 , "\n"
        if regs1 is None:
            error = True
            print "Could not read from DSP2"
        else:
            PV = round(unpack('f',pack('<HH',regs1[11],regs1[10]))[0],4)
            data_entry()
            row = read_from_db()
        #print "c.close\t", c.close()
            print row, "\n"
    elif flag > 0:
        c.unit_id(1)
        word2, word1 = unpack('>HH', pack('>i', int(mydict["SoCBalancing"])))
        print word1,word2
        c.write_single_register(16,word1)
        c.write_single_register(17,word2)
        regs2 = c.read_holding_registers(0,10)
        print "GLEEEEEEEEEEEEEEEEEEEEEEBAAAAAAAAAAAAAAAAAA\n\n", regs2
        
        c.unit_id(2)
        time.sleep(0.3)
        word4, word3 = unpack('>HH', pack('>i', int(mydict["MPPT"])))
        print word1,word2
        c.write_single_register(18,word3)
        c.write_single_register(19,word4)
        regs2 = c.read_holding_registers(0,10)
        print "GLEEEEEEEEEEEEEEEEEEEEEEBAAAAAAAAAAAAAAAAAA\n\n", regs2
        
        #print "regs2" , regs2 , "\n"
        mydict["flag"] = 0
        with open('flag.csv', 'wb') as csv_file:
            writer = csv.writer(csv_file)
            for key, value in mydict.items():
                writer.writerow([key,value])
                
#        flagFile = open('flag.txt', 'w')
#        flag = flagFile.write("0")
#        flagFile.close()
