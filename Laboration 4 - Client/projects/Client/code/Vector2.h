#pragma once
class Vector2
{
public:
	float X;
	float Y;

	Vector2() : X(0), Y(0) { }
	Vector2(float x, float y) : X(x), Y(y) { }
	Vector2(int x, int y) : X(static_cast<float>(x)), Y(static_cast<float>(y)) { }

	~Vector2() = default;
};