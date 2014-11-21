/*
 * Home Controller
 */

App.controller('HomeCtrl', ['$scope', '$controller',
	'$timeout', 'StatusResource', 
	function ($scope, $controller, $timeout, StatusResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.status = {};
		$scope.timer = {};

		$scope.initStatus = function() {
			console.log('Checking status');
			StatusResource.get({}, 
				function(response) {
					$scope.status = response;
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