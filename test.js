var http = require('http');
var server = http.createServer(function(req, res) {
  res.writeHead(200, {'content-type': 'text/plain'});
  res.end('Hello World!');
});

server.listen(3000, 'localhost');

console.log('server running on 3000');
