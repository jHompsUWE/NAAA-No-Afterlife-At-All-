#pragma once

class Manager
{
public:
	Manager() {};
	~Manager() {};

	virtual void awake() {};
	virtual void update() = 0;
};


