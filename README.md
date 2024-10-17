## MultiThreaded Proxy Server with Cache
This is a multithreaded proxy server implemented in C, which handles HTTP requests using the GET method. The proxy server caches the responses to improve performance by serving repeated requests from the cache.

# Features
Multithreading: Supports handling multiple clients simultaneously using threads.
LRU Caching: Implements a Least Recently Used (LRU) caching mechanism to store and serve requests faster when repeated.
Semaphore and Mutex: Uses semaphores and mutex locks to control concurrent access to shared resources and ensure thread safety.
Error Handling: Handles invalid requests and sends appropriate error messages back to the client.
# Prerequisites
To run this project, ensure you have the following installed:
GCC compiler
pthread library for multithreading
socket programming libraries

You can install the necessary packages with the following commands (for Debian-based systems):
```
sudo apt update
sudo apt install build-essential
sudo apt install gcc libpthread-stubs0-dev
```
# How to Build
To compile the proxy server, navigate to the project directory and run the following command:
```
gcc -pthread -o Proxy_Server_With_Cache main.c HeaderFiles/proxy_parse.c -I HeaderFiles -lpthread
```
This will generate an executable named Proxy_Server_With_Cache.
# How to Run
To start the server, run the compiled executable and provide the desired port number as an argument:
```
./Proxy_Server_With_Cache <PORT_NUMBER>
```
For example, to run the server on port 8080:
```
./Proxy_Server_With_Cache 8080
```
# Code Overview
Key Components
Main Function: Sets up the socket, binds it to the specified port, and listens for incoming client connections.

Thread Function: Each client connection is handled in a separate thread (thread_fn), which processes the HTTP request and checks the cache for a response.

Caching Mechanism: Uses a linked list to store cached responses, and employs the LRU (Least Recently Used) strategy to evict old cache entries when the cache is full.

Semaphore and Mutex: Ensures thread-safe access to shared resources like the cache, and limits the number of clients that can connect at once.

# Functions
find(char *url): Searches the cache for a stored response for a given URL.

add_cache_element(char *data, int size, char *url): Adds a new cache element.

remove_cache_element(): Removes the least recently used element when the cache is full.

thread_fn(void *socketNew): Handles the client requests in a new thread.

ParsedRequest_create(), ParsedRequest_parse(), ParsedRequest_destroy(): Functions to parse and manage the HTTP request.

# Client Connection
The server listens for incoming client connections on the specified port. When a client connects:

It accepts the client connection, logs the client's IP address and port.
It spawns a new thread to handle the client's request.
If the request is a cache hit, the server responds from the cache.
If not, the server fetches the data from the requested URL, caches the response, and forwards it to the client.
# Error Handling
If the client sends an invalid request, the server returns an HTTP 500 error.
The server supports only the GET method.