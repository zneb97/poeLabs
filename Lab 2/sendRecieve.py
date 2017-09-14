import serial
import binascii
ser = serial.Serial('/dev//ttyACM0',9600)

def getAxis():
    #Output takes the form x&y&z&r&button&s
    output = ser.readline()
    outputString = str(output, 'utf-8')
    axis = []
    flag = 0
    currAxis = ''

    #Break down output
    for i in range(len(outputString)):
        if(flag != 5):
            if(outputString[i] == '&'):
                flag += 1;
                axis.append(currAxis)
                currAxis = ''
            else:
                currAxis += outputString[i]
    return axis
