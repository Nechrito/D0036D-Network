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

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>   
#include <arpa/inet.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> 

constexpr auto PORT = 49152;

constexpr auto BUFFER_SIZE = 1024;
constexpr auto MAX_CLIENTS_ALLOWED = 4;

class SimpleServer
{
private:
	
public:

	SimpleServer();


	~SimpleServer() = default; 
};

