#pragma once

#define MAXNAMELEN 32

/// Enums & constants
enum class ObjectDesc
{
	Human,
	NonHuman,
	Vehicle,
	StaticObject
};

enum class ObjectForm
{
	Cube,
	Sphere,
	Pyramid,
	Cone
};

struct Coordinate
{
	int x;
	int y;
};

enum class MsgType
{
	Join, // Client joining game at server
	Leave, // Client leaving game
	Change, // Information to clients
	Event, // Information from clients to server
	TextMessage // Send text messages to one or all
};

// Included first in all messages
struct MsgHead
{
	unsigned int length; // Total length for whole message
	unsigned int seq_no; // Sequence number
	unsigned int id; // Client ID or 0;
	MsgType type; // Type of message
};

/// Client -> Server
struct JoinMsg
{
	MsgHead head;
	ObjectDesc desc;
	ObjectForm form;
	char name[MAXNAMELEN]; // nullterminated!, or empty
};
struct LeaveMsg
{
	MsgHead head;
};
enum class EventType
{
	Move
};
// Included first in all Event messages
struct EventMsg
{
	MsgHead head;
	EventType type;
};
#pragma pack(1)
struct MoveEvent
{
	EventMsg event;
	Coordinate pos; //New object position
	Coordinate dir; //New object direction
};
#pragma pack(0)

/// Server -> Client 
enum class ChangeType
{
	NewPlayer,
	PlayerLeave,
	NewPlayerPosition
};
// Included first in all Change messages
struct ChangeMsg
{
	MsgHead head;
	ChangeType type;
};
struct NewPlayerMsg
{
	ChangeMsg msg; //Change message header with new client id
	ObjectDesc desc;
	ObjectForm form;
	char name[MAXNAMELEN]; // nullterminated!, or empty
};
struct PlayerLeaveMsg
{
	ChangeMsg msg; //Change message header with new client id
};
struct NewPlayerPositionMsg
{
	ChangeMsg msg; //Change message header
	Coordinate pos; //New object position
	Coordinate dir; //New object direction
};

/// Messages of type "TextMessage"
struct TextMessageMsg // Optional at client side!!!
{
	MsgHead head;
	char text[1]; // NULL-terminerad array av chars.
};