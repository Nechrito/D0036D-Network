#pragma once
#include <iostream>

class Color
{
public:
	float& operator[](int i);
	
	float R;
	float G;
	float B;

	Color() = default;
	
	Color(float r, float g, float b)
	{
		R = r;
		G = g;
		B = b;
	}
};

inline float& Color::operator[](int i)
{
	switch (i)
	{
		case 0: return R;
		case 1: return G;
		case 2: return B;
	}
	assert("Invalid Index");
	return R;
}
