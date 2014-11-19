from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class Configuration(models.Model):
	after_date = models.IntegerField()
	temperature_min = models.IntegerField()
	temperature_max = models.IntegerField()
	humidity_min = models.IntegerField()
	humidity_max = models.IntegerField()

class Plant(models.Model):
	name = models.CharField(max_length=200)
	configurations = models.ManyToManyField(Configuration)
	synced = models.BooleanField(default=False)
	in_store = models.BooleanField(default=False)
	creator = models.ForeignKey(User)

class UserPlants(models.Model):
	user = models.ForeignKey(User)
	plants = models.ManyToManyField(Plant)
