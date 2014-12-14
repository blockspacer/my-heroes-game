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
				{
					// basic attack only
					
					int actionStartTime = entityMemory.m_statusComponents.GetBusyStatusStartTime_D(targetEntity);
					int actionTotalTime = entityMemory.m_statusComponents.GetBusyStatusTotalTime_D(targetEntity);
					int currentTime = SDL_GetTicks();
					int staticID = entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity);

					// check whether we have reached the point where we actually do damage
					if (currentTime - actionStartTime > actionTotalTime * entityMemory.m_actionComponents.GetNormalAttackDamagePoint_S(staticID) &&
						entityMemory.m_actionComponents.GetNormalAttackDamagePoint_D(targetEntity) == false)
					{
						// do damage
						entityMemory.m_actionComponents.SetNormalAttackDamagePoint_D(targetEntity, true);
					}
				}

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

			} // namespace WarriorSystems
		} // namespace GamePlay
	} // namespace States
} // namespace Heroes