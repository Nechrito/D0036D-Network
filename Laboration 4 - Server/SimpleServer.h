#pragma once

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

#define PORT 49154  

class SimpleServer
{
private:
	
public:

	SimpleServer();


	~SimpleServer() = default; 
};
