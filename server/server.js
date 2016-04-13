var connect = require('connect');
var serveStatic = require('serve-static');
var socket = require('socket.io');

//save connect in app
var server = connect()
  .use(serveStatic(__dirname + '/../client/'))
  .listen(3000);
console.log('server started and listens to 192.168.2.4:3000');

//init socket
var io = socket.listen(server);
io.sockets.on('connection', function(socket) {
  console.log('client connected');
});

//** SOCKET COMMUNICATION ***
io.sockets.on('connection', function(socket) {
//communicate about daniel
  setTimeout(function() {
		socket.emit('hello', 'Daniel', function (err, response) {
      console.log('recieved an answer' + response);
    console.log("change name to daniel");
  })
	}, 3000);
// communicate about slidervalue
socket.on('slidervalue', function(value) {
  console.log("slider changed. new value " + value);
});

// change slidervalue via STDINPUT (cli)
//STDINPUT
  var stdin = process.openStdin();
  stdin.addListener("data", function(d) {
      // note:  d is an object, and when converted to a string it will
      // end with a linefeed.  so we (rather crudely) account for that
      // with toString() and then trim()
      console.log("you entered: [" +
          d.toString().trim() + "]");
          var value = Number(d);
          console.log(value);
          if (value != NaN)
          {
            socket.emit('slidervalueFromServer', value, function (err, response) {
              console.log('recieved an answer' + response);
              console.log("change slider to " + value);
            });
          }
    });
});
