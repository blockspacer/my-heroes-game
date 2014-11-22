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

					SDL_assert(m_freeEntities.size() == ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
					SDL_assert(m_usedEntities.size() == 0);
				}

				EntityMemory::~EntityMemory()
				{
					// manually delete entity texture
					for (int i = 0; i < m_freeStaticEntityID; i++)
					{
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetEntityTexture_S(i));
						m_sdlUtilityTool.DestroyTexture(m_renderComponents.GetHealthBarTexture_S(i));
					}
				}

				EntityDynamicIDType EntityMemory::LoadDynamicWarrior(b2Vec2 position, b2Vec2 orientation)
				{
					EntityStaticIDType staticWarriorID = m_staticEntityMap["Warrior"];

					EntityDynamicIDType id = m_freeEntities.front();
					

					// manually load the player controlled entity

					m_systemsComponents.SetTargetSystem_D(id, m_systemsComponents.GetTargetSystem_S(staticWarriorID));
					m_systemsComponents.SetDirectionSystem_D(id, m_systemsComponents.GetDirectionSystem_S(staticWarriorID));

					m_statusComponents.SetStaticEntityID_D(id, staticWarriorID); // warrior is the only static entity
					m_statusComponents.SetAction_D(id, ActionType::NO_ACTION);
					m_statusComponents.SetMovement_D(id, MovementType::NO_MOVEMENT);
					m_statusComponents.SetStatus_D(id, StatusType::ALIVE);
					m_statusComponents.SetDeathTimer_D(id, m_statusComponents.GetDeathTimer_S(staticWarriorID));

					m_healthComponents.SetNormalHealth_D(id, m_healthComponents.GetNormalHealth_S(staticWarriorID) / 2);
					m_healthComponents.SetDirectDamage_D(id, 0);
					m_healthComponents.SetDirectDamageSource_D(id, -1);

					// TODO
					// m_physicsComponents
					b2BodyDef def;
					b2FixtureDef fixDef;
					def.type = b2_dynamicBody;
					def.position = position; // center
					def.angle = 0;
					def.fixedRotation = true;
					m_physicsComponents.SetEntityBody_D(id, m_entityWorld.CreateBody(&def));
					m_physicsComponents.GetEntityBody_D(id)->SetUserData((void*)id);
					std::cout << m_physicsComponents.GetEntityBody_D(id)->GetUserData() << std::endl;
					b2CircleShape* shape = new b2CircleShape;
					shape->m_radius = 0.5;
					shape->m_p = b2Vec2(0, 0.25);
					m_physicsComponents.GetEntityShapes_D(id)->push_back(shape);
					fixDef.shape = shape;
					fixDef.density = 1;
					fixDef.friction = 1;
					fixDef.isSensor = false;
					fixDef.filter.categoryBits = EntityCollisionMasks::ALLY_BODY;
					fixDef.filter.maskBits = EntityCollisionCategories::ALLY_BODY_COL;
					m_physicsComponents.GetEntityBody_D(id)->CreateFixture(&fixDef);
					// m_targetComponents
					// m_actionComponents
					// m_directionComponents
					m_directionComponents.SetDirection_D(id, orientation);
					// m_movementComponents
					// m_renderComponents


					m_renderComponents.GetDestinationRect_D(id)->w = 64;
					m_renderComponents.GetDestinationRect_D(id)->h = 64;
					m_renderComponents.GetDestinationRect_D(id)->x = -32;
					m_renderComponents.GetDestinationRect_D(id)->y = -32;
					m_renderComponents.GetHealthBarRect_D(id)->h = 8;
					m_renderComponents.GetHealthBarRect_D(id)->w = m_renderComponents.GetTextureWidth_S(staticWarriorID);
					m_renderComponents.SetAngle_D(id, 0.0f);

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
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
						SDL_assert(false);
					}
				}

				void EntityMemory::QueryEntityWorld(std::list<EntityDynamicIDType>& entityList, b2AABB boundingArea)
				{
					SDL_assert(entityList.size() == 0);

					EntityQuery entityQuery;
					entityQuery.m_queryList = &entityList;

					m_entityWorld.QueryAABB(&entityQuery, boundingArea);
				}

				void EntityMemory::UpdateEntityWorld(float time)
				{
					SDL_assert(time > 0);
					
					m_entityWorld.Step(time, 8, 2);
					m_entityWorld.ClearForces();
				}

				int EntityMemory::GetMainEntityDynamicID()
				{
					SDL_assert(m_mainEntityDynamicID >= 0);
					return m_mainEntityDynamicID;
				}
					
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

