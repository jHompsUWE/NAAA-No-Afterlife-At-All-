#pragma once

enum class EventType
{
	MouseMoved,
	MouseClicked,
	MouseScrolled,
	KeyPressed,
	KeyReleased,
	KeyHeld,
};

class Event
{
public:
	struct GameEvent
	{
		char* str = NULL;
	};

	struct KeyEvent
	{
		char* str = NULL;
	};

	struct MouseEvent
	{
		char* str = NULL;
	};

	union EventPayload
	{
		GameEvent game_event;
		KeyEvent key_event;
		MouseEvent mouse_event;
	};

	////////////////////////////////////////////////////////////
	/// \brief Holds the event-specific data.
	////////////////////////////////////////////////////////////
	EventPayload payload;

	////////////////////////////////////////////////////////////
	/// \brief Helps users avoid undefined behaviour. Check the type and only read from the corresponding payload member. 
	////////////////////////////////////////////////////////////
	EventType type;

	////////////////////////////////////////////////////////////
	/// \brief The time between tick in which the event is trigger and its execution in seconds, defaulted to 0 for an immediate event. 
	////////////////////////////////////////////////////////////
	float delay = 0;
};
