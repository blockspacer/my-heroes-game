#pragma once
// precompiled
#include "stdafx.h"

// utilities
#include <FastDelegate.h>
#include <unordered_set>
#include <map>

// my headers
#include "SDLEventListener.h"

// USAGE: use fastdelegate to create the SDLEventListenerDelegate

// predefined queue size
#define EVENT_QUEUE_SIZE 128

// define the fast delegate functions for this use
typedef fastdelegate::FastDelegate1<SDL_Event*, void> SDLEventListenerDelegate;

// custom function for creating SDLEventListenerDelegates
template <class X, class Y, class Param1, class RetType>
static SDLEventListenerDelegate createSDLEventListenerDelegate(Y* x, RetType(X::*func)(Param1 p1)) {
return fastdelegate::FastDelegate1<Param1, void>(x, func);
}

// for future filter function
typedef int(*Event_Filter)(const SDL_Event*);

// define variables for event manager
typedef int64_t EventType;
typedef std::unordered_set<SDLEventListenerDelegate*> EventListenerSet;
typedef std::map<EventType, EventListenerSet*> EventListenerMap;

class SDLEventManager
{
public:

	// This is the method to get the instance of the event manager singleton
	static SDLEventManager* getInstance()
	{
		static SDLEventManager* instance = new SDLEventManager(false, NULL); // Guaranteed to be destroyed.

		// Instantiated on first use.
		return instance;
	}

	// add a listener to the event manager
	// takes a event type and a EventListenerDelegate
	// return true for success and false for failure
	bool addListener(EventType eventType, SDLEventListenerDelegate* del);

	// removes a listener to the event manager
	// takes a event type and a EventListenerDelegate
	// return true for success and false for failure
	bool removeListener(EventType eventType, SDLEventListenerDelegate* del);

	// sends an event via SDL, mainly for consistency with only useing the sdl Manager
	int sendEvent(SDL_Event* e);

	// grab current events and call all registered listeners for any
	// event in the SDL queue
	void processEvents();

	// actaully add/removes the queued delegates
	void updateEventManager();

private:

	// takes a bool if you want multi threaded (not implemented)
	// and a filter function for events (not implemented)
	SDLEventManager(bool multi, Event_Filter eventfilter);
	~SDLEventManager(void);

	// bool for multi threaded running
	bool multi_;

	// map from events to the registered delegates
	EventListenerMap* event_listener_map_;

	SDL_Event* events_;
	std::list<std::pair<EventType, SDLEventListenerDelegate*>> to_be_removed_;
	std::list<std::pair<EventType, SDLEventListenerDelegate*>> to_be_added_;
};

