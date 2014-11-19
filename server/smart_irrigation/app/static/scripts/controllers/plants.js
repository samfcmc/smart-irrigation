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

	  	$scope.deletePlant = function(plant) {
	  		PlantsResource.deletePlant({id: plant.id},
	  			function(response) {
	  				var index = $scope.plants.indexOf(plant);
	  				$scope.plants.splice(index, 1);
	  		});
	  	}

	  	

 }])