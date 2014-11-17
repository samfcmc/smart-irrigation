/*
 * Config Controller
 */

App.controller('ConfigCtrl', ['$scope', '$controller',
	'ConfigResource', 'PlantsResource', '$stateParams',
	function ($scope, $controller, ConfigResource, PlantsResource, $stateParams) {

		$controller('BaseCtrl', {$scope: $scope})

		$scope.configuration = {configuration: []};

		$scope.adding = false;

		if($stateParams.id) {
			//Load from resource
			PlantsResource.get({id: $stateParams.id},
				function(response) {
					$scope.configuration = response;
			});
		}

		$scope.startAdding = function() {
			$scope.adding = true;
		}

		$scope.cancelAdding = function() {
			$scope.adding = false;
		}

		$scope.addConfiguration = function(valid, configuration) {
			if(valid) {
				$scope.configuration.configuration.push(configuration);
				$scope.cancelAdding();	
			}
		}

		$scope.saveChanges = function() {
			ConfigResource.create($scope.configuration,
				function(response) {
					console.log(response);
				});
		}
	
}]);