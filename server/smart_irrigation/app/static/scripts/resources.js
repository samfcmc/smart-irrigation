var Resources = angular.module('Resources', []);

Resources.factory('StatusResource', 
	['$resource', 
	function ($resource) {
		var url = 'api/status';

		return $resource(url, {}, {
			'get': {method: 'GET'}
		});
}]);