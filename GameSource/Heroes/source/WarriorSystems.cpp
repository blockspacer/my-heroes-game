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
				{
					int damage = entityMemory.m_healthComponents.GetDirectDamage_D(targetEntity);
					if (damage > 0)
					{
						entityMemory.m_healthComponents.SetDirectDamage_D(targetEntity, 0);
						entityMemory.m_healthComponents.SetNormalHealth_D(targetEntity, entityMemory.m_healthComponents.GetNormalHealth_D(targetEntity) - damage);
						entityMemory.m_AIComponents.SwitchToTarget_D(targetEntity, entityMemory.m_healthComponents.GetDirectDamageSource_D(targetEntity), entityMemory);
					}

					if (entityMemory.m_healthComponents.GetNormalHealth_D(targetEntity) <= 0)
					{
						//entityMemory.m_statusComponents.SetBusyStatus(targetEntity, BusyStatusType::DEAD, entityMemory.m_healthComponents.GetDeathTimer_S(targetEntity) * 100);
						entityMemory.m_statusComponents.SetBusyStatus_D(targetEntity, BusyStatusType::DEAD, 1000);
					}
					
				}

				void WarriorAISystem(int targetEntity, GamePlay::EntityMemory& entityMemory, Engine::InputHandler& inputHandler)
				{
					// check that target is still valid
					int staticID = entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity);
					int target = entityMemory.m_AIComponents.GetTarget_D(targetEntity, entityMemory);
					
					if (target != -1)
					{
						// check range
						b2Vec2 centralizedPosition = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetPosition() - entityMemory.m_physicsComponents.GetEntityBody_D(target)->GetPosition();
						float distanceToTarget = centralizedPosition.Length();

						if (distanceToTarget <= entityMemory.m_AIComponents.GetTrackingRange_S(staticID))
						{
							centralizedPosition.Normalize();
							entityMemory.m_AIComponents.SetOrientation_D(targetEntity, centralizedPosition);
							entityMemory.m_AIComponents.SetDirection_D(targetEntity, -1 * centralizedPosition);
							entityMemory.m_AIComponents.SetMovementPercentage_D(targetEntity, 0.1f);

							// check attack distance and attack
							if (distanceToTarget < entityMemory.m_actionComponents.GetNormalAttackRange_S(staticID))
							{
								entityMemory.m_statusComponents.SetBusyStatus_D(targetEntity, BusyStatusType::BASIC_ATTACK, entityMemory.m_actionComponents.GetNormalAttackSpeed_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity)) * 100);
							}
						}
					}
					else
					{
						entityMemory.m_AIComponents.SetMovementPercentage_D(targetEntity, 0.0);
					}
				}

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

						int target = entityMemory.m_AIComponents.GetTarget_D(targetEntity, entityMemory);
						if (target != -1)
						{
							b2Vec2 source = entityMemory.m_physicsComponents.GetEntityBody_D(targetEntity)->GetPosition();
							b2Vec2 sourceOrientation = entityMemory.m_AIComponents.GetOrientation_D(targetEntity);
							float angle = atan2f(sourceOrientation.y, sourceOrientation.x);
							float range = entityMemory.m_actionComponents.GetNormalAttackRange_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity));

							b2RayCastInput rayCastInputCenter;
							rayCastInputCenter.p1.Set(source.x, source.y);
							rayCastInputCenter.p2.Set(source.x - cosf(angle) * range, source.y - sinf(angle) * range); // calculate to point
							rayCastInputCenter.maxFraction = 1.0f;

							b2RayCastInput rayCastInputSide1;
							rayCastInputSide1.p1.Set(source.x, source.y);
							rayCastInputSide1.p2.Set(source.x - cosf(angle - (M_PI / 4)) * range, source.y - sinf(angle - (M_PI / 4)) * range); // calculate to point
							rayCastInputSide1.maxFraction = 1.0f;

							b2RayCastInput rayCastInputSide2;
							rayCastInputSide2.p1.Set(source.x, source.y);
							rayCastInputSide2.p2.Set(source.x - cosf(angle + (M_PI / 4)) * range, source.y - sinf(angle + (M_PI / 4)) * range); // calculate to point
							rayCastInputSide2.maxFraction = 1.0f;

							b2RayCastOutput rayCastOutput;

							bool hit = false;
							b2Fixture* fixtureList = entityMemory.m_physicsComponents.GetEntityBody_D(entityMemory.m_AIComponents.GetTarget_D(targetEntity, entityMemory))->GetFixtureList();
							while (fixtureList != nullptr && !hit)
							{
								if (!fixtureList->IsSensor())
								{
									if (fixtureList->RayCast(&rayCastOutput, rayCastInputCenter, 0))
									{
										hit = true;
									}
									else if (fixtureList->RayCast(&rayCastOutput, rayCastInputSide1, 0))
									{
										hit = true;
									}
									else if (fixtureList->RayCast(&rayCastOutput, rayCastInputSide2, 0))
									{
										hit = true;
									}
								}

								fixtureList = fixtureList->GetNext();
							}

							if (hit)
							{
								// actually do damage
								int oldDamage = entityMemory.m_healthComponents.GetDirectDamage_D(target);
								int newDamage = entityMemory.m_actionComponents.GetNormalAttackDamage_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity));
								entityMemory.m_healthComponents.SetDirectDamage_D(target, oldDamage + newDamage);
								entityMemory.m_healthComponents.SetDirectDamageSource_D(target, targetEntity);
							}
						}
						

						entityMemory.m_actionComponents.SetNormalAttackDamagePoint_D(targetEntity, true);
					}
					else if (currentTime - actionStartTime < actionTotalTime * entityMemory.m_actionComponents.GetNormalAttackDamagePoint_S(staticID) &&
							entityMemory.m_actionComponents.GetNormalAttackDamagePoint_D(targetEntity) == true)
					{
						entityMemory.m_actionComponents.SetNormalAttackDamagePoint_D(targetEntity, false);
					}

				}

				void WarriorMovementSystem(int targetEntity, GamePlay::EntityMemory& entityMemory)
				{
					

					float movementPercentage = entityMemory.m_AIComponents.GetMovementPercentage_D(targetEntity);
					float desiredVelocity = 0;
					if (movementPercentage > 0.0f)
					{
						desiredVelocity = entityMemory.m_movementComponents.GetMovementSpeed_S(entityMemory.m_statusComponents.GetStaticEntityID_D(targetEntity)) * entityMemory.m_AIComponents.GetMovementPercentage_D(targetEntity);
					}
					
					// change to have incremental change
					float desiredVelocityX = desiredVelocity * entityMemory.m_AIComponents.GetDirectionX_D(targetEntity);
					float desiredVelocityY = desiredVelocity * entityMemory.m_AIComponents.GetDirectionY_D(targetEntity);

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