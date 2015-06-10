#include "stdafx.h"
#include "SDLEventManager.h"
#include "GameManager.h"
#include "ViewManager.h"
#include "ViewLevel.h"

static const Uint32 FRAMERATE = 33;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLEventManager* eventManager = SDLEventManager::getInstance();
	assert(eventManager != NULL);

	GameManager* gameManager = new GameManager();
	assert(gameManager != NULL);

	// get time and show view
	Uint32 time = SDL_GetTicks();
	gameManager->gameStart();

	while (gameManager->gameContinue()) {
		if (time + FRAMERATE < SDL_GetTicks()) {
			// process events
			eventManager->updateEventManager();
			eventManager->processEvents();

			// update logic
			gameManager->gameUpdate();

			time = SDL_GetTicks();
		}
	}
	return 0;
}

