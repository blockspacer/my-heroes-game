#include <SDL_assert.h>

#include "Engine\SDLXbox360Controller.h"
#include "States/GamePlayState/Systems/PlayerSystems.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			namespace PlayerSystems
			{

				void MainEntityTargetSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{

				}

				void MainEntityDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{
					SDL_assert(targetEntity >= 0 && targetEntity < GamePlay::EntityMemorySize::SIZE);
					SDL_assert(controller != nullptr);

					Sint16 axisLeftX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
					Sint16 axisLeftY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
					
					Sint16 axisRightX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX);
					Sint16 axisRightY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY);

					b2Vec2 movementVector = b2Vec2(axisLeftX, axisLeftY);
					if (abs(movementVector.x) > Engine::AXIS_EPSILON || abs(movementVector.y) > Engine::AXIS_EPSILON)
					{
						movementVector.Normalize();
					}
					else
					{
						movementVector = b2Vec2_zero;
					}
					entityMemory.m_directionComponents[targetEntity].m_direction = movementVector;

					// apply forces

					b2Vec2 orientationVector = b2Vec2(- axisRightX, - axisRightY);
					if (abs(orientationVector.x) > Engine::AXIS_EPSILON || abs(orientationVector.y) > Engine::AXIS_EPSILON)
					{
						orientationVector.Normalize();
						entityMemory.m_targetComponents[targetEntity].m_orientation = orientationVector;
					}
					
					
				}

			} // namespace PlayerSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes