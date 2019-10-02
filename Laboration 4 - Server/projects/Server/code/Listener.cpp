#include "Listener.h"
#include <thread>

Listener::Listener()
{
	// Initializes the Winsock API at version 2.2 
	int result = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (result != 0)
	{
		printf("[WSAStartup] Error: %d\n", result);
	}

	// specifies the values in terms of the 'sockaddr' structure
	// initializes the destination address with the size 
	ZeroMemory(&socketAddress, sizeof socketAddress);
	socketAddress.ai_family = AF_INET; // IPv4 
	socketAddress.ai_socktype = SOCK_STREAM; // Type of socket, in this case stream
	socketAddress.ai_protocol = IPPROTO_TCP; // We want to use TCP 
	socketAddress.ai_flags = AI_PASSIVE; // Indicates that the client(s) intends to use the returned structure in a bind function

	// resolves the address & port 
	result = getaddrinfo(nullptr, PORT, &socketAddress, &addressInfo);
	if (result != 0)
	{
		printf("[getaddrinfo] Error: %d\n", result);
		WSACleanup();
		return;
	}

	// creates the socket which allows the server to listen to client connections
	ServerSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (ServerSocket == INVALID_SOCKET)
	{
		printf("[Socket] Error: %d\n", WSAGetLastError());
		freeaddrinfo(addressInfo);
		WSACleanup();
		return;
	}

	// binds the socket to a network address 
	result = bind(ServerSocket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		printf("[Bind] Error: %d\n", WSAGetLastError());
		freeaddrinfo(addressInfo);
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

	// since we're done with this, we'll remove it 
	freeaddrinfo(addressInfo);

	// Instructs the server to accept a fair amount of pending connections
	if (listen(ServerSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("[Listen] Error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

	
	
	printf("Created the socket");
}

void Listener::Update()
{
	// accepts an incoming client connection 
	ClientSocket = accept(ServerSocket, nullptr, nullptr);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("[Accept] Error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return;
	}

	// receive as long as the connection is upheld 
	int bufferSize = 512;
	char* buffer = new char[bufferSize];
	int result = recv(ClientSocket, buffer, bufferSize, 0);

	if (result > 0)
	{
		printf("Received %d", result);
		printf(" Bytes!\n");
		
	}
	else
	{
		printf("Failed to receive data, shutting down...%d\n", WSAGetLastError());
	}
}


void Listener::AcceptPacket()
{
	
}

void Listener::Close()
{
	if (shutdown(ClientSocket, SD_SEND) == SOCKET_ERROR)
	{
		printf("[Shutdown] Error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}

	closesocket(ClientSocket);
	WSACleanup();
}