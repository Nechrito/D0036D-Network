#pragma once
#include "Color.h"
#include "Vector2D.h"

class Layout
{
public:
	Color QuadColor;
	Vector2D Position;

	Layout() = default;

	Layout(Color color, const Vector2D& position)
	{
		this->QuadColor = color;
		this->Position = position;
	}
};
