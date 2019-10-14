#pragma once
#include "CProtocol.h"

class Serializer
{
public:
	Serializer() = default;
	~Serializer() = default;

	static unsigned char* serializeInt(unsigned char* buffer, int value);
	static unsigned char* serializeChar(unsigned char* buffer, char value);
	static unsigned char* serialize(unsigned char* buffer, MoveEvent *value);
};
