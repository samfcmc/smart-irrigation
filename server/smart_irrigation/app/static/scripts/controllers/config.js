/*
 * Config Controller
 */

App.controller('ConfigCtrl', ['$scope', '$controller',
	'ConfigResource', '$stateParams',
	function ($scope, $controller, ConfigResource, $stateParams) {

		$controller('BaseCtrl', {$scope: $scope})

		$scope.configuration = {configuration: []};

		$scope.adding = false;

		if($stateParams.id) {
			//Load from resource
			console.log($stateParams.id);
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