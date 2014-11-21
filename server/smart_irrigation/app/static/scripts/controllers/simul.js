/*
 * Simulation Controller
 */

App.controller('SimulCtrl', ['$scope', '$controller', 'SimulResource', 
	function ($scope, $controller, SimulResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.setTemperature = function(valid, simul) {
			if(valid) {
				SimulResource.temperature({}, simul,
					function(response) {
						console.log(response);
				});
			}
		}

		$scope.setHumidity = function(valid, simul) {
			if(valid) {
				SimulResource.humidity({}, simul,
					function(response) {
						console.log(response);
				});
			}
		}
}]);