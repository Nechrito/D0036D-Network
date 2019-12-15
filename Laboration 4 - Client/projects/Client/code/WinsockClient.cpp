#include "WinsockClient.h"
#include "CProtocol.h"
#include "Vector2.h"
#include <iostream>

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
	
	bool option = true;
	setsockopt(ClientSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&option, sizeof option);
	
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

	printf("Connect Result: %d\n", result);

	if (result)
	{
		printf("[getaddrinfo] Error: %d\n", WSAGetLastError());
		WSACleanup();
		closesocket(ClientSocket);
		return false;
	}

	int numbytes;
	result = numbytes = recv(ClientSocket, recieveBuffer, RECIEVE_BUFFER_SIZE, 0);
	if (result == -1)
	{
		std::cout << "Socket error: " << WSAGetLastError() << std::endl;
		perror("recv");
		exit(1);
	}

	if (numbytes < RECIEVE_BUFFER_SIZE)
	{
		recieveBuffer[numbytes] = '\0';
		printf("%s\n", recieveBuffer);
	}
	
	// threading
	receiveThread = std::thread(&WinsockClient::Recieve, this);
	
	return true;
}

void WinsockClient::Close()
{
	disconnect = true;

	receiveThread.join();

	closesocket(ClientSocket);
	WSACleanup();
}

void WinsockClient::Recieve()
{
	MsgHead head;
	while (!disconnect)
	{
		int bytesRecieved = recv(ClientSocket, recieveBuffer, RECIEVE_BUFFER_SIZE, 0);
		if (bytesRecieved == SOCKET_ERROR)
		{
			std::cout << WSAGetLastError() << std::endl;
			continue;
		}

		if (bytesRecieved > RECIEVE_BUFFER_SIZE)
			continue;
		
		std::cout << "Received " << bytesRecieved << " bytes\n";
		
		for (int offset = 0; offset < bytesRecieved; offset += (int)head.length)
		{
			memcpy(&head, &recieveBuffer[0] + offset, sizeof MsgHead);
			ReadBuffer(offset, head.length, head.type);
		}
	}
}

void WinsockClient::ReadChangeMsg(int offset, ChangeType type)
{
	std::cout << "1\n";
	switch (type)
	{
		case ChangeType::NewPlayer: break;
		case ChangeType::PlayerLeave: break;
		
		case ChangeType::NewPlayerPosition:
		{
				std::cout << "2\n";

				NewPlayerPositionMsg posMsg;
				memcpy(&posMsg, &recieveBuffer[0] + offset, sizeof NewPlayerPositionMsg);
				std::cout << "3\n";

				int x = ntohs(posMsg.dir.x);
				int y = ntohs(posMsg.dir.y);
				Vector2 newPos(x, y);
				std::cout << "4\n";

				this->moveCallback(newPos);
		}
		break;
		default: ;
	}
}

void WinsockClient::ReadBuffer(int offset, unsigned int length, MsgType msg)
{
	switch (msg)
	{
		case MsgType::Join:
			std::cout << "Join\n";
		
			JoinMsg joinMsg;
			memcpy(&joinMsg, &recieveBuffer[0] + offset, length);
		break;
		case MsgType::Leave: break;
		case MsgType::Change:
		{
			std::cout << "Change\n";

			ChangeMsg changeMsg;
			memcpy(&changeMsg, &recieveBuffer[0] + offset, sizeof ChangeMsg);
			ReadChangeMsg(offset, changeMsg.type);
		}
		break;
		case MsgType::Event:

		break;
		case MsgType::TextMessage: break;
		default: ;
	}
}


void WinsockClient::RequestMove(Vector2 pos, Vector2 dir)
{
	// cast to char for each struct
	// offset, length
	 
	MsgHead head =
	{
		sizeof MoveEvent,
		sequence,
		playerID,
		MsgType::Event
	};
	
	EventType type = { EventType::Move };
	EventMsg msg = { head, type };

	int posX = int(pos.X);
	int posY = int(pos.Y);
	Coordinate cPos = { htons(posX), htons(posY) };

	int dirX = int(dir.X);
	int dirY = int(dir.Y);
	Coordinate cDir = { htons(dirX), htons(dirY) };

	MoveEvent event = { msg, cPos, cDir };

	memcpy(&sendBuffer, &event, sizeof event);
	send(ClientSocket, sendBuffer, sizeof event, 0);

	sequence++;
}
