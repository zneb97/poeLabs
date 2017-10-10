"""
PoE Lab 2 - 3D Scanner
Evan Cusato and Benjamin Ziemann

Recieves position and IR values from serial, converts to distance,
and writes it into CSV
"""

import serial
import binascii
import math

#Read from serial port
ser = serial.Serial('/dev//ttyACM0',9600)

def getAxis():
    """
    Breaks down serial output and writes to CSV
    """

    #Setup
    output = ""
    axis = []
    currAxis = ''

    while(True):
        #Output takes the form x&y&analogValue
        output = ser.readline().strip()
        if output == "Stop":
            break

        #Break output into easy to use list
        axis = output.split("&")

        distance = calcDistance(axis[2])

        #IR value limits to eliminate noise
        #Background
    	if distance > 60:
    		distance = 60
        #Too close to function
    	elif distance < 0:
    		distance = 0
        
        #Write to csv
        f.write(axis[0] + ',' + axis[1] + ',' + str(distance) + "\n")

        #Reset
        axis =[]

def calcDistance(aVal):
    """
    Rough mathematical function to fit IR values to calibration data
    """
    aVal = float(aVal)
    a = 134.1
    b = -.003899
    calced = a*math.exp(b*aVal)
    return calced

if __name__ == "__main__":
    f = open("dataLab2.csv",'a')
    #Clear any existing data
    f.seek(0)
    f.truncate()
    #Header
    f.write("x" + ',' + "y" + ',' + "dist" + "\n")

    #Wait for button press / start command
    while(True):
        out = ser.readline().strip()
        if out == "Start":
            break

    getAxis()
    f.close()