import serial

arduino = serial.Serial("/dev/ttyACM0", 9600);

to_send = b"testingoutofbufferlimits"

print("Sending " + str(to_send))

arduino.write(to_send)

print(arduino.readline())