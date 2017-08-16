import csv

##mydict = {'MPPT_flag': 0,
##          'MPPT': 0,
##          'SoC_flag' :0,
##          'SoCBalancing':0,
##          'Rd1': 0.25,
##          'Rd2': 0.25
##          }

mydict = {'flag': 0,
          'MPPT': 0,
          'SoCBalancing':0,
          'Rd1': 0.25,
          'Rd2': 0.25
          }

with open('modbus/flag.csv', 'wb') as csv_file:
    writer = csv.writer(csv_file)
    for key, value in mydict.items():
        writer.writerow([key,value])


