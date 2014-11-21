"""
	Irrigation Control: Module to
	send messages to the arduino
	to control the Irrigation
	system
"""
# Messages
GET_CURRENT_TEMPERATURE = bytes([0, 0, 0])
SET_CURRENT_TEMPERATURE = bytes([0, 0, 0])
GET_CURRENT_HUMIDITY = bytes([0, 0, 0])
SET_CURRENT_HUMIDITY = bytes([0, 0, 0])
SET_TEMPERATURE_MIN = bytes([0, 0, 0])
SET_TEMPERATURE_MAX = bytes([0, 0, 0])
SET_HUMIDITY_MIN = bytes([0, 0, 0])
SET_HUMIDITY_MAX = bytes([0, 0, 0])

class IrrigationControl(object):
	def __init__(self, arduino):
		self.arduino = arduino

	def get_status(self):
		self.arduino.write(GET_CURRENT_TEMPERATURE)
		temperatureByte = self.arduino.read()
		temperature = self.arduino.byteToInteger(temperatureByte)
		self.arduino.write(GET_CURRENT_HUMIDITY)
		humidityByte = self.arduino.read()
		humidity = self.arduino.byteToInteger(humidityByte)
		status = {'temperature': temperature, 'humidity': humidity}

		return status

	def sync(self, configurations, days):
		for configuration in configurations:
			if configuration.after_date <= days:
				config_found = configuration

		self.arduino.write(SET_TEMPERATURE_MIN)
		self.arduino.read()
		self.arduino.write(SET_TEMPERATURE_MAX)
		self.arduino.read()
		self.arduino.write(SET_HUMIDITY_MIN)
		self.arduino.read()
		self.arduino.write(SET_HUMIDITY_MAX)

		result = {'synced': True}
		return result

	def disconnect(self):
		self.arduino.close()

	def set_temperature(self, temperature):
		self.arduino.write(SET_CURRENT_TEMPERATURE)
		temperatureByte = self.arduino.read()
		return self.arduino.byteToInteger(temperatureByte)

	def set_humidity(self, humidity):
		self.arduino.write(SET_CURRENT_HUMIDITY)
		humidityByte = self.arduino.read()
		return self.arduino.byteToInteger(humidityByte)