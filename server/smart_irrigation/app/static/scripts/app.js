
var App = angular.module('App', 
	['ui.bootstrap', 'ui.router']);

App.config(['$stateProvider', '$urlRouterProvider',
	function ($stateProvider, $urlRouterProvider) {

		$urlRouterProvider.otherwise('/');

		$stateProvider.state('home', {
			url: '/',
			templateUrl: '/static/views/home.html'
		});

}]);