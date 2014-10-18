#pragma once

#include "States/GamePlayState/Entities/EntityMemory.h"
#include "States/GamePlayState/Systems/EntitySystem.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			namespace PlayerSystems
			{

				void MainEntityTargetSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

				void MainEntityDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller);

			} // namespace PlayerSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes