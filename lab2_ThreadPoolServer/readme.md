This lab contains 6 classes, they are:
ThreadSafeKVStore, ThreadSafeListenerQueue
ThreadPoolServer
httpreq, httpresp(used to parse http request and response)
md5(used to return hash value)

When we create a threadpool, several threads have been launched and running forever while listening jobs from ThreadSafeListenerQueue. In the run function inside ThreadPoolServer, threads receive jobs, parse request, modify the key value store, and then return a response.
There are function called handleconn() inside ThreadPoolServer, which used to open a socket and bind with server while keep accepting new socket and push them into ThreadSafeQueue, waiting for thread deal with.

PS: the default port number for this class is 8889, which can be seen in ThreadPoolServer.