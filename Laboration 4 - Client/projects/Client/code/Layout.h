#pragma once
#include "Color.h"
#include "Vector2.h"

class Layout
{
public:
	Color QuadColor;
	Vector2 Position;

	Layout() = default;

	Layout(Color color, const Vector2& position)
	{
		this->QuadColor = color;
		this->Position = position;
	}
};
