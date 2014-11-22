/*
 * Home Controller
 */

App.controller('HomeCtrl', ['$scope', '$controller',
	'$timeout', 'StatusResource', 'ConfigResource',
	function ($scope, $controller, $timeout, StatusResource, ConfigResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.status = {};
		$scope.configuration = {};
		$scope.timer = {};

		$scope.initStatus = function() {
			StatusResource.get({}, 
				function(response) {
					$scope.status = response;
					$scope.configuration = response.configuration
					$scope.timer = $timeout(function(){
						$scope.initStatus();
					}, 10000);
			});
		}

		$scope.$on('$destroy', function(event) {
			$timeout.cancel($scope.timer);
		});

		$scope.initStatus();

}]);