#include <iostream>

#include <SDL_image.h>

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

				EntityMemory::EntityMemory(Engine::SDLUtilityTool& sdlUtilityTool) : m_sdlUtilityTool(sdlUtilityTool)
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
					m_sdlUtilityTool.DestroyTexture(m_staticRenderComponents[0].m_texture);
				}

				EntityDynamicIDType EntityMemory::LoadMainEntity(SDL_Renderer* renderer)
				{

					StaticEntityIDType staticWarriorID = 0;
					// create static entity of warrior
					m_staticStatusComponents[staticWarriorID].m_countDownBase = 10;
					m_staticHealthComponents[staticWarriorID].m_healthNormalBase = 100;
					m_staticHealthComponents[staticWarriorID].m_resistanceNormalBase = 0;
					m_staticActionComponents[staticWarriorID].m_normalBase = 20;
					m_staticMovementComponents[staticWarriorID].m_baseMax = 10;
					m_staticRenderComponents[staticWarriorID].m_texture = m_sdlUtilityTool.LoadImageTexture("./Resources/Textures/TestEntity.png", renderer);
					
					SDL_QueryTexture(m_staticRenderComponents[staticWarriorID].m_texture, NULL, NULL, &(m_staticRenderComponents[staticWarriorID].m_textureWidth), &(m_staticRenderComponents[staticWarriorID].m_textureHeight));

					EntityDynamicIDType id = m_freeEntities.front();

					// manually load the player controlled entity
					m_dynamicSystemComponents[id].m_statusSystem = WarriorSystems::WarriorStatusSystem;
					m_dynamicSystemComponents[id].m_healthSystem = WarriorSystems::WarriorHealthSystem;
					m_dynamicSystemComponents[id].m_targetSystem = PlayerSystems::MainEntityTargetSystem; // player system
					m_dynamicSystemComponents[id].m_actionSystem = WarriorSystems::WarriorActionSystem;
					m_dynamicSystemComponents[id].m_directionSystem = PlayerSystems::MainEntityDirectionSystem; // player system
					m_dynamicSystemComponents[id].m_movementSystem = WarriorSystems::WarriorMovementSystem;
					m_dynamicSystemComponents[id].m_renderUpdateSystem = WarriorSystems::WarriorRenderUpdateSystem;

					m_dynamicStatusComponents[id].m_staticEntityID = staticWarriorID;// warrior is the only static entity
					m_dynamicStatusComponents[id].m_action = ActionType::NO_ACTION;
					m_dynamicStatusComponents[id].m_movement = MovementType::NO_MOVEMENT;
					m_dynamicStatusComponents[id].m_status = StatusType::ALIVE;
					m_dynamicStatusComponents[id].m_countDownCurrent = m_staticStatusComponents[staticWarriorID].m_countDownBase;
					
					m_dynamicHealthComponents[id].m_healthNormalCurrent = m_staticHealthComponents[staticWarriorID].m_healthNormalBase;
					m_dynamicHealthComponents[id].m_damageDirect = 0;
					m_dynamicHealthComponents[id].m_damageDirectSource = -1;

					// TODO
					// m_physicsComponents
					b2BodyDef def;
					b2FixtureDef fixDef;
					def.type = b2_dynamicBody;
					def.position = b2Vec2(id * 2, id * 2); // center
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
					m_dynamicDirectionComponents[id].m_direction = b2Vec2_zero;
					// m_movementComponents
					// m_renderComponents
					

					m_dynamicRenderComponents[id].m_dstRect.w = 64;
					m_dynamicRenderComponents[id].m_dstRect.h = 64;
					m_dynamicRenderComponents[id].m_dstRect.x = -32;
					m_dynamicRenderComponents[id].m_dstRect.y = -32;
					m_dynamicRenderComponents[id].m_angle = 0.0f;

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
				}

				int EntityMemory::LoadEntityFile(const char* entityFile, SDL_Renderer* renderer)
				{
					EntityDynamicIDType id = m_freeEntities.front();

					// loads static data
					// loads the dynamic data
					SDL_assert(false);

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
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
					
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

