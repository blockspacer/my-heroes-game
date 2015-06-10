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

				void MainEntityAISystem(int targetEntity, GamePlay::EntityMemory& entityMemory, Engine::InputHandler& inputHandler);

			} // namespace PlayerSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes