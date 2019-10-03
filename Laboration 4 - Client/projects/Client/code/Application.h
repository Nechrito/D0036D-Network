#pragma once

#include "core/app.h"
#include "render/window.h"
#include <vector>
#include "Layout.h"

class Application : public Core::App
{
public:
	Application() : window(nullptr)
	{
		this->player = Layout(Color(1, 1, 1), Vector2D(0.0f - 1 / quadSize, 0.0f - 1 / quadSize));
	}

	bool Open()  override;
	void Run()   override;
	void Close() override;
	void Exit()  override;

	void ReceiveCommand(const std::string& command);
	void ConfigureQuads();

	~Application() = default;
	
private:

	Display::Window* window;
	
	float width = 1024;
	float height = 720;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// game-related
	std::vector<Layout> tiles;
	int quadCount;
	float quadSize;
	bool isRefreshing;
	
	Layout player;
	float playerSpeed = 0.05f;
	float col = 0.65;
	
	Color GenerateColor();
};
