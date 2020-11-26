var http = require('http');
var url = require('url');
var StringDecoder = require('string_decoder').StringDecoder;

var port = 3000;
var server = http.createServer(function(req, res){
    unifiedServer(req, res);
});

server.listen(port, function(){
    console.log("Server listening on port " + port);
});

var handlers = {};
handlers.hello = function(data, callback){
    callback(200, {message: "Hello!"});
};

handlers.notfound =  function(data, callback){
    callback(404);
};

var router = {
    'hello': handlers.hello
};

function unifiedServer(req,res){
   var parsedUrl = url.parse(req.url, true);
   var path = parsedUrl.pathname;
   var trimmedPath = path.replace(/^\/+|\/+$/g, '');
   var method = req.method.toLowerCase();
   var buffer = '';
   var headers = req.headers;
   var queryStringObject = parsedUrl.query;
   var decoder = new StringDecoder('utf-8');

   req.on('data', function(data){
       buffer += decoder.write(data);
   });

   req.on('end', function(){

        buffer += decoder.end();
        var chosendHandler = typeof(router[trimmedPath.toLowerCase()]) != 'undefined' ? router[trimmedPath.toLowerCase()] : handlers.notfound;
        console.log("Chosen path: " + trimmedPath);
        console.log("Router ", router);
        var data = {
            'trimmedPath' : trimmedPath,
            'queryStringObject': queryStringObject,
            'method': method,
            'header': headers,
            'payload': buffer
        };
        var dataString =  JSON.stringify(data);

        console.log("received this payload: ", dataString);

        chosendHandler(data, function(statusCode, payload){
            statusCode = typeof(statusCode) == 'number' ? statusCode : 200;
            payload = typeof(payload) == 'object' ? payload : {};
            var payloadString = JSON.stringify(payload);
            res.setHeader('Content-Type', 'application/json')
            res.writeHead(statusCode);
            res.end(payloadString);
            console.log('Returning this response', statusCode, payloadString);
        });
    });
}



