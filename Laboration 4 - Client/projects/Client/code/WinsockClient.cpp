#include "WinsockClient.h"

WinsockClient::WinsockClient()
{
	
}

bool WinsockClient::ConnectToServer()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result)
	{
		printf("[WSAStartup] Error: %d\n", result);
		return false;
	}

	ZeroMemory(&hints, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// assigns the ip & port
	result = getaddrinfo(IP, PORT, &hints, &addressInfo);
	if (result)
	{
		printf("[getaddrinfo] Error: %d\n", result);
		WSACleanup();
		return false;
	}

	// iterates through possible addresses with the attempt to connect with one of them
	for (addrinfo* address = addressInfo; address != nullptr; address = address->ai_next)
	{
		// assigns our socket to the current element
		ClientSocket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("[Socket] Error: %d\n", result);
			WSACleanup();
			return false;
		}

		// attempts to connect to the server
		result = connect(ClientSocket, address->ai_addr, (int)address->ai_addrlen);
		if (result == SOCKET_ERROR)
		{
			closesocket(ClientSocket);
			ClientSocket = INVALID_SOCKET;
			continue; // continues to the next element as this one didn't work out
		}

		// as we've connected without any errors, we can break free from the loop 
		break;
	}

	// frees the allocated memory as it no longer serves a purpose
	freeaddrinfo(addressInfo);

	if (ClientSocket == INVALID_SOCKET)
	{
		printf("[Connection] Error: %d\n", result);
		WSACleanup();
		return false;
	}

	printf("Sucessfully connected to the server!\n");
	return true;
}

void WinsockClient::Update()
{
	
}

void WinsockClient::Close() const
{
	closesocket(ClientSocket);
	WSACleanup();
}
