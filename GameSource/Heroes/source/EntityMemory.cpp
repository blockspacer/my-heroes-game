#include <iostream>

#include <SDL_image.h>

#include "Engine/Log.h"
#include "States/GamePlayState/Systems/PlayerSystems.h"
#include "States/GamePlayState/Systems/WarriorSystems.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

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
					for (EntityDynamicIDType i = 0; i < EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE; i++)
					{
						m_freeEntities.push_back(i);
					}

					SDL_assert(m_freeEntities.size() == EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
					SDL_assert(m_usedEntities.size() == 0);
				}

				EntityMemory::~EntityMemory()
				{
					// manually delete entity texture
					for (int i = 0; i < m_freeStaticEntityID; i++)
					{
						m_sdlUtilityTool.DestroyTexture(m_staticRenderComponents[i].m_entityTexture);
						m_sdlUtilityTool.DestroyTexture(m_staticRenderComponents[i].m_healthBarTexture);
					}
				}

				EntityDynamicIDType EntityMemory::LoadDynamicWarrior(b2Vec2 position, b2Vec2 orientation)
				{
					EntityStaticIDType staticWarriorID = m_staticEntityMap["Warrior"];

					EntityDynamicIDType id = m_freeEntities.front();

					// manually load the player controlled entity
					
					m_dynamicSystemComponents[id].m_targetSystem = WarriorSystems::WarriorTargetSystem;
					m_dynamicSystemComponents[id].m_directionSystem = WarriorSystems::WarriorDirectionSystem;

					m_dynamicStatusComponents[id].m_staticEntityID = staticWarriorID; // warrior is the only static entity
					m_dynamicStatusComponents[id].m_action = ActionType::NO_ACTION;
					m_dynamicStatusComponents[id].m_movement = MovementType::NO_MOVEMENT;
					m_dynamicStatusComponents[id].m_status = StatusType::ALIVE;
					m_dynamicStatusComponents[id].m_deathTimer = m_staticStatusComponents[staticWarriorID].m_deathTimer;

					m_dynamicHealthComponents[id].m_healthNormalCurrent = m_staticHealthComponents[staticWarriorID].m_healthNormal / 2;
					m_dynamicHealthComponents[id].m_damageDirect = 0;
					m_dynamicHealthComponents[id].m_damageDirectSource = -1;

					// TODO
					// m_physicsComponents
					b2BodyDef def;
					b2FixtureDef fixDef;
					def.type = b2_dynamicBody;
					def.position = position; // center
					def.angle = 0;
					def.fixedRotation = true;
					m_dynamicPhysicsComponents[id].body = m_entityWorld.CreateBody(&def);
					m_dynamicPhysicsComponents[id].body->SetUserData((void*)id);
					std::cout << m_dynamicPhysicsComponents[id].body->GetUserData() << std::endl;
					b2CircleShape* shape = new b2CircleShape;
					shape->m_radius = 0.5;
					shape->m_p = b2Vec2(0, 0.25);
					m_dynamicPhysicsComponents[id].shapes.push_back(shape);
					fixDef.shape = shape;
					fixDef.density = 1;
					fixDef.friction = 1;
					fixDef.isSensor = false;
					fixDef.filter.categoryBits = EntityCollisionMasks::ALLY_BODY;
					fixDef.filter.maskBits = EntityCollisionCategories::ALLY_BODY_COL;
					m_dynamicPhysicsComponents[id].body->CreateFixture(&fixDef);
					// m_targetComponents
					// m_actionComponents
					// m_directionComponents
					m_dynamicDirectionComponents[id].m_direction = orientation;
					// m_movementComponents
					// m_renderComponents


					m_dynamicRenderComponents[id].m_dstRect.w = 64;
					m_dynamicRenderComponents[id].m_dstRect.h = 64;
					m_dynamicRenderComponents[id].m_dstRect.x = -32;
					m_dynamicRenderComponents[id].m_dstRect.y = -32;
					m_dynamicRenderComponents[id].m_healthBarRect.h = 8;
					m_dynamicRenderComponents[id].m_healthBarRect.w = m_staticRenderComponents[staticWarriorID].m_textureWidth;
					m_dynamicRenderComponents[id].m_angle = 0.0f;

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
				}

				EntityDynamicIDType EntityMemory::OverrideMainEntity(EntityDynamicIDType entityID)
				{					
					m_dynamicSystemComponents[entityID].m_targetSystem = PlayerSystems::MainEntityTargetSystem; // player system
					m_dynamicSystemComponents[entityID].m_directionSystem = PlayerSystems::MainEntityDirectionSystem; // player system
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

