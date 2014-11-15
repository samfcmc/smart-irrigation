import serial

class Arduino(object):

	def __init__(self, serial_port, rate):
		self.port = serial.Serial(serial_port, rate)
		self.port.read()

	def read(self):
		return self.port.read()

	def write(self, byteArray):
		return self.port.write(byteArray)

	def readline(self):
		return self.port.readline()