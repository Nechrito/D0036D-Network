#include "WinsockClient.h"
#include "CProtocol.h"
#include "Vector2D.h"

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
	if (result)
	{
		printf("[getaddrinfo] Error: %d\n", WSAGetLastError());
		WSACleanup();
		closesocket(ClientSocket);
		return false;
	}
	
	int numbytes;
	const int size = 512;
	char buf[size];
	if ((numbytes = recv(ClientSocket, buf, size - 1, 0)) == -1)
	{
		perror("recv");
		exit(1);
	}

	buf[numbytes] = '\0';
	printf("Received '%s'\n", buf);
	
	
	return true;
}

void WinsockClient::Close() const
{
	closesocket(ClientSocket);
	WSACleanup();
}

void WinsockClient::RequestMove(Vector2D pos, Vector2D dir)
{
	MsgHead head = 
	{
		
	};
	EventType type = { EventType::Move };
	EventMsg msg = { head, type };

	int posX = int(pos.X);
	int posY = int(pos.Y);
	Coordinate cPos = { posX, posY};

	int dirX = int(dir.X);
	int dirY = int(dir.Y);
	Coordinate cDir = { dirX, dirY };
	
	MoveEvent event = { msg, cPos, cDir };

	char* buf = new char[sizeof event];
	memcpy(&buf, &event, sizeof event);
	send(ClientSocket, buf, sizeof buf, 0);

	delete[] buf;
}
