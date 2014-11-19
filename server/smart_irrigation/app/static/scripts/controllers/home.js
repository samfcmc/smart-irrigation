/*
 * Home Controller
 */

App.controller('HomeCtrl', ['$scope', '$controller',
	'$timeout', 'StatusResource', 
	function ($scope, $controller, $timeout, StatusResource) {

		$controller('BaseCtrl', {$scope: $scope});

		$scope.status = {};

		$scope.initStatus = function() {
			console.log('Checking status');
			StatusResource.get({}, 
				function(response) {
					$scope.status = response;
					$timeout(function(){
						$scope.initStatus();
					}, 10000);
			});
		}

		$scope.initStatus();

}]);