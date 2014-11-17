
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

		$stateProvider.state('config', {
			url: '/config',
			templateUrl: '/static/views/config.html',
			controller: 'ConfigCtrl'
		});

		$stateProvider.state('plant', {
			url: '/plant/{id}',
			templateUrl: '/static/views/config.html',
			controller: 'ConfigCtrl'
		})

}]);