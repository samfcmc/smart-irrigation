
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

		$stateProvider.state('config', {
			url: '/config',
			templateUrl: '/static/views/config.html',
			controller: 'ConfigCtrl'
		});

}]);