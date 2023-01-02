# This is the first version of the Flux server.

This directory contains a very basic web client aswell as a basic webserver.
Further version will upgrade this one but going through simpler version may be usefull.

## Client
This web client is really really basic. It will retrieve a server response for a simple
"GET / HTTP/1.1" request. Once the response received it will output it to the terminal,
really nothing fancy. This code is not secure and does nothing special, it purpose is
the get an idea of how a client must connect to a server. With this base, communications
between client and server might go further.

## Server
This server is also very basic. It will output the request to the terminal and will respond
every time with just a "Hello" message. Very boring server but it allows to see what is actually
inside a request and a response. Also this server is not secure at all but has a handy way
to output the data. This server can be accessed by a traditionnal web browser.