/*
 * Sync Controller
 */

App.controller('SyncCtrl', ['$scope', '$controller',
	'$stateParams', '$state', 'PlantsResource',
	function ($scope, $controller, $stateParams, 
		$state, PlantsResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.sync = function(valid, syncData) {
			if(valid) {
		  		PlantsResource.sync({id: $stateParams.id},
		  			{after: syncData.days},
		  			function(response) {
		  				$state.go('plants');
		  		});
			}
	  	}
}]);