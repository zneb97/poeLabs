"""
PoE Lab 3 - Line Following Robot
Lucky Jordan and Benjamin Ziemann

Sends tuning PID values to the arduino via serial
"""

import serial
import binascii
import math

#Read from serial port
ser = serial.Serial('/dev//ttyACM0',9600)

def writeSerial():
	flag = 0
	flag2 = 0

	while True:
		while flag == 0:
			var = raw_input("Enter the variable you want to tune (p,i,d)")
			if len(var) != 1:
				print("Not a valid input, enter a single character")
			else:
				flag=1
		flag = 0

		while flag2 == 0:
			value = raw_input("Enter the value you want to tune to")
			try:
				value = float(value)
			except ValueError:
				print("Not a valid value")
				break
			flag2 =1

		if flag2 == 1:
			flag2 = 0	
			ser.write(str(var)+"&"+str(value))



if __name__ == "__main__":
	writeSerial()