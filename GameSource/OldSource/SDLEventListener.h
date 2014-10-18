#pragma once
#include "stdafx.h"

// inherit this class to be able to catch events
class SDLEventListener
{
public:
	virtual ~SDLEventListener(void) {};

	// queues up which events have happend
	virtual void eventHandler(SDL_Event* e) = 0;

	virtual void registerDelegates() = 0;

	virtual void unregisterDelegates() = 0;
};
