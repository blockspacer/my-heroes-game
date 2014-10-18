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
				void WarriorStatusSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);
				
				void WarriorHealthSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void WarriorTargetSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void WarriorActionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void WarriorDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void WarriorMovementSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes