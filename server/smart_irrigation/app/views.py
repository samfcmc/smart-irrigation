from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt

from django.contrib.auth import logout, login, authenticate
from app.models import UserPlants, Plant, Configuration
import json

from . import arduino
from . import irrigation_control
arduino = arduino.Arduino("/dev/ttyACM0")
control = irrigation_control.IrrigationControl(arduino)

# Return json
def getJson(response):
	return HttpResponse(json.dumps(response), content_type="application/json")

def redirectToIndex():
	return HttpResponseRedirect('/app')

# Create your views here.
def index(request):
	if(request.user.is_authenticated()):
		view = 'index.html'
	else:
		view = 'login.html'

	return render(request, view)

def user_logout(request):
	logout(request)
	control.disconnect()
	return redirectToIndex()

def user_login(request):
	if request.method == 'POST':
		username = request.POST['username']
		password = request.POST['password']

		user = authenticate(username=username, password=password)
		print(user)

		if user:
			if user.is_active:
				login(request, user)
	return redirectToIndex()


"""
	REST endpoints
"""

def method_not_allowed(request):
	response = {'error': 'method ' + request.method + ' not allowed'}
	return getJson(response)

def plant_to_json(plant, request):
	response = {'id': plant.id, 'name': plant.name, 'synced': plant.synced, 'store': plant.in_store, 'creator': plant.creator.username, 'owner': plant.creator == request.user, 'configuration': []}
	configurations = plant.configurations.all()
	for configuration in configurations:
		config_json = {'after': configuration.after_date, 'temperature': {'min': configuration.temperature_min, 'max': configuration.temperature_max}, 'humidity': {'min': configuration.humidity_min, 'max': configuration.humidity_max}}
		response['configuration'].append(config_json)

	return response

def plants_to_json(plants, request):
	response = {'plants': []}
	for plant in plants:
		plant_json = plant_to_json(plant, request)
		response['plants'].append(plant_json)

	return response


def status(request):
	response = control.get_status()
	synced_plant = UserPlants.objects.get(user=request.user).plants.filter(synced=True).first()
	response['name'] = synced_plant.name

	return getJson(response)

def plants(request):
	user_plants = UserPlants.objects.filter(user=request.user)
	response = {'plants': []}

	for user_plant in user_plants:
		for plant in user_plant.plants.all():	
			plant_json = plant_to_json(plant, request)
			response['plants'].append(plant_json)

	return getJson(response)

@csrf_exempt
def config(request):
	if request.method == 'POST':
		#Create config
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		name = data['name']
		plant = Plant.objects.create(name=name, creator=request.user)
		user = request.user
		user_plants, created = UserPlants.objects.get_or_create(user=user)
		user_plants.plants.add(plant)
		for configuration in data['configuration']:
			after_date = configuration['after']
			temperature_min = configuration['temperature']['min']
			temperature_max = configuration['temperature']['max']
			humidity_min = configuration['humidity']['min']
			humidity_max = configuration['humidity']['max']
			configuration = Configuration.objects.create(after_date = after_date, temperature_min = temperature_min, temperature_max = temperature_max, humidity_min = humidity_min, humidity_max = humidity_max)
			plant.configurations.add(configuration)
			configuration.save()
		plant.save()
		user_plants.save()

		response = {'created': True}
		return getJson(response)
	else:
		return method_not_allowed()

@csrf_exempt
def edit_config(request, plant_id):
	if request.method == 'POST':
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		plant = Plant.objects.get(id=plant_id)
		plant.name = data['name']

		#Delete previous configuration
		for configuration in plant.configurations.all():
			plant.configurations.remove(configuration)
			configuration.delete()

		#Add the new configurations
		for configuration in data['configuration']:
			after_date = configuration['after']
			temperature_min = configuration['temperature']['min']
			temperature_max = configuration['temperature']['max']
			humidity_min = configuration['humidity']['min']
			humidity_max = configuration['humidity']['max']
			configuration = Configuration.objects.create(after_date = after_date, temperature_min = temperature_min, temperature_max = temperature_max, humidity_min = humidity_min, humidity_max = humidity_max)
			plant.configurations.add(configuration)
			configuration.save()

		response = {'edited': True}
		plant.save()
		return getJson(response)
	else:
		return method_not_allowed()



@csrf_exempt
def plant(request, pk):
	plant = Plant.objects.get(id=pk)
	configurations = plant.configurations.all()
	if request.method == 'GET':
		response = plant_to_json(plant, request)
		return getJson(response)
	elif request.method == "DELETE":
		#Check if the user is the owner
		if plant.creator == request.user:
			#If the user is the owner
			#Delete configurations
			for configuration in configurations:
				configuration.delete()
			#Delete plant
			plant.delete()
		else:
			user_plants, created = UserPlants.objects.get_or_create(user=request.user)
			user_plants.plants.remove(plant)
		response = {'deleted': True}
		return getJson(response)

@csrf_exempt
def sync(request, pk):
	if request.method == 'POST':
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		plant = Plant.objects.get(id=pk)
		synced_plants = Plant.objects.filter(synced=True)

		for synced in synced_plants:
			synced.synced = False
			synced.save()

		plant.synced = True
		after = int(data['after'])
		response = control.sync(plant.configurations.all(), after)
		
		plant.save()

	else:
		return method_not_allowed(request)
	
	return getJson(response)

@csrf_exempt
def share_in_store(request, pk):
	if request.method == 'POST':
		plant = Plant.objects.get(id = pk)
		plant.in_store = True
		plant.save()
		response = {'shared': True}
		return getJson(response)
	else:
		return method_not_allowed()

@csrf_exempt
def store_plants(request):
	if request.method == 'GET':
		plants = Plant.objects.filter(in_store=True)
		plants_json = plants_to_json(plants, request)
		return getJson(plants_json)
	else:
		return method_not_allowed(request)

@csrf_exempt
def add_to_account(request, pk):
	if request.method == 'POST':
		plant = Plant.objects.get(id = pk)
		user_plants, created = UserPlants.objects.get_or_create(user=request.user)
		user_plants.plants.add(plant)
		user_plants.save()
		response = {'added': True}
		return getJson(response)
	else:
		return method_not_allowed(request)

def user(request):
	user = request.user
	response = {'username': user.username}
	return getJson(response)

@csrf_exempt
def set_temperature(request):
	if request.method == 'POST':
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		temperature = data['temperature']
		responseData = {'temperature': control.set_temperature(temperature)}
		response = getJson(responseData)
	else:
		response = method_not_allowed()

	return response

@csrf_exempt
def set_humidity(request):
	if request.method == 'POST':
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		humidity = data['humidity']
		responseData = {'humidity': control.set_humidity(humidity)}
		response = getJson(responseData)
	else:
		response = method_not_allowed()

	return response