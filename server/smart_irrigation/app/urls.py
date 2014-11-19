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
		url(r'^api/config/(?P<plant_id>[0-9]+)/?$', views.edit_config, name='edit config'),
		url(r'^api/config', views.config, name='config'),
		url(r'^api/plant/(?P<pk>\d+)/?$', views.plant, name='plant'),
		url(r'^api/sync/(?P<pk>\d+)/?$', views.sync, name='sync'),
		url(r'^api/store/', views.store_plants, name='store'),
		url(r'^api/share/(?P<pk>\d+)/?$', views.share_in_store, name='share in store'),
		url(r'^api/account/(?P<pk>\d+)/?$', views.add_to_account, name='add to account'),
		url(r'^api/user', views.user, name='user'),
)