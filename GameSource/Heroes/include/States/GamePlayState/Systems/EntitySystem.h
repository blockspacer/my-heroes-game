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
			typedef void(*SystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
