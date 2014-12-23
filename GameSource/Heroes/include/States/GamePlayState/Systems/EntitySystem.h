#pragma once

#include <Engine/SDLUtilityTool.h>
#include <Engine/InputHandler.h>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			class EntityMemory;

			// parameters will eventually include the entity group
			typedef void(*EntitySystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory);
			typedef void(*EntityDecisionSystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller, Engine::InputHandler& inputHandler);
			typedef void(*EntityRenderFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_Window* window);

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
