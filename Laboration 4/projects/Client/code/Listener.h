#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

constexpr auto PORT = "49153";

class Listener
{
private:
	WSADATA wsadata;
	
	struct addrinfo* addressInfo = nullptr, *ptr = nullptr, socketAddress;
	
	SOCKET ServerSocket = INVALID_SOCKET; 
	SOCKET ClientSocket = INVALID_SOCKET; // Manages connections from external clients

public:

	Listener();

	void Update();
	void AcceptPacket();

	void Close();
	
	~Listener() = default;
};