// var angular = require('angular');
// define global app
angular.module('App', ['Services']);

// create app router for url management/redirect
angular.module('App').config(function ($routeProvider) {
  $routeProvider.when('/frontpage', {
    templateUrl: 'partials/frontpage.html',
    controller: 'frontpage',
  });
  $routeProvider.when('/view', {
    templateUrl: 'partials/view.html',
    controller: 'view',
  });
  console.log('anglular config here :D');
  // $routeProvider.otherwise({redirectTo: '/frontpage'});
});

// frontpage controller
angular.module('App').controller('frontpage', function ($scope, Socket) {
  console.log('Hello from frontpage controller');
  //$scope.name = 'Something';
  Socket.on('hello', function(name, callback) {
    $scope.name = name;
    callback(false, {response: 'hello'});
  });
});
// view controller
angular.module('App').controller('view', function ($scope, Socket) {
  console.log('Hello from view controller');
  //send slider value to server
    $scope.sendSliderValue = function() {
      Socket.emit('slidervalue', $scope.myValue);
      console.log("value changed to " + $scope.myValue);
    }
    //get slidervalue from server
    //doesn't work simultaneously
    Socket.on('slidervalueFromServer', function (value) {
        $scope.myValue = value;
    })
//  }

});

// ****** SOCKETS ************************************************
// **FIRSTTESTs**/ CUSTOM
// connect socket
/* var socket = io.connect();
// socket testing
socket.on('hello', function (data, callback) {
  console.log('ohh, hello!');
  console.log(' hello ' + data);
  callback(false, {response: 'hello'});
}); */
// *****
//implementation by http://www.interaktionsdesigner.de/2013/die-killerapplikation-mit-node.js-socket.io-und-angularjs
//TODO: understand how this works
angular.module('Services', []).
	factory('Socket', function($rootScope) {
		var socket = io.connect();
		return {
			on: function(eventName, callback) {
				socket.on(eventName, function() {
					var args = arguments;
					$rootScope.$apply(function() {
						callback.apply(socket, args);
					});
				});
			},
			emit: function(eventName, data, callback) {
				if(typeof data == 'function') {
					callback = data;
					data = {};
				}
				socket.emit(eventName, data, function() {
					var args = arguments;
					$rootScope.$apply(function() {
						if(callback) {
							callback.apply(socket, args);
						}
					});
				});
			},
			emitAndListen: function(eventName, data, callback) {
				this.emit(eventName, data, callback);
				this.on(eventName, callback);
			}
		};
	});
