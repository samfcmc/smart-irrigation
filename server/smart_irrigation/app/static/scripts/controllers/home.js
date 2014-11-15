/*
 * Home Controller
 */

App.controller('HomeCtrl', ['$scope', '$controller',
	'StatusResource', 
	function ($scope, $controller, StatusResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.status = {};

		StatusResource.get({}, 
			function(response) {
				$scope.status = response;
			})

}]);