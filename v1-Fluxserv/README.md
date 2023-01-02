# This is the second version of the Flux server.

This server is a redesigned version that is optimized for speed and scalability. It uses threads to improve its performance and can handle a high number of requests. The server is able to retrieve data from the requested file. The main processing occurs in the "handle_connection" function, which can be easily modified to add new behaviors. The server uses a thread pool to perform its tasks concurrently, but without creating an excessive number of threads that could slow or crash the server.

## Issues
However, it is important to note that this server is not secure, as clients can access the entire machine, and it is vulnerable to DDOS attacks.

## Use
Once the server compiled and running use the "manyclients.bash" script to lunch multiple ruby connection to see how the server works.
time ./manyclients.bash -- to see performance