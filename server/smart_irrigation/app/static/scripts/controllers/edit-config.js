/*
 * Edit Configuration Controller
 */

App.controller('EditConfigCtrl', ['$scope', '$controller',
	'$stateParams', 'PlantsResource',
	function ($scope, $controller, $stateParams, PlantsResource) {

		$controller('ConfigCtrl', {$scope: $scope});

		if($stateParams.id) {
			//Load from resource
			PlantsResource.get({id: $stateParams.id},
				function(response) {
					$scope.configuration = response;
			});
		}

}]);