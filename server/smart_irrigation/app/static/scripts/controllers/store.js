/*
 * Store Controller
 */

App.controller('StoreCtrl', ['$scope', '$controller',
	'$state', 'StoreResource', 'AccountResource',
	function ($scope, $controller, $state, StoreResource, AccountResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.plants = []

		StoreResource.list({}, function(response) {
			$scope.plants = response.plants;
		});

		$scope.addToAccount = function(plant) {
			AccountResource.addPlant({id: plant.id},
				{},
				function(response) {
					$state.go('plants');
			});
		}
}]);
