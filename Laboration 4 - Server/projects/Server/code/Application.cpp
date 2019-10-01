#include "config.h"
#include "Application.h"
#include <iostream>

bool Application::Open()
{
	// start app
	App::Open();

	// window override config
	this->window = new Display::Window;
	this->window->SetSize(width, height);
	this->window->SetTitle("Server");

	return this->window->Open();
}

void Application::Run()
{
	while (this->window->IsOpen())
	{
		// Clear screen
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		this->window->Update();

		// Time since glfw was initialized 
		const auto currentTime = float(glfwGetTime());

		// Time between current and previous frame, useful to limit movement as compute speed differs with unlocked frame-rate
		deltaTime = float(currentTime - lastFrame);
		lastFrame = currentTime;


		
		
		// swap buffers 
		this->window->SwapBuffers();
	}
}

void Application::Close() { }
void Application::Exit() { }