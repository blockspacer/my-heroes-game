#include "Engine/Log.h"

#include "Engine/SDLXbox360Controller.h"
#include "States/GamePlayState/Systems/PlayerSystems.h"

#include <iostream>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			namespace PlayerSystems
			{

				void MainEntityAISystem(int targetEntity, GamePlay::EntityMemory& entityMemory, Engine::InputHandler& inputHandler)
				{
					if (inputHandler.GetButton(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == ButtonState::BUTTON_PRESSED)
					{
						// set basic attack 1.5 secs
						entityMemory.m_AIComponents.SwitchTargets_D(targetEntity, entityMemory);

					}

					ButtonState buttonAState = inputHandler.GetButton(SDL_CONTROLLER_BUTTON_A);

					if (buttonAState == ButtonState::BUTTON_PRESSED)
					{
						// set basic attack 1.5 secs
						entityMemory.m_statusComponents.SetBusyStatus_D(targetEntity, BusyStatusType::BASIC_ATTACK, entityMemory.m_actionComponents.GetNormalAttackSpeed_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity)) * 100);
					}

					// direction stuff
					Sint16 axisLeftX = inputHandler.Left_Stick_X();
					Sint16 axisLeftY = inputHandler.Left_Stick_Y();

					Sint16 axisRightX = inputHandler.Right_Stick_X();
					Sint16 axisRightY = inputHandler.Right_Stick_Y();

					b2Vec2 movementVector = b2Vec2(axisLeftX, axisLeftY);
					if (abs(movementVector.x) > 5000 || abs(movementVector.y) > 5000)
					{
						entityMemory.m_AIComponents.SetMovementPercentage_D(targetEntity, movementVector.Length() / 32768);
						movementVector.Normalize();
					}
					else
					{
						entityMemory.m_AIComponents.SetMovementPercentage_D(targetEntity, 0.0f);
						movementVector = b2Vec2_zero;
					}
					entityMemory.m_AIComponents.SetDirection_D(targetEntity, movementVector);


					b2Vec2 orientationVector = b2Vec2(static_cast<float>(-axisRightX), static_cast<float>(-axisRightY));
					if (abs(orientationVector.x) > Engine::AXIS_EPSILON || abs(orientationVector.y) > Engine::AXIS_EPSILON)
					{
						orientationVector.Normalize();
						entityMemory.m_AIComponents.SetOrientation_D(targetEntity, orientationVector);
					}
					else
					{
						orientationVector = entityMemory.m_AIComponents.GetOrientation_D(targetEntity);
					}

					// set the idle status
					IdleStatusType idleStatus;
					if (entityMemory.m_AIComponents.GetMovementPercentage_D(targetEntity) > 0.7 &&
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