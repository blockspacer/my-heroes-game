#pragma once

#include <SDL.h>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			class EntityMemory;

			// parameters will eventually include the entity group
			typedef void(*EntitySystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory);
			typedef void(*EntityDecisionSystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);
			typedef void(*EntityRenderFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_Window* window);

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
