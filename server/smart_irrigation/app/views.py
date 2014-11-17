from django.shortcuts import render
from django.http import HttpResponse
from django.contrib.auth import logout, login, authenticate
import json

# Return json
def getJson(response):
	return HttpResponse(json.dumps(response), content_type="application/json")

# Create your views here.
def index(request):
	if(request.user.is_authenticated()):
		view = 'index.html'
	else:
		view = 'login.html'

	return render(request, view)

def user_logout(request):
	logout(request)
	return index(request)

def user_login(request):
	if request.method == 'POST':
		username = request.POST['username']
		password = request.POST['password']

		user = authenticate(username=username, password=password)
		print(user)

		if user:
			if user.is_active:
				login(request, user)
	return index(request)


def status(request):
	response = {'name': 'Test',
				'temperature': 0,
				'humidity': 0}

	return getJson(response)