
var App = angular.module('App', 
	['ui.bootstrap', 'ui.router',
	'ngResource',
	'Resources', 'Directives']);

App.config(['$stateProvider', '$urlRouterProvider',
	function ($stateProvider, $urlRouterProvider) {

		$urlRouterProvider.otherwise('/');

		$stateProvider.state('home', {
			url: '/',
			templateUrl: '/static/views/home.html',
			controller: 'HomeCtrl'
		});

		$stateProvider.state('plants', {
			url: '/plants',
			templateUrl: '/static/views/plants.html',
			controller: 'PlantsCtrl'
		})

		$stateProvider.state('create-config', {
			url: '/config',
			templateUrl: '/static/views/config.html',
			controller: 'CreateConfigCtrl'
		});

		$stateProvider.state('plant', {
			url: '/plant/{id}',
			templateUrl: '/static/views/config.html',
			controller: 'EditConfigCtrl'
		});

		$stateProvider.state('sync', {
			url: '/sync/{id}',
			templateUrl: '/static/views/sync.html',
			controller: 'SyncCtrl'
		});

		$stateProvider.state('store', {
			url: '/store',
			templateUrl: '/static/views/store.html',
			controller: 'StoreCtrl'
		})

}]);