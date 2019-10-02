#pragma once
class Vector2D
{
public:
	float X;
	float Y;

	Vector2D()
	{
		X = -1;
		Y = -1;
	}

	Vector2D(float x, float y) : X(x), Y(y)
	{
		
	}

	~Vector2D()
	{
		
	};
};