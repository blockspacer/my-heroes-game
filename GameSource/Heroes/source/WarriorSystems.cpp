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
					

					float movementPercentage = entityMemory.m_directionComponents.GetMovementPercentage_D(targetEntity);
					float desiredVelocity = 0;
					if (movementPercentage > 0.0f)
					{
						desiredVelocity = entityMemory.m_movementComponents.GetMovementSpeed_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity)) * entityMemory.m_directionComponents.GetMovementPercentage_D(targetEntity);
					}
					
					// change to have incremental change
					float desiredVelocityX = desiredVelocity * entityMemory.m_directionComponents.GetDirectionX_D(targetEntity);
					float desiredVelocityY = desiredVelocity * entityMemory.m_directionComponents.GetDirectionY_D(targetEntity);

					// do the math based on massed and preferred velocity of the body
					b2Vec2 vel = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetLinearVelocity();
					float velChangeX = desiredVelocityX - vel.x;
					float impulseX = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetMass() * velChangeX; //disregard time factor
					float velChangeY = desiredVelocityY - vel.y;
					float impulseY = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetMass() * velChangeY; //disregard time factor

					entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetWorldCenter(), true);
				}

				void WarriorRenderUpdateSystem(int targetEntity, GamePlay::EntityMemory& entityMemory, SDL_Window* window)
				{
					SDL_DisplayMode displayMode;
					SDL_GetWindowDisplayMode(window, &displayMode);

					EntityStaticIDType staticID = entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity);
					b2Vec2 mainEntitylocation = entityMemory.m_physicsComponents.GetEntityBody_D(entityMemory.GetMainEntityDynamicID())->GetPosition();
					b2Vec2 location = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetPosition();
					SDL_Rect dst;

					// determine pixel location from simulation world
					dst.x = Meter2Pixel(location.x) - entityMemory.m_renderComponents.GetTextureWidth_S(staticID);
					dst.y = Meter2Pixel(location.y) - entityMemory.m_renderComponents.GetTextureHeight_S(staticID);

					// make relative to the main entities location
					
					dst.x = dst.x - static_cast<int>(mainEntitylocation.x * PIXEL_TO_METER) + displayMode.w / 2;
					dst.y = dst.y - static_cast<int>(mainEntitylocation.y * PIXEL_TO_METER) + displayMode.h / 2;

					entityMemory.m_renderComponents.GetDestinationRect_D(targetEntity)->x = dst.x;
					entityMemory.m_renderComponents.GetDestinationRect_D(targetEntity)->y = dst.y;

					// set health bar coordinates
					entityMemory.m_healthComponents.SetNormalHealth_D(targetEntity, (entityMemory.m_healthComponents.GetNormalHealth_D(targetEntity) + 1) % entityMemory.m_healthComponents.GetNormalHealth_S(staticID));
					float healthPercentage = (entityMemory.m_healthComponents.GetNormalHealth_D(targetEntity) * 1.0f) / entityMemory.m_healthComponents.GetNormalHealth_S(staticID);
					entityMemory.m_renderComponents.GetHealthBarRect_D(targetEntity)->w = static_cast<int>(entityMemory.m_renderComponents.GetTextureWidth_S(staticID) * healthPercentage);
					entityMemory.m_renderComponents.GetHealthBarRect_D(targetEntity)->x = dst.x;
					entityMemory.m_renderComponents.GetHealthBarRect_D(targetEntity)->y = dst.y - 10;

					b2Vec2 orientation = entityMemory.m_targetComponents.GetOrientation_D(targetEntity);
					entityMemory.m_renderComponents.SetAngle_D(targetEntity, (atan2(orientation.y, orientation.x)) * (180.0f / static_cast<float>(M_PI)) - 90.0f);
				}

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes