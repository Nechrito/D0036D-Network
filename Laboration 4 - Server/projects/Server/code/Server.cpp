#include "WinsockServer.h"
#include "Input.h"
#include <thread>

int main()
{
	WinsockServer server;
	Input input;
	
	std::thread threadListener(&WinsockServer::Update, server);
	std::thread threadInput(&Input::Update, input);
	
	if (threadListener.joinable())
		threadListener.join();

	if (threadInput.joinable())
		threadInput.join();
}
