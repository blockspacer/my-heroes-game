#pragma once
#include "stdafx.h"

class SDLEventSender
{
public:
	virtual	~SDLEventSender() {};

protected:
	SDL_Event event_messager_;
};

