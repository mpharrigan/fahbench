'use strict';

angular.module('myApp.view1', ['ngRoute', 'ngResource'])

    .config(['$routeProvider', function ($routeProvider) {
        $routeProvider.when('/view1', {
            templateUrl: 'view1/view1.html',
            controller: 'View1Ctrl'
        });
    }])

    .controller('View1Ctrl', ['$scope', '$resource',
        function ($scope, $resource) {
            var Devices = $resource('/api/devices', {});
            Devices.get({}, function (data) {
                $scope.devices = data.devices;
            });

        }]);