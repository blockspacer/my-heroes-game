#pragma once
#include "ViewData.h"
#include "SDLEventListener.h"

// Interface for a generic view that can be held by the
// view manager, implements SDLEventListener interface for listening
// for events from models
class View : public SDLEventListener
{
public:

	// creates the view
	// effects: sets active_ = false and view_ID to the VIRTUAL id in view data
	View(void) : active_(false), view_ID_(VIEW_DATA::ID_VIEW_VIRTUAL) {}
	~View(void) {}

	// This function is for intializing any data the view needs to 
	// draw itself later
	// OVERRRIDE
	virtual void init(SDL_Window* window, SDL_Renderer* renderer) = 0;

	// method to call when the view should be drawn
	// OVERRRIDE
	virtual void draw(SDL_Renderer* renderer) = 0;

	// returns the id 
	int64_t getID() { return view_ID_; }

	// returns whether this view is currently active
	bool isActive() { return active_; }

	// method to activate the view
	// OVERRRIDE
	virtual void activate() { active_ = true; }

	// method to deactivate the view
	// OVERRRIDE
	virtual void deactivate() { active_ = false; }

protected:
	// ID of view
	int64_t view_ID_;

	// state of view active means it is ready to draw
	bool active_;
};

