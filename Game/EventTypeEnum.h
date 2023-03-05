#pragma once

enum class EventType
{
	None = 0,
	KeyPressed, KeyReleased, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};
// Instead of casting, give events IDs.
