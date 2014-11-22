import serial

arduino = serial.Serial("/dev/ttyACM0", 9600);

car = arduino.read()
print(car)
 
to_send = bytes([2, 2, 50])

print("Sending " + str(to_send))

arduino.write(to_send)
read = arduino.read()
value = int.from_bytes(read, byteorder="little")
print(value)

arduino.close()
"""
arduino = serial.Serial("/dev/ttyACM0", 9600);
print(arduino.read())
to_send = b"testingoutofbufferlimits"
print("Sending " + str(to_send))
arduino.write(to_send)
print(arduino.read())

arduino.close()"""

