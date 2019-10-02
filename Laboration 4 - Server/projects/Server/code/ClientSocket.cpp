//#include "ClientSocket.h"
//
//
//ClientSocket::ClientSocket(SOCKET socket)
//{
//	this->socket = socket;
//}
//
//void ClientSocket::CloseConnection()
//{
//	
//}
//
//void ClientSocket::ReceiveData()
//{
//	// receive as long as the connection is upheld 
//	int bufferSize = 512;
//	char* buffer = new char[bufferSize];
//	int result = recv(socket, buffer, bufferSize, 0);
//
//	if (result == 0)
//	{
//		printf("Something went wrong...\n");
//		return;
//	}
//
//	if (result > 0)
//	{
//		printf("Received %d", result);
//		printf(" Bytes!\n");
//
//	}
//	else
//	{
//		printf("Failed to receive data, shutting down...%d\n", WSAGetLastError());
//	}
//}
