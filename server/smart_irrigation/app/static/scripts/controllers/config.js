/*
 * Config Controller
 */

App.controller('ConfigCtrl', ['$scope', '$controller', 
	function ($scope, $controller) {

		$controller('BaseCtrl', {$scope: $scope})

		$scope.configuration = {
			name: 'Name',
			configuration: []
		};

		$scope.adding = false;

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

		}
	
}]);