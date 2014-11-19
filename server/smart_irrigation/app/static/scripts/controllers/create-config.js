/*
 * Create Configuration Controller 
 */

App.controller('CreateConfigCtrl', ['$scope', '$controller',
	'$stateParams', '$state', 'ConfigResource',
	function ($scope, $controller, $stateParams, $state, ConfigResource) {

		$controller('ConfigCtrl', {$scope: $scope});

		

		$scope.saveChanges = function() {
			ConfigResource.create($scope.configuration,
				function(response) {
					$state.go('plants', {});
				});
		}
}]);