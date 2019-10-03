#include "WinsockClient.h"

bool WinsockClient::ConnectToServer()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result)
	{
		printf("[WSAStartup] Error: %d\n", result);
		return false;
	}

	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("[Socket] Error: %d\n", WSAGetLastError());
		WSACleanup();
		return false;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	char str[INET_ADDRSTRLEN];
	inet_pton(AF_INET, IP, &serverAddr.sin_addr);

	inet_ntop(AF_INET, &serverAddr.sin_addr, str, INET_ADDRSTRLEN);
	printf("%s\n", str);

	result = connect(ClientSocket, (sockaddr*)&serverAddr, sizeof serverAddr);
	if (result != 0)
	{
		printf("[getaddrinfo] Error: %d\n", WSAGetLastError());
		WSACleanup();
		closesocket(ClientSocket);
		return false;
	}
	
	printf("Sucessfully connected to the server!\n\n");
	return true;
}

void WinsockClient::SendCommand()
{
	
}

void WinsockClient::Update()
{
	
}

void WinsockClient::Close() const
{
	closesocket(ClientSocket);
	WSACleanup();
}
