#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdio>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

constexpr auto IP = "130.240.40.7"; 

class WinsockClient
{
private:

	SOCKET ClientSocket = INVALID_SOCKET; // our socket which connects to the server
	struct addrinfo hints; // contains properties for our connection
	struct addrinfo* addressInfo; // retrieves data used to assign the socket
	struct sockaddr_in serverAddr, senderInfo;
	
	unsigned int PORT = 49153;
	
public:

	WinsockClient() = default;

	bool ConnectToServer();
	
	
	void Update();

	void Close() const;

	~WinsockClient() = default;
	
};

