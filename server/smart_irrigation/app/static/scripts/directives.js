/*
 * Directives
 */

var Directives = angular.module('Directives', []);

Directives.directive('navbar', [function () {
	return {
		restrict: 'AE',
		templateUrl: '/static/views/partials/navbar.html',
		link: function (scope, iElement, iAttrs) {
			
		}
	};
}])