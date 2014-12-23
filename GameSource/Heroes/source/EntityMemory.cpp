#include <iostream>

#include <SDL_image.h>

#include "Engine/Log.h"
#include "States/GamePlayState/Entities/EntityComponentConstants.h"
#include "States/GamePlayState/Systems/PlayerSystems.h"
#include "States/GamePlayState/Systems/WarriorSystems.h"
#include "States/GamePlayState/Entities/EntityMemory.h"
#include "States/GamePlayState/Entities/StatusComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			EntityMemory::EntityContactListener::EntityContactListener(EntityMemory& entityMemory) : b2ContactListener(), m_entityMemory(entityMemory) {}

			void EntityMemory::EntityContactListener::BeginContact(b2Contact* contact) {
				// figure out information about contact

				b2Fixture* fixtureA = contact->GetFixtureA();
				b2Fixture* fixtureB = contact->GetFixtureB();

				//make sure only one of the fixtures was a sensor
				bool sensorA = fixtureA->IsSensor();
				bool sensorB = fixtureB->IsSensor();

				// only one is a sensor
				if (sensorA ^ sensorB)
				{
					b2Fixture* sensor;
					b2Fixture* entity;

					if (sensorA)
					{
						sensor = fixtureA;
						entity = fixtureB;
					}
					else
					{
						sensor = fixtureB;
						entity = fixtureA;
					}

					// if alive put try and add it
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D((int)entity->GetBody()->GetUserData()) == ActiveStatusType::ACTOR)
					{
						m_entityMemory.m_AIComponents.AddTarget_D((int)sensor->GetBody()->GetUserData(), (int)entity->GetBody()->GetUserData(), m_entityMemory);
					}
					
				}
			}

			void EntityMemory::EntityContactListener::EndContact(b2Contact* contact) {
				// figure out information about contact

				b2Fixture* fixtureA = contact->GetFixtureA();
				b2Fixture* fixtureB = contact->GetFixtureB();

				//make sure only one of the fixtures was a sensor
				bool sensorA = fixtureA->IsSensor();
				bool sensorB = fixtureB->IsSensor();

				// only one is a sensor
				if (sensorA ^ sensorB)
				{
					b2Fixture* sensor;
					b2Fixture* entity;

					if (sensorA)
					{
						sensor = fixtureA;
						entity = fixtureB;
					}
					else
					{
						sensor = fixtureB;
						entity = fixtureA;
					}

					m_entityMemory.m_AIComponents.RemoveTarget_D((int)sensor->GetBody()->GetUserData(), (int)entity->GetBody()->GetUserData(), m_entityMemory);
				}
			}

			// Mutiple fixture problem
			bool EntityQuery::ReportFixture(b2Fixture* fixture)
			{
				//quick fix
				if (!fixture->IsSensor())
				{

					//b2Body* body = fixture->GetBody();

					//// go over all the bodies fixture to check whether it has been added
					//b2Fixture* fixtureList = body->GetFixtureList();
					//bool bodyAdded = false;

					//while (fixtureList != nullptr && !bodyAdded)
					//{
					//	// bodyAdded = ?
					//	fixtureList = fixtureList->GetNext();
					//}

					//// logic to get id of the body and then add it to the list
					//
					//if (!bodyAdded)
					//{
					//	assert(sizeof(void*) == sizeof(EntityDynamicIDType));
					//	m_queryList->push_back((EntityDynamicIDType)fixture->GetBody()->GetUserData());
					//}

					assert(sizeof(void*) == sizeof(EntityDynamicIDType));
					m_querySet->insert((EntityDynamicIDType)fixture->GetBody()->GetUserData());
				}
				
				return true;
			}

			EntityMemory::EntityMemory(Engine::SDLUtilityTool& sdlUtilityTool, SDL_Window* window) : m_sdlUtilityTool(sdlUtilityTool)
			{
				// fill up the free entities
				for (EntityDynamicIDType i = 0; i < ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE; i++)
				{
					m_freeEntities.push_back(i);
				}

				g_assert(m_freeEntities.size() == ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
				g_assert(m_usedEntities.size() == 0);

				m_entityWorld.SetContactListener(&m_entityContactListener);
			}

			EntityMemory::~EntityMemory()
			{
				// manually delete entity texture
				for (int i = 0; i < m_freeStaticEntityID; i++)
				{
					//m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetEntityTexture_S(i));
					
					if (m_renderComponents.GetStatusTexture_S(i) != nullptr)
					{
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetStatusTexture_S(i));
					}

					if (m_renderComponents.GetStandingFramesTexture_S(i) != nullptr)
					{
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetStandingFramesTexture_S(i));
					}

					if (m_renderComponents.GetMovingFramesTexture_S(i) != nullptr)
					{
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetMovingFramesTexture_S(i));
					}

					if (m_renderComponents.GetBasicAttackFramesTexture_S(i) != nullptr)
					{
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetBasicAttackFramesTexture_S(i));
					}
					
					
					
					
				}
			}

			EntityDynamicIDType EntityMemory::OverrideMainEntity(EntityDynamicIDType entityID)
			{					
				m_systemsComponents.SetAISystem_D(entityID, PlayerSystems::MainEntityAISystem); // player system
				m_mainEntityDynamicID = entityID;
				return entityID;
			}

			void EntityMemory::QueryEntityWorld(std::unordered_set<EntityDynamicIDType>& entitySet, b2AABB boundingArea)
			{
				g_assert(entitySet.size() == 0);

				EntityQuery entityQuery;
				entityQuery.m_querySet = &entitySet;

				m_entityWorld.QueryAABB(&entityQuery, boundingArea);
			}

			void EntityMemory::UpdateEntityWorld(float time)
			{
				g_assert(time > 0);
					
				m_entityWorld.Step(time, 8, 2);
				m_entityWorld.ClearForces();
			}

			int EntityMemory::GetMainEntityDynamicID()
			{
				g_assert(m_mainEntityDynamicID >= 0);
				return m_mainEntityDynamicID;
			}

			int EntityMemory::GetStaticID()
			{
				std::lock_guard<std::mutex> lock(m_lock);

				int id = m_freeStaticEntityID++;

				return id;
			}
					
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

