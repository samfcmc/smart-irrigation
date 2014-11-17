# App urls
# Mapping between urls and views

from django.conf.urls import patterns, include, url

from app import views

urlpatterns = patterns('',
		url(r'^$', views.index, name='index'),
		url(r'^logout/', views.user_logout, name='logout'),
		url(r'^login/', views.user_login, name='login'),
		url(r'^api/status', views.status, name='status'),
		url(r'^api/plants', views.plants, name='plants'),
		url(r'^api/config', views.config, name='config'),
		url(r'^api/plant/(?P<pk>\d+)/$', views.plant, name='plant'),
)