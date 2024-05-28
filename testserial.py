import serial
import struct
import time
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)
def write_read(x):
    arduino.write(bytes(x))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:
    num = input("Enter a number: ") # Taking input from user
    value = write_read(struct.pack('>BBB',45,90,180))
    print(value) # printing the value
    num1 = input("Enter a number1: ") # Taking input from user
    value = write_read(struct.pack('>BBB',45,90,180))
    print(value)
    
    
"""
 
 
import serial
import struct
import time

arduino = serial.Serial('/dev/ttyACM0', 9600)

# let it initialize
time.sleep(2)
num = input("Enter a number: ")
num1 = input("Enter a numbe0r: ")
num2 = input("Enter a number: ")
# send the first int in binary format
arduino.write(struct.pack('>BBB',45,90,180))"""

#, 'utf-8'
