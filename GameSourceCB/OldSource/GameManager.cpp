#include "stdafx.h"
#include "GameManager.h"
#include "ViewLevel.h"

GameManager::GameManager()
{
	continue_ = true;

	view_manager_ = new ViewManager();
	assert(view_manager_ != NULL);

}

GameManager::~GameManager()
{
	delete view_manager_;
}

void GameManager::gameStart()
{
	//------------------------- TEMP-----------------------
	// create the level view here for simulation
	view_level_ = new ViewLevel();
	view_manager_->addView(view_level_);
	view_manager_->updateView(VIEW_DATA::ID_VIEW_LEVEL);
	view_manager_->showView();
	//------------------------- TEMP-----------------------

	// create the level
	CameraPtr cameraPtr = CameraPtr(new Camera);
	cameraPtr->init(view_manager_->getWindow());
	level_manager_ = new LevelManager(cameraPtr);
	level_manager_->loadLevel(view_manager_->getRenderer());	
}

void GameManager::gameUpdate() {
	// update the game state
	level_manager_->updateLevel();

	// draw
	view_manager_->drawView();
}

bool GameManager::gameContinue() {
	return continue_;
}

// handles events for state changes
void GameManager::eventHandler(SDL_Event* e) {

}

// state changes should handle delegate registration
void GameManager::registerDelegates() {}
void GameManager::unregisterDelegates() {}

void GameManager::cleanUpState(GameState state) {
	// TODO
}

void GameManager::changeState(GameState state) {
	// TODO
}