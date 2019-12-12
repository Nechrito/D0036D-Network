#pragma once

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#ifndef SOL_SOCKET
#define SOL_SOCKET 1
#endif

#ifndef SO_REUSEADDR
#define SO_REUSEADDR 2
#endif

#ifndef SO_KEEPALIVE
#define SO_KEEPALIVE 9
#endif

#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   
#include <arpa/inet.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> 

#define PORT 49152  

class SimpleServer
{
private:
	
public:

	SimpleServer();


	~SimpleServer() = default; 
};

