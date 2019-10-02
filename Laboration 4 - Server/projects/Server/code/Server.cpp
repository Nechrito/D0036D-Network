#include "Listener.h"
#include <thread>

int main()
{
	Listener listener;
	std::thread threadObj(&Listener::Update, listener);

	if (threadObj.joinable())
		threadObj.join();

	
}
