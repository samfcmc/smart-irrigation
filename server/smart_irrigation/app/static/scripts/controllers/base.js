/*
 * Base Controller
 * Every controller should inherit from 
 * this one
 */

App.controller('BaseCtrl', ['$scope', '$rootScope', 
	'$state', 'UserResource',
	function ($scope, $rootScope, $state, UserResource) {

		$rootScope.activeState = function(stateName) {
			return $state.includes(stateName);
		}

		$rootScope.initUser = function() {
			UserResource.get({},
				function(response) {
					$rootScope.user = response;
			})
		}
	
}]);