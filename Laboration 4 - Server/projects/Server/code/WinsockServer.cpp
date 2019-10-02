#include "WinsockServer.h"
#include <thread>

void WinsockServer::AllowConnections()
{
	// accepts an incoming client connection 
	SOCKET incomingSocket = accept(ServerSocket, nullptr, nullptr);
	if (incomingSocket == INVALID_SOCKET)
	{
		printf("[Accept] Error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

}

WinsockServer::WinsockServer()
{
	printf("Initializing API...\n");

	// Initializes the Winsock API at version 2.2 
	WSADATA wsadata;
	int result = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (result)
	{
		printf("[WSAStartup] Error: %d\n", result);
		return;
	}

	// specifies the values in terms of the 'sockaddr' structure
	// initializes the destination address with the size 
	ZeroMemory(&hints, sizeof hints);
	hints.ai_family = AF_UNSPEC; // Allows both IPv4 & IPv6 
	hints.ai_socktype = SOCK_STREAM; // Type of socket, in this case stream
	hints.ai_protocol = IPPROTO_TCP; // We want to use TCP 
	hints.ai_flags = AI_PASSIVE; // Indicates that the client(s) intends to use the returned structure in a bind function
	
	// resolves the address & port 
	result = getaddrinfo(nullptr, PORT, &hints, &address);
	if (result)
	{
		printf("[getaddrinfo] Error: %d\n", result);
		WSACleanup();
		return;
	}

	// creates the socket which allows the server to listen to client connections
	if ((ServerSocket = socket(address->ai_family, address->ai_socktype, address->ai_protocol)) == INVALID_SOCKET)
	{
		printf("[Socket] Error: %d\n", WSAGetLastError());
		freeaddrinfo(address);
		WSACleanup();
		return;
	}

	// allows multiple connections to get through
	int opt = 1;
	if (setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof opt) < 0)
	{
		printf("[setsockopt] Error: %d\n", WSAGetLastError());
		return;
	}

	// binds the socket to a network address 
	if (bind(ServerSocket, address->ai_addr, (int)address->ai_addrlen) == SOCKET_ERROR)
	{
		printf("[Bind] Error: %d\n", WSAGetLastError());
		freeaddrinfo(address);
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

	// since we're done with this, we'll remove it 
	freeaddrinfo(address);

	// Instructs the server to accept 3 pending connections
	if (listen(ServerSocket, 3) == SOCKET_ERROR)
	{
		printf("[Listen] Error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

	printf("Initialized successfully!\n\n");
}

void WinsockServer::Update()
{
	
}

void WinsockServer::Close() const
{
	/*
	if (shutdown(ClientSocket, SD_SEND) == SOCKET_ERROR)
	{
		printf("[Shutdown] Error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}

	closesocket(ClientSocket);
	WSACleanup();*/
}
