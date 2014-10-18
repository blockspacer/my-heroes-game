#include "stdafx.h"
#include "SDLEventManager.h"

SDLEventManager::SDLEventManager(bool multi, Event_Filter eventFilter) {

	// intialize the class parameters
	multi_ = multi;
	event_listener_map_ = new EventListenerMap();
	events_ = new SDL_Event[EVENT_QUEUE_SIZE];

	// fuction for user to define for filtering events 
	if (eventFilter != NULL)
		SDL_SetEventFilter((SDL_EventFilter)eventFilter, NULL);
}


SDLEventManager::~SDLEventManager(void) {}

int SDLEventManager::sendEvent(SDL_Event* e)
{
	// simply push what ever is passed (assume non null)
	return SDL_PushEvent(e);
}

bool SDLEventManager::addListener(int64_t eventType, SDLEventListenerDelegate* eventDelegate)
{
	// queue it to be added
	to_be_added_.push_back(std::pair<EventType, SDLEventListenerDelegate*>(eventType, eventDelegate));
	return true;
}

bool SDLEventManager::removeListener(int64_t eventType, SDLEventListenerDelegate* eventDelegate)
{
	// queue it to be removed
	to_be_removed_.push_back(std::pair<EventType, SDLEventListenerDelegate*>(eventType, eventDelegate));
	return true;
}

void SDLEventManager::processEvents()
{
	SDL_PumpEvents();

	// grab the events and put them into the events queue
	int ret = SDL_PeepEvents(events_, EVENT_QUEUE_SIZE, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);

	// for each event returned try and find delegates for them
	for (int i = 0; i < ret; i++)
	{
		auto list = event_listener_map_->find(events_[i].type);
		if (list != event_listener_map_->end())
		{
			EventListenerSet* eventListenerSet = event_listener_map_->at(events_[i].type);

			for (auto d = eventListenerSet->begin(); d != eventListenerSet->end(); d++)
			{
				// finally call the delegate listener
				SDLEventListenerDelegate listener = **d; // double dereference
				listener(events_ + i);
			}
		}
	}
}

void SDLEventManager::updateEventManager() {

	// ADD FROM THE ADD LIST
	int num_elements = to_be_added_.size();
	for (int i = 0; i < num_elements; i++) {

		std::pair<EventType, SDLEventListenerDelegate*> del = to_be_added_.back();
		to_be_added_.pop_back();

		EventListenerSet* eventListenerSet = NULL;
		auto list = event_listener_map_->find(del.first); // attempt to find the list

		// if the list for that event type has not been added add it
		if (list == event_listener_map_->end())
		{
			eventListenerSet = new EventListenerSet();
			event_listener_map_->insert(std::pair<int64_t, EventListenerSet*>(del.first, eventListenerSet));
		}
		else {

			eventListenerSet = event_listener_map_->at(del.first);
		}

		// add it and retun
		eventListenerSet->insert(del.second);
	}

	// REMOVE FROM THE REMOVE LIST
	num_elements = to_be_removed_.size();
	for (int i = 0; i < num_elements; i++) {

		// access and then remove
		std::pair<EventType, SDLEventListenerDelegate*> del = to_be_removed_.back();
		to_be_removed_.pop_back();

		auto listIter = event_listener_map_->find(del.first);

		// check that the map has an entry for eventType
		if (listIter != event_listener_map_->end())
		{

			// go through and look for delegate
			EventListenerSet* eventListenerSet = event_listener_map_->at(del.first);
			auto delIter = eventListenerSet->find(del.second);
			if (delIter != eventListenerSet->end()) {
				eventListenerSet->erase(delIter);
			}
		}

	}
}
