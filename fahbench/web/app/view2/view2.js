'use strict';

angular.module('myApp.view2', ['ngRoute'])

    .config(['$routeProvider', function ($routeProvider) {
        $routeProvider.when('/view2', {
            templateUrl: 'view2/view2.html',
            controller: 'View2Ctrl'
        });
    }])

    .controller('View2Ctrl', ['$scope', '$resource',
        function ($scope, $resource) {

            var Version = $resource('/api/version', {});
            Version.get({}, function (data) {
                $scope.version = data;
            });

        }]);