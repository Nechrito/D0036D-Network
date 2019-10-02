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
	this->window->SetTitle("Client");

	this->window->SetKeyPressFunction([this](int, const int button, const int action, int)
	{
		if (action == 1 && button == 1)
			this->window->Close();
	});

	return this->window->Open();
}

void Application::Run()
{
	while (this->window->IsOpen())
	{
		// Clear screen
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Time since glfw was initialized 
		const auto currentTime = float(glfwGetTime());

		// Time between current and previous frame, useful to limit movement as compute speed differs with unlocked frame-rate
		deltaTime = float(currentTime - lastFrame);
		lastFrame = currentTime;

		this->window->Update();

		
		// swap buffers 
		this->window->SwapBuffers();
	}
}

void Application::Close() { }
void Application::Exit() { }