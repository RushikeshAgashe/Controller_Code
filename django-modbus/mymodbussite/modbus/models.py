from __future__ import unicode_literals

from django.db import models

# Create your models here.

class PV(models.Model):
    voltage = models.FloatField(max_length = 200)
    current = models.FloatField(max_length = 200)
    timestamp = models.DateTimeField(max_length = 200)
    
class Battery1(models.Model):
    voltage = models.FloatField(max_length = 200)
    current = models.FloatField(max_length = 200)
    SoC     = models.FloatField(max_length = 200)
    timestamp = models.DateTimeField(max_length = 200)

class Battery2(models.Model):
    voltage = models.FloatField(max_length = 200)
    current = models.FloatField(max_length = 200)
    SoC     = models.FloatField(max_length = 200)
    timestamp = models.DateTimeField(max_length = 200)

class DCBusVoltage(models.Model):
    voltage = models.FloatField(max_length = 200)
    timestamp = models.DateTimeField(max_length = 200)
    
class Inverter(models.Model):
    voltage = models.FloatField(max_length = 200)
    InverterType    = models.CharField(max_length = 200)
    timestamp = models.DateTimeField(max_length = 200)
    def __str__(self):
        return self.InverterType

    