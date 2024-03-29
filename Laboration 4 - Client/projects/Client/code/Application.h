#pragma once

#include "core/app.h"
#include "render/window.h"
#include <vector>
#include "Layout.h"
#include "WinsockClient.h"

class Application final : public Core::App
{
public:
	Application();

	bool Open()  override;
	void Run()   override;
	void Close() override {}
	void Exit()  override {}

	void ReceiveCommand(const std::string& command);
	void RefreshTiles();

	void SetMovePos(Vector2& pos) { this->player.Position = pos; }
	
	~Application() = default;
	
private:

	Display::Window* window;
	WinsockClient winsockClient;
	
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
