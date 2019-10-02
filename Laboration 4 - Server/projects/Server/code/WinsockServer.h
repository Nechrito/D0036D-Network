#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include "ClientSocket.h"
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

constexpr auto PORT = "49153";
constexpr auto IP = "130.240.40.7"; 

class WinsockServer
{
private:
	
	struct addrinfo hints;
	struct addrinfo* address;
	
	SOCKET ServerSocket = INVALID_SOCKET; 
	//std::vector<ClientSocket> clients; 
	
	void AllowConnections();
	
public:

	WinsockServer();

	void Update();
	
	void Close() const;
	
	~WinsockServer() = default;
};