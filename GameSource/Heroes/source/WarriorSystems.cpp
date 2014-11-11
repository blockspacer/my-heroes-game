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
				void WarriorStatusSystem(int targetEntity, GamePlay::EntityMemory& entityMemory)
				{}

				void WarriorHealthSystem(int targetEntity, GamePlay::EntityMemory& entityMemory)
				{}

				void WarriorTargetSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorActionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory)
				{}

				void WarriorDirectionSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_GameController* controller)
				{}

				void WarriorMovementSystem(int targetEntity, GamePlay::EntityMemory& entityMemory)
				{
					

					float movementPercentage = entityMemory.m_dynamicDirectionComponents[targetEntity].m_movementPercentage;
					float desiredVelocity = 0;
					if (movementPercentage > 0.0f)
					{
						desiredVelocity = entityMemory.m_staticMovementComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_speed * entityMemory.m_dynamicDirectionComponents[targetEntity].m_movementPercentage;
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

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_Window* window)
				{
					SDL_DisplayMode displayMode;
					SDL_GetWindowDisplayMode(window, &displayMode);

					EntityStaticIDType staticID = entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID;
					b2Vec2 mainEntitylocation = entityMemory.m_dynamicPhysicsComponents[entityMemory.GetMainEntityDynamicID()].body->GetPosition();
					b2Vec2 location = entityMemory.m_dynamicPhysicsComponents[targetEntity].body->GetPosition();
					SDL_Rect dst;

					// determine pixel location from simulation world
					dst.x = Meter2Pixel(location.x) - entityMemory.m_staticRenderComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_textureWidth;
					dst.y = Meter2Pixel(location.y) - entityMemory.m_staticRenderComponents[entityMemory.m_dynamicStatusComponents[targetEntity].m_staticEntityID].m_textureHeight;

					// make relative to the main entities location
					
					dst.x = dst.x - (mainEntitylocation.x * PIXEL_TO_METER) + displayMode.w / 2;
					dst.y = dst.y - (mainEntitylocation.y * PIXEL_TO_METER) + displayMode.h / 2;

					entityMemory.m_dynamicRenderComponents[targetEntity].m_dstRect.x = dst.x;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_dstRect.y = dst.y;

					// set health bar coordinates
					entityMemory.m_dynamicHealthComponents[targetEntity].m_healthNormalCurrent = (entityMemory.m_dynamicHealthComponents[targetEntity].m_healthNormalCurrent + 1) % entityMemory.m_staticHealthComponents[staticID].m_healthNormal;
					float healthPercentage = (entityMemory.m_dynamicHealthComponents[targetEntity].m_healthNormalCurrent * 1.0f) / entityMemory.m_staticHealthComponents[staticID].m_healthNormal;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_healthBarRect.w = static_cast<int>(entityMemory.m_staticRenderComponents[staticID].m_textureWidth * healthPercentage);
					entityMemory.m_dynamicRenderComponents[targetEntity].m_healthBarRect.x = dst.x;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_healthBarRect.y = dst.y - 10;

					b2Vec2 orientation = entityMemory.m_dynamicTargetComponents[targetEntity].m_orientation;
					entityMemory.m_dynamicRenderComponents[targetEntity].m_angle = (atan2(orientation.y, orientation.x)) * (180.0f / static_cast<float>(M_PI)) - 90.0f;
				}

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes