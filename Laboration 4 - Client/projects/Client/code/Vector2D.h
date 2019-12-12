#pragma once
class Vector2D
{
public:
	float X;
	float Y;

	Vector2D() : X(0), Y(0) { }
	Vector2D(float x, float y) : X(x), Y(y) { }
	Vector2D(int x, int y) : X(static_cast<float>(x)), Y(static_cast<float>(y)) { }

	~Vector2D() = default;
};