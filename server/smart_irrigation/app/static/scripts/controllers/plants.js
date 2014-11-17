/*
 * Plants Controller
 */
 App.controller('PlantsCtrl', ['$scope', '$controller',
	'PlantsResource',	
	function ($scope, $controller, PlantsResource) {

	  	$controller('BaseCtrl', {$scope: $scope});

	  	$scope.plants = [];

	  	PlantsResource.list({}, function(response) {
	  		$scope.plants = response.plants;
	  	});

 }])