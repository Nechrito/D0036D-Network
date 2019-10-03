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
		if (action == 0)
			return;
		
		switch (button)
		{
			case 1: this->window->Close(); break;
			
			case 17:
				this->player.Position.Y += playerSpeed;
				break;
			case 30:
				this->player.Position.X -= playerSpeed;
				break;
			case 31:
				this->player.Position.Y -= playerSpeed;
				break;
			case 32:
				this->player.Position.X += playerSpeed;
				break;
		}
	});

	return this->window->Open();
}

void Application::Run()
{
	quadCount = 20;
	quadSize = 2.0f / quadCount;
	ConfigureQuads();
	
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

		if (!isRefreshing)
		{
			glBegin(GL_QUADS);
			
			for (const Layout& layout : tiles)
			{
				Color color = layout.QuadColor;
				Vector2D pos = layout.Position;
				
				glColor3f(color.R, color.G, color.B);

				glVertex2f(pos.X, pos.Y);
				glVertex2f(pos.X + quadSize, pos.Y);
				glVertex2f(pos.X + quadSize, pos.Y + quadSize);
				glVertex2f(pos.X, pos.Y + quadSize);
			}

			Color playerColor = player.QuadColor;
			Vector2D playerPosition = player.Position;
			float playerSize = quadSize;

			glColor3f(playerColor.R, playerColor.G, playerColor.B);

			glVertex2f(playerPosition.X, playerPosition.Y);
			glVertex2f(playerPosition.X + playerSize, playerPosition.Y);
			glVertex2f(playerPosition.X + playerSize, playerPosition.Y + playerSize);
			glVertex2f(playerPosition.X, playerPosition.Y + playerSize);

			glEnd();
		}
		
		// swap buffers 
		this->window->SwapBuffers();
	}
}

void Application::Close() { }
void Application::Exit() { }

void Application::ReceiveCommand(const std::string& command)
{
	if (command == "NewPlayerPosition")
	{
		// fetch the position 
		return;
	}
	
	double quads = std::stod(command);
	this->quadCount = (int)quads;
	this->quadSize = 2.0f / quadCount;
	this->isRefreshing = true;
}

void Application::ConfigureQuads()
{
	tiles.clear();
	
	for (int x = 0; x < quadCount; x++)
	{
		for (int y = 0; y < quadCount; y++)
		{
			Vector2D position(-1.0f + x * quadSize, -1.0f + y * quadSize);
			Color randomColor = GenerateColor();
			
			tiles.emplace_back(randomColor, position);
		}
	}

	std::cout << "Tiles: " << tiles.size() << std::endl;

	this->isRefreshing = false;
}

Color Application::GenerateColor()
{
	Color temp;
	for (int i = 0; i < 3; i++)
	{
		//temp[i] = (float)rand() / RAND_MAX;
		temp[i] = col;
		col -= 0.0005f;
	}
	return temp;
}
