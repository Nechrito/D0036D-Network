#include "Listener.h"
#include "Input.h"
#include <thread>

int main()
{
	Listener listener;
	Input input;
	
	std::thread threadListener(&Listener::Update, listener);
	std::thread threadInput(&Input::Update, input);
	
	if (threadListener.joinable())
		threadListener.join();

	if (threadInput.joinable())
		threadInput.join();
}
