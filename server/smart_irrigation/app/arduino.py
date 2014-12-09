import serial

class Arduino(object):

	def __init__(self, serial_port, rate = 9600):
		self.port = serial.Serial(serial_port, rate)
		#self.port.flush()
		print("Estou aqui!")
		#self.port.read()
		print("Estou ali!")

	def read(self):
		return self.port.read()

	def write(self, byteArray):
		return self.port.write(byteArray)

	def readline(self):
		return self.port.readline()

	def byteToInteger(self, byte):
		value = int.from_bytes(byte, byteorder="little")
		return value

	def close(self):
		self.port.close()