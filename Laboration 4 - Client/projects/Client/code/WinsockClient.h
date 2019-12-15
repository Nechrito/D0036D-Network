#pragma once
#define WIN32_LEAN_AND_MEAN

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

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdio>
#include <string>
#include "Vector2.h"
#include "CProtocol.h"
#include <functional>
#include <thread>
#include <atomic>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

constexpr auto IP = "130.240.40.7";

#define RECIEVE_BUFFER_SIZE 1024
#define SEND_BUFFER_SIZE 512

class WinsockClient
{
private:

	SOCKET ClientSocket = INVALID_SOCKET; // our socket which connects to the server
	struct addrinfo hints; // contains properties for our connection
	struct addrinfo* addressInfo; // retrieves data used to assign the socket
	struct sockaddr_in serverAddr, senderInfo;

	char sendBuffer[SEND_BUFFER_SIZE];
	char recieveBuffer[RECIEVE_BUFFER_SIZE];

	unsigned playerID = 0;
	unsigned sequence = 0;

	unsigned int PORT = 49152;
	std::atomic<bool> disconnect = false;

	std::thread receiveThread;
	
	std::function<void(Vector2&)> moveCallback;
	
public:

	WinsockClient() = default;

	bool ConnectToServer();
	void Close();

	void Recieve();
	void ReadChangeMsg(int offset, ChangeType type);
	void ReadBuffer(int offset, unsigned length, MsgType msg);

	void SetMoveCallback(const std::function<void(Vector2&)>& func) { this->moveCallback = func; }
	
	// Send
	void RequestMove(Vector2 pos, Vector2 dir);

	
	~WinsockClient() { Close(); };
};

