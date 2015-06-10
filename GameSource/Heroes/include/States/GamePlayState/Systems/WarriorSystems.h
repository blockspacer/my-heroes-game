#pragma once

#include "States/GamePlayState/Entities/EntityMemory.h"
#include "States/GamePlayState/Systems/EntitySystem.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			namespace WarriorSystems
			{
				void WarriorStatusSystem(int targetEntity, GamePlay::EntityMemory& entityMemory);
				
				void WarriorHealthSystem(int targetEntity, GamePlay::EntityMemory& entityMemory);

				void WarriorAISystem(int targetEntity, GamePlay::EntityMemory& entityMemory, Engine::InputHandler& inputHandler);

				void WarriorActionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory);

				void WarriorMovementSystem(int targetEntity, GamePlay::EntityMemory& entityMemory);

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_Window* window);

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes