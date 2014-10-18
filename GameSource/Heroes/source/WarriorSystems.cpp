#include <Box2D/Box2D.h>

#include "States/GamePlayState/b2Conversion.h"
#include "States/GamePlayState/Systems/WarriorSystems.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			namespace WarriorSystems
			{
				void WarriorStatusSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorHealthSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorTargetSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorActionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorMovementSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{
					

					b2Vec2 direction = entityMemory.m_directionComponents[targetEntity].m_direction;
					float desiredVelocity = 0;
					if (direction.x != 0.0f || direction.y != 0.0f)
					{
						SDL_assert(direction.Length() > 0.5f);
						desiredVelocity = entityMemory.m_movementComponents[targetEntity].m_baseMax;
					}
					
					// change to have incremental change
					float desiredVelocityX = desiredVelocity * entityMemory.m_directionComponents[targetEntity].m_direction.x;
					float desiredVelocityY = desiredVelocity * entityMemory.m_directionComponents[targetEntity].m_direction.y;

					// do the math based on massed and preferred velocity of the body
					b2Vec2 vel = entityMemory.m_physicsComponents[targetEntity].body->GetLinearVelocity();
					float velChangeX = desiredVelocityX - vel.x;
					float impulseX = entityMemory.m_physicsComponents[targetEntity].body->GetMass() * velChangeX; //disregard time factor
					float velChangeY = desiredVelocityY - vel.y;
					float impulseY = entityMemory.m_physicsComponents[targetEntity].body->GetMass() * velChangeY; //disregard time factor

					entityMemory.m_physicsComponents[targetEntity].body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), entityMemory.m_physicsComponents[targetEntity].body->GetWorldCenter(), true);
				}

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{
					b2Vec2 location = entityMemory.m_physicsComponents[targetEntity].body->GetPosition();
					entityMemory.m_renderComponents[targetEntity].m_dstRect.x = Meter2Pixel(location.x) - 32;
					entityMemory.m_renderComponents[targetEntity].m_dstRect.y = Meter2Pixel(location.y) - 32;

					b2Vec2 orientation = entityMemory.m_targetComponents[targetEntity].m_orientation;
					entityMemory.m_renderComponents[targetEntity].m_angle = (atan2(orientation.y, orientation.x)) * (180.0 / M_PI) - 90;
				}

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes