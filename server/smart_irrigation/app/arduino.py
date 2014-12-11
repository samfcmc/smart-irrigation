import serial

class Arduino(object):

	def __init__(self, serial_port, rate = 9600):
		self.port = serial.Serial(serial_port, rate)
		#self.port.flush()
		#self.port.read()

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

class FakeArduino(object):

	def __init__(self):
		print('Using a fake arduino')
		self.properties = [0, 0, 0, 0, 0, 0]
		self.last_property = 0

	def is_get_message(self, byteArray):
		return byteArray[0] == 1

	def is_set_message(self, byteArray):
		return byteArray[0] == 2

	def read(self):
		return bytes([self.properties[self.last_property]])

	def write(self, byteArray):
		prop = byteArray[1]
		if self.is_set_message(byteArray):
			self.properties[prop] = byteArray[2]

		self.last_property = prop

	def readline(self):
		return self.read()

	def byteToInteger(self, byte):
		value = int.from_bytes(byte, byteorder="little")
		return value

	def close(self):
		print('Closing Fake Arduino...')