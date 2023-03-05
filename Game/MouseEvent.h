#pragma once

#include <string>
#include "Event.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y) : mouse_x(x), mouse_y(y) {}
	~MouseMovedEvent() = default;

	inline float getX() const { return mouse_x; }
	inline float getY() const{ return mouse_y; }

	std::string toString() const override
	{
		std::string string;
		string = "MouseMovedEvent: " + std::to_string(mouse_x) + ", " + std::to_string(mouse_y);
		return string;
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY((int)EventCategory::EVENT_CATEGORY_MOUSE | (int)EventCategory::EVENT_CATEGORY_INPUT)

private:
	float mouse_x = 0;
	float mouse_y = 0;
};


class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float _scroll_Offset) : scroll_offset(_scroll_Offset) {}
	~MouseScrolledEvent() = default;

	inline float getXOffset() { return scroll_offset; }

	std::string toString() const override
	{
		std::string string;
		string = "MouseScrollEvent: " + std::to_string(scroll_offset);
		return string;
	}

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY((int)EventCategory::EVENT_CATEGORY_MOUSE | (int)EventCategory::EVENT_CATEGORY_INPUT)

private:
	float scroll_offset = 0;
};


class MouseButtonEvent : public Event
{
public:
	inline int getMouseButton() const { return button; }

	EVENT_CLASS_CATEGORY((int)EventCategory::EVENT_CATEGORY_MOUSE | (int)EventCategory::EVENT_CATEGORY_INPUT)

protected:
	MouseButtonEvent(int _button) : button(_button) {}
	~MouseButtonEvent() = default;

	int button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int _button) : MouseButtonEvent(_button) {}
	~MouseButtonPressedEvent() = default;

	std::string toString() const override
	{
		std::string string;
		string = "MouseButtonPressedEvent: " + std::to_string(button);
		return string;
	}

	EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int _button) : MouseButtonEvent(_button) {}
	~MouseButtonReleasedEvent() = default;

	std::string toString() const override
	{
		std::string string;
		string = "MouseButtonReleased: " + std::to_string(button);
		return string;
	}

	EVENT_CLASS_TYPE(MouseButtonReleased);
};
