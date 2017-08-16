from django.shortcuts import render
from django.http import HttpResponse
import sqlite3
from subprocess import Popen, PIPE

def read_from_db():
    conn = sqlite3.connect('modbus/modbusdata2.db')
    c= conn.cursor()
    c.execute('SELECT * FROM stuffToPlot')
    data = c.fetchall()
    for x in data:
        row = x
    conn.commit()
    c.close()
    conn.close()
    modbusdata = row
    
    dictionary={
    'DC_Bus_Voltage':modbusdata[0],
    'Current_Battery_1':modbusdata[1],
    'Current_Battery_2':modbusdata[2],
    'PV':modbusdata[3],
    'Rd1':modbusdata[4],
    'Rd2':modbusdata[5],
    'Battery_1':modbusdata[6],
    'Battery_2':modbusdata[7],
    }
    
    return modbusdata, dictionary
    

def index(request):
    return render(request, 'modbus/ModbusDataVisualizer.html')
   
def table(request):
    modbusdata, dictionary = read_from_db()
    print "This is dummy", modbusdata
    return render(request, 'modbus/table.html', dictionary)

def tablescript(request):
    return render(request, 'modbus/table.js')

def test(request):
    p = Popen(['python','test.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)

def writer(request):
    p = Popen(['python','writer.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)
def MPPT_Enable(request):
    p = Popen(['python','MPPT_Enable.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)
def MPPT_Disable(request):
    p = Popen(['python','MPPT_Disable.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)
def SoC_Balancing_Enable(request):
    p = Popen(['python','SoC_Balancing_Enable.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)
def SoC_Balancing_Disable(request):
    p = Popen(['python','SoC_Balancing_Disable.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response)

def database(request):
    p = Popen(['python','database.py'],stdin=PIPE, stdout=PIPE,stderr=PIPE)
    response= p.communicate()
    return HttpResponse(response) 

def dataloaderscript(request):
    return render(request, 'modbus/dataloader.js')

def linechartscript(request):
    return render(request, 'modbus/linechart.js')

def base(request):
    modbusdata,dictionary = read_from_db()
    return render(request, 'modbus/base.html',dictionary)

def chart(request):
    modbusdata,dictionary = read_from_db()
    #print "This is dummy", modbusdata
    return render(request, 'modbus/chart.html',dictionary)
