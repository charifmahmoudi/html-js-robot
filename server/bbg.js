/**
 * Created by Charif on 20/03/2016.
 */

var WebSocketServer = require('websocket').server;
var http = require('http');
var b = require('bonescript');
function printJSON(x) { console.log(JSON.stringify(x)); }

var server = http.createServer(function(request, response) {
  // process HTTP request. Since we're writing just WebSockets server
  // we don't have to implement anything.
});
server.listen(1337, function() { });

// create the server
wsServer = new WebSocketServer({
  httpServer: server
});

function handleElem(e) {

  var pin = e.pin[0];
  var pin1 = e.pin[1];
  var pin2 = e.pin[2];
  var dir = e.dir;
  var value = e.value ;


  b.pinMode(pin, 'out');
  b.pinMode(pin1, 'out');
  b.pinMode(pin2, 'out');

  b.analogWrite(pin, 0.7, value, printJSON);
  b.digitalWrite(pin1, ! dir);
  b.digitalWrite(pin2, dir);
}

// WebSocket server
wsServer.on('request', function(request) {
  var connection = request.accept(null, request.origin);

  // This is the most important callback for us, we'll handle
  // all messages from users here.
  connection.on('message', function(message) {
    try {
      var json = JSON.parse(message.data);

      vhandleElem(json.left);
      handleElem(json.right);

    } catch (e) {
      console.log('This doesn\'t look like a valid JSON: ', message.data);
      return;
    }
    if (message.type === 'utf8') {
      analogWrite('P9_14', value);
      digitalWrite(pin1, ! dir);
      digitalWrite(pin2, dir);

      b.analogWrite('P9_14', 0.7, 2000, printJSON);

    }
  });

  connection.on('close', function(connection) {
    // close user connection
  });
});
