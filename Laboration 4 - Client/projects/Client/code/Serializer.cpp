#include "Serializer.h"

/* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
unsigned char* Serializer::serializeInt(unsigned char* buffer, int value)
{
	buffer[0] = value >> 24;
	buffer[1] = value >> 16;
	buffer[2] = value >> 8;
	buffer[3] = value;
	return buffer + 4;
}

unsigned char* Serializer::serializeChar(unsigned char* buffer, char value)
{
	buffer[0] = value;
	return buffer + 1;
}

unsigned char* Serializer::serialize(unsigned char* buffer, MoveEvent* value)
{
	/*buffer = serializeInt(buffer, value->);
	buffer = serializeChar(buffer, value->b);*/
	return buffer;
}