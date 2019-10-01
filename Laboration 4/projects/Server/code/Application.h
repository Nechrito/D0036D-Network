#pragma once

#include "core/app.h"
#include "render/window.h"

class Application : public Core::App
{
public:
	Application() : window(nullptr) { }

	bool Open()  override;
	void Run()   override;
	void Close() override;
	void Exit()  override;

	~Application() = default;
	
private:

	Display::Window* window;
	
	float width = 1280;
	float height = 720;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};
