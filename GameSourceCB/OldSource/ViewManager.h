#pragma once

// precompiled
#include "stdafx.h"

// utilities
#include "SDL_ttf.h"
#include <map>

// my classes
#include "SDLEventListener.h"
#include "View.h"

// This class is the manager for all the Views in the game
// lets the client add and remove views along with the EventListenerDelegates
// if the view commnicates to other game objects, this class takes ownership
// of all views added (aka it deletes them)
class ViewManager
{
public:

	// Constuctor for a view mananger
	// creates SDL Window to WINDOW_WDITH and WINDOW_HEIGHT and hidden and borderless
	// creates SDL renderer from window
	// Initilzes the TTF fonts for all views
	// attaches EventManager so views can add thier delegates
	// creates the default view (loading screen), sets current view to this default view
	// creates the static view (border)
	ViewManager() {

		window_ = SDL_CreateWindow("Heroes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP);
		assert(window_ != NULL);

		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
		assert(renderer_ != NULL);

		// intiate the font and writing system
		TTF_Init();
	}

	~ViewManager(void) {
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);

		// Deletes each view in map
		for (auto v : view_map_) {
			View* view = v.second;
			delete view;
		}
	}

	// Adds a view along with its delegates to the view manager
	// Paramter is a std::pair where first is a View*
	// and second is a vector of std::pair<event type, eventListenerDelegate>
	void addView(View* view) {

		// put the view into the map
		view_map_[view->getID()] = view;

		// intiate the view so that it can draw
		view->init(window_, renderer_);
	}

	// hides the screen
	void hideView() { SDL_HideWindow(window_); }

	// shows the screen
	void showView() { SDL_ShowWindow(window_); }

	// draw the current view
	// if no views have been added draws default view
	// always draws the static view
	void drawView() {
		//assert(current_view_ != NULL);
		//assert(current_view_->isActive());

		SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer_);

		if (current_view_ != NULL && current_view_->isActive()) {
			current_view_->draw(renderer_);
		}

		SDL_RenderPresent(renderer_);
	}

	void updateView(int64_t view_ID) {
		// clean up current view
		if (current_view_ != NULL) {
			unregisterView();
		}

		// register the new view id
		registerView(view_ID);
	}

	SDL_Renderer* getRenderer() {
		return renderer_;
	}
	SDL_Window* getWindow() {
		return window_;
	}

private:

	/*
	* calls deactivate on current view and then removes all the
	* EventListenerDelegates for that view from the event manager
	*/
	void unregisterView() {
		current_view_->unregisterDelegates();
		current_view_->deactivate();
	}

	/*
	* This takes a view ID and activates it and then adds
	* each EventListenerDelegate to the event manager
	*/
	void registerView(int64_t view_ID) {
		// set the current view to this one
		View* view = view_map_[view_ID];
		current_view_ = view;

		// set it and activate it
		current_view_->registerDelegates();
		current_view_->activate();
	}

	// SDL window and renderer
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	// current view to draw
	View* current_view_;

	// loading screen
	View* default_view_;

	// this is a variable to hold the mapping from view ID to a view and the delegate listeners for the view
	std::map <int64_t, View*> view_map_;
};

