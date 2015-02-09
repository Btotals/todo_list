http = require 'http'
server = http.createServer (req, res)!->
  res.writeHead('content-type': 'text/plain')
  res.end('Hello World!')

console.log 'server running on 3000'

server.listen 3000 'localhost'
