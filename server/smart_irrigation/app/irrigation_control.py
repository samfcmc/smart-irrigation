"""
	Irrigation Control: Module to
	send messages to the arduino
	to control the Irrigation
	system
"""

class IrrigationControl(object):

	def __init__(self, arduino):
		self.arduino = arduino

	def get_status(self):
		#TODO: Change this
		message = 'test'

		status = {
			'name': 'Test',
			'temperature': 0,
			'humidity': 0
		}

		return status