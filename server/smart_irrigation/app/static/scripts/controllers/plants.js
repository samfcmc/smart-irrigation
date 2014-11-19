/*
 * Plants Controller
 */
 App.controller('PlantsCtrl', ['$scope', '$controller',
	'PlantsResource', 'StoreResource',	
	function ($scope, $controller, PlantsResource, StoreResource) {

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

	  	$scope.share = function(plant) {
	  		StoreResource.share({id: plant.id},
	  			function(response) {
	  				if(response.shared) {
	  					plant.store = true;
	  				}
	  		});
	  	}

 }]);