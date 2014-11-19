from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt

from django.contrib.auth import logout, login, authenticate
from app.models import UserPlants, Plant, Configuration
import json

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
def status(request):
	response = {'name': 'Test',
				'temperature': 0,
				'humidity': 0}

	return getJson(response)

def plants(request):
	user_plants = UserPlants.objects.filter(user=request.user)
	response = {'plants': []}

	for user_plant in user_plants:
		for plant in user_plant.plants.all():	
			plant_json = {'id': plant.id, 'name': plant.name, 'synced': plant.synced}
			response['plants'].append(plant_json)

	return getJson(response)

@csrf_exempt
def config(request):
	if request.method == 'POST':
		#Create config
		json_str = request.body.decode(encoding='UTF-8')
		data = json.loads(json_str)
		name = data['name']
		plant = Plant.objects.create(name=name)
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
		return HttpResponse('Wrong method!')

@csrf_exempt
def plant(request, pk):
	plant = Plant.objects.get(id=pk)
	configurations = plant.configurations.all()
	if request.method == 'GET':
		response = {'name': plant.name, 'synced': plant.synced, 'configuration': []}
		for configuration in configurations:
			config_json = {'after': configuration.after_date, 'temperature': {'min': configuration.temperature_min, 'max': configuration.temperature_max}, 'humidity': {'min': configuration.humidity_min, 'max': configuration.humidity_max}}
			response['configuration'].append(config_json)

		return getJson(response)
	elif request.method == "DELETE":
		#Delete configurations
		for configuration in configurations:
			configuration.delete()
		#Delete plant
		plant.delete()
		response = {'deleted': True}
		return getJson(response)

@csrf_exempt
def sync(request, pk):
	if request.method == 'POST':
		plant = Plant.objects.get(id=pk)
		synced_plants = Plant.objects.filter(synced=True)

		for synced in synced_plants:
			synced.synced = False
			synced.save()

		plant.synced = True
		plant.save()

		#TODO: Use Irrigation Control
		response = {'synced': True}
	else:
		response = {'error': 'method not allwoed'}
	
	return getJson(response)



