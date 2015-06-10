#pragma once
#include "ViewManager.h"
#include "SDLEventListener.h"
#include "SDLEventManager.h"
#include "LevelManager.h"

typedef uint64_t GameState;

// This class deals with menu changes and every thing with setting
// and deals with the actual game simulation
class GameManager : public SDLEventListener
{
public:
	GameManager();
	~GameManager();

	void gameStart();
	bool gameContinue();
	void gameUpdate();

private:
	// internal functions
	virtual void eventHandler(SDL_Event* e);
	virtual void registerDelegates();
	virtual void unregisterDelegates();

	void cleanUpState(GameState state);
	void changeState(GameState state);

	SDLEventListenerDelegate user_event_delegate_;
	SDLEventListenerDelegate keydown_event_delegate_; // mouse?

	View* view_level_; // temp
	ViewManager* view_manager_;

	LevelManager* level_manager_;
	
	bool continue_;
};

