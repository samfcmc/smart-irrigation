/*
 * Base Controller
 * Every controller should inherit from 
 * this one
 */

App.controller('BaseCtrl', ['$scope', '$rootScope', 
	'$state',
	function ($scope, $rootScope, $state) {

		$rootScope.activeState = function(stateName) {
			return $state.includes(stateName);
		}
	
}]);