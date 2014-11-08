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
					

					float movementPercentage = entityMemory.m_dynamicDirectionComponents[targetEntity].m_movementPercentage;
					float desiredVelocity = 0;
					if (movementPercentage > 0.0f)
					{
						desiredVelocity = entityMemory.m_staticMovementComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_baseMax * entityMemory.m_dynamicDirectionComponents[targetEntity].m_movementPercentage;
					}
					
					// change to have incremental change
					float desiredVelocityX = desiredVelocity * entityMemory.m_dynamicDirectionComponents[targetEntity].m_direction.x;
					float desiredVelocityY = desiredVelocity * entityMemory.m_dynamicDirectionComponents[targetEntity].m_direction.y;

					// do the math based on massed and preferred velocity of the body
					b2Vec2 vel = entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetLinearVelocity();
					float velChangeX = desiredVelocityX - vel.x;
					float impulseX = entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetMass() * velChangeX; //disregard time factor
					float velChangeY = desiredVelocityY - vel.y;
					float impulseY = entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetMass() * velChangeY; //disregard time factor

					entityMemory.m_dynamicPhysicsComponents[targetEntity].body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetWorldCenter(), true);
				}

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{
					b2Vec2 location = entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetPosition();
					entityMemory.m_dynamicRenderComponents[targetEntity].m_dstRect.x = Meter2Pixel(location.x) - entityMemory.m_staticRenderComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_textureWidth;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_dstRect.y = Meter2Pixel(location.y) - entityMemory.m_staticRenderComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_textureHeight;

					b2Vec2 orientation = entityMemory.m_dynamicTargetComponents[targetEntity].m_orientation;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_angle = (atan2(orientation.y, orientation.x)) * (180.0f / static_cast<float>(M_PI)) - 90.0f;
				}

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes