# App urls
# Mapping between urls and views

from django.conf.urls import patterns, include, url

from app import views

urlpatterns = patterns('',
		url(r'^$', views.index, name='index'),
		url(r'^api/status', views.status, name='status'),
)