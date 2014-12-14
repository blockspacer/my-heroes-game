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

				bool EntityQuery::ReportFixture(b2Fixture* fixture)
				{
					// logic to get id of the body and then add it to the list
					assert(sizeof(void*) == sizeof(EntityDynamicIDType));
					m_queryList->push_back((EntityDynamicIDType) fixture->GetBody()->GetUserData());
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
				}

				EntityMemory::~EntityMemory()
				{
					// manually delete entity texture
					for (int i = 0; i < m_freeStaticEntityID; i++)
					{
						//m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetEntityTexture_S(i));
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetStatusTexture_S(i));
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetStandingFramesTexture_S(i));
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetMovingFramesTexture_S(i));
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetBasicAttackFramesTexture_S(i));
					}
				}

				EntityDynamicIDType EntityMemory::OverrideMainEntity(EntityDynamicIDType entityID)
				{					
					m_systemsComponents.SetTargetSystem_D(entityID, PlayerSystems::MainEntityTargetSystem); // player system
					m_systemsComponents.SetDirectionSystem_D(entityID, PlayerSystems::MainEntityDirectionSystem); // player system
					m_mainEntityDynamicID = entityID;
					return entityID;
				}

				void EntityMemory::ReleaseEntites(std::list<EntityDynamicIDType>& entityIDs)
				{
					for (EntityDynamicIDType &c : entityIDs)
					{
						g_assert(false);
					}
				}

				void EntityMemory::QueryEntityWorld(std::list<EntityDynamicIDType>& entityList, b2AABB boundingArea)
				{
					g_assert(entityList.size() == 0);

					EntityQuery entityQuery;
					entityQuery.m_queryList = &entityList;

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

