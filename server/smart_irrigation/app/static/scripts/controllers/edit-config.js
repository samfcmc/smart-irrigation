/*
 * Edit Configuration Controller
 */

App.controller('EditConfigCtrl', ['$scope', '$controller',
	'$stateParams', '$state', 'PlantsResource', 'ConfigResource',
	function ($scope, $controller, $stateParams, $state, PlantsResource, ConfigResource) {

		$controller('ConfigCtrl', {$scope: $scope});

		if($stateParams.id) {
			//Load from resource
			PlantsResource.get({id: $stateParams.id},
				function(response) {
					$scope.configuration = response;
			});
		}

		$scope.saveChanges = function() {
			ConfigResource.edit({id: $stateParams.id},
				$scope.configuration,
				function(response) {
					$state.go('plants');
			})
		}

}]);