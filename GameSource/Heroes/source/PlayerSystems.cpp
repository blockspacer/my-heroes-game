#include "Engine/Log.h"

#include "Engine/SDLXbox360Controller.h"
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
					Uint8 buttonA = SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

					if (buttonA)
					{
						// set basic attack 1.5 secs
						entityMemory.m_statusComponents.SetBusyStatus(targetEntity, BusyStatusType::BASIC_ATTACK, entityMemory.m_actionComponents.GetNormalAttackSpeed_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity)) * 100);
					}
				}

				void MainEntityDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{
					g_assert(targetEntity >= 0 && targetEntity < GamePlay::ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
					g_assert(controller != nullptr);

					Sint16 axisLeftX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
					Sint16 axisLeftY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
					
					Sint16 axisRightX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX);
					Sint16 axisRightY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY);

					b2Vec2 movementVector = b2Vec2(axisLeftX, axisLeftY);
					if (abs(movementVector.x) > 5000 || abs(movementVector.y) > 5000)
					{
						entityMemory.m_directionComponents.SetMovementPercentage_D(targetEntity, movementVector.Length() / 32768);
						movementVector.Normalize();
					}
					else
					{
						entityMemory.m_directionComponents.SetMovementPercentage_D(targetEntity, 0.0f);
						movementVector = b2Vec2_zero;
					}
					entityMemory.m_directionComponents.SetDirection_D(targetEntity, movementVector);
					

					b2Vec2 orientationVector = b2Vec2(static_cast<float>(-axisRightX), static_cast<float>(-axisRightY));
					if (abs(orientationVector.x) > Engine::AXIS_EPSILON || abs(orientationVector.y) > Engine::AXIS_EPSILON)
					{
						orientationVector.Normalize();
						entityMemory.m_targetComponents.SetOrientation_D(targetEntity, orientationVector);
					}
					else
					{
						orientationVector = entityMemory.m_targetComponents.GetOrientation_D(targetEntity);
					}

					// set the idle status
					IdleStatusType idleStatus;
					if (entityMemory.m_directionComponents.GetMovementPercentage_D(targetEntity) > 0.7 &&
						abs(acosf((orientationVector.x) * -movementVector.x + (orientationVector.y * -movementVector.y))) < M_PI / 6)
					{
						idleStatus = IdleStatusType::MOVING;
					}
					else
					{
						idleStatus = IdleStatusType::STANDING;
					}
					entityMemory.m_statusComponents.SetIdleStatus_D(targetEntity, idleStatus);
					
				}

			} // namespace PlayerSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes