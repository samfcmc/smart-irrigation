"""
	Irrigation Control: Module to
	send messages to the arduino
	to control the Irrigation
	system
"""
# Messages
GET = 1
SET = 2
CURRENT_TEMPERATURE = 0
CURRENT_HUMIDITY = 1
TEMPERATURE_MIN = 2
TEMPERATURE_MAX = 3
HUMIDITY_MIN = 4
HUMIDITY_MAX = 5

class IrrigationControl(object):
	def __init__(self, arduino):
		self.arduino = arduino



	def get_current_temperature_message(self):
		return bytes([GET, CURRENT_TEMPERATURE])

	def get_current_humidity_message(self):
		return bytes([GET, CURRENT_HUMIDITY])

	def get_temperature_min_message(self):
		return bytes([GET, TEMPERATURE_MIN])

	def get_temperature_max_message(self):
		return bytes([GET, TEMPERATURE_MAX])

	def get_humidity_min_message(self):
		return bytes([GET, HUMIDITY_MIN])

	def get_humidity_max_message(self):
		return bytes([GET, HUMIDITY_MAX])

	def set_current_temperature_message(self, value):
		return bytes([SET, CURRENT_TEMPERATURE, value])

	def set_current_humidity_message(self, value):
		return bytes([SET, CURRENT_HUMIDITY, value])

	def set_temperature_min_message(self, value):
		return bytes([SET, TEMPERATURE_MIN, value])

	def set_temperature_max_message(self, value):
		return bytes([SET, TEMPERATURE_MAX, value])

	def set_humidity_min_message(self, value):
		return bytes([SET, HUMIDITY_MIN, value])

	def set_humidity_max_message(self, value):
		return bytes([SET, HUMIDITY_MAX, value])



	def get_state(self, temperature, humidity, configuration):
		state = {'temperature': 'GOOD', 'watering': False}
		# Check temperature
		temp_min = configuration['temperature']['min']
		temp_max = configuration['temperature']['max']
		if temperature < temp_min:
			state['temperature'] = 'LOW'
		elif temperature > temp_max:
			state['temperature'] = 'HIGH'
		# Check humidity
		humidity_min = configuration['humidity']['min']
		if humidity < humidity_min:
			state['watering'] = True
		return state

	def get_status(self):
        # Getting the conditions of the plant
		self.arduino.write(self.get_current_temperature_message())
		temperatureByte = self.arduino.read()
		temperature = self.arduino.byteToInteger(temperatureByte)
		self.arduino.write(self.get_current_humidity_message())
		humidityByte = self.arduino.read()
		humidity = self.arduino.byteToInteger(humidityByte)
		# Getting the configuration that is inside the Arduino
		configuration = self.get_current_configuration()
		state = self.get_state(temperature, humidity, configuration)
		# Building data object to appear if the web app
		status = {'temperature': temperature, 'humidity': humidity, 'configuration': configuration, 'state': state}
		return status


	def sync(self, configurations, days):
		for configuration in configurations:
			if configuration.after_date <= days:
				config_found = configuration

		self.arduino.write(self.set_temperature_min_message(config_found.temperature_min))
		self.arduino.read()
		self.arduino.write(self.set_temperature_max_message(config_found.temperature_max))
		self.arduino.read()
		self.arduino.write(self.set_humidity_min_message(config_found.humidity_min))
		self.arduino.read()
		self.arduino.write(self.set_humidity_max_message(config_found.humidity_max))

		result = {'synced': True}
		return result

	def disconnect(self):
		self.arduino.close()

	def set_temperature(self, temperature):
		message = self.set_current_temperature_message(temperature)
		self.arduino.write(message)
		temperatureByte = self.arduino.read()
		result = self.arduino.byteToInteger(temperatureByte)
		return result

	def set_humidity(self, humidity):
		self.arduino.write(self.set_current_humidity_message(humidity))
		humidityByte = self.arduino.read()
		result = self.arduino.byteToInteger(humidityByte)
		return result

	def get_current_configuration(self):
		self.arduino.write(self.get_temperature_min_message())
		temp_min_byte = self.arduino.read()
		temp_min = self.arduino.byteToInteger(temp_min_byte)

		self.arduino.write(self.get_temperature_max_message())
		temp_max_byte = self.arduino.read()
		temp_max = self.arduino.byteToInteger(temp_max_byte)

		self.arduino.write(self.get_humidity_min_message())
		hum_min_byte = self.arduino.read()
		hum_min = self.arduino.byteToInteger(hum_min_byte)

		self.arduino.write(self.get_humidity_max_message())
		hum_max_byte = self.arduino.read()
		hum_max = self.arduino.byteToInteger(hum_max_byte)

		result = {'temperature': {'min': temp_min, 'max': temp_max}, 'humidity': {'min': hum_min, 'max': hum_max}}

		return result