from django.shortcuts import render
from django.http import HttpResponse
import json

# Return json
def getJson(response):
	return HttpResponse(json.dumps(response), content_type="application/json")

# Create your views here.
def index(request):
	return render(request, 'index.html')

def status(request):
	response = {'name': 'Test',
				'temperature': 0,
				'humidity': 0}

	return getJson(response)