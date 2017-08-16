import random
from pyModbusTCP.client import ModbusClient
import win_inet_pton
import time
import sys
import csv

with open('modbus/flag.csv', 'rb') as csv_file:
    reader = csv.reader(csv_file)
    mydict = dict(reader)

mydict["flag"] = 1
mydict["SoCBalancing"] = 1

with open('modbus/flag.csv', 'wb') as csv_file:
    writer = csv.writer(csv_file)
    for key, value in mydict.items():
        writer.writerow([key,value])
