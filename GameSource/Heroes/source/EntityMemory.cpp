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
					assert(sizeof(void*) == sizeof(EntityIDType));
					m_queryList->push_back((EntityIDType) fixture->GetBody()->GetUserData());
					return true;
				}

				EntityMemory::EntityMemory()
				{

					// fill up the free entities
					for (EntityIDType i = 0; i < EntityMemorySize::SIZE; i++)
					{
						m_freeEntities.push_back(i);
					}

					SDL_assert(m_freeEntities.size() == EntityMemorySize::SIZE);
					SDL_assert(m_usedEntities.size() == 0);
				}

				EntityMemory::~EntityMemory()
				{

				}

				EntityIDType EntityMemory::LoadMainEntity(SDL_Renderer* renderer)
				{
					EntityIDType id = m_freeEntities.front();

					// manually load the player controlled entity
					m_systemComponents[id].m_statusSystem = WarriorSystems::WarriorStatusSystem;
					m_systemComponents[id].m_healthSystem = WarriorSystems::WarriorHealthSystem;
					m_systemComponents[id].m_targetSystem = PlayerSystems::MainEntityTargetSystem; // player system
					m_systemComponents[id].m_actionSystem = WarriorSystems::WarriorActionSystem;
					m_systemComponents[id].m_directionSystem = PlayerSystems::MainEntityDirectionSystem; // player system
					m_systemComponents[id].m_movementSystem = WarriorSystems::WarriorMovementSystem;
					m_systemComponents[id].m_renderUpdateSystem = WarriorSystems::WarriorRenderUpdateSystem;

					m_statusComponents[id].m_action = ActionType::NO_ACTION;
					m_statusComponents[id].m_movement = MovementType::NO_MOVEMENT;
					m_statusComponents[id].m_countDownBase = 10;
					m_statusComponents[id].m_countDownCurrent = 10;
					m_statusComponents[id].m_status = StatusType::ALIVE;

					m_healthComponents[id].m_healthNormalBase = 100;
					m_healthComponents[id].m_healthNormalCurrent = 100;
					m_healthComponents[id].m_resistanceNormalBase = 0;
					m_healthComponents[id].m_damageDirect = 0;
					m_healthComponents[id].m_damageDirectSource = -1;

					// TODO
					// m_physicsComponents
					b2BodyDef def;
					b2FixtureDef fixDef;
					def.type = b2_dynamicBody;
					def.position = b2Vec2(id * 2, id * 2); // center
					def.angle = 0;
					def.fixedRotation = true;
					m_physicsComponents[id].body = m_entityWorld.CreateBody(&def);
					m_physicsComponents[id].body->SetUserData((void*) id);
					std::cout << m_physicsComponents[id].body->GetUserData() << std::endl;
					b2CircleShape* shape = new b2CircleShape;
					shape->m_radius = 0.5;
					shape->m_p = b2Vec2(0, 0.25);
					m_physicsComponents[id].shapes.push_back(shape);
					fixDef.shape = shape;
					fixDef.density = 1;
					fixDef.friction = 1;
					fixDef.isSensor = false;
					fixDef.filter.categoryBits = EntityBodyCategories::ALLY_BODY;
					fixDef.filter.maskBits = EntityCollisionCategories::ALLY_BODY_COL;
					m_physicsComponents[id].body->CreateFixture(&fixDef);
					// m_targetComponents
					// m_actionComponents
					m_actionComponents[id].m_normalBase = 20;
					// m_directionComponents
					m_directionComponents[id].m_direction = b2Vec2_zero;
					// m_movementComponents
					m_movementComponents[id].m_baseMax = 10; //?
					// m_renderComponents
					SDL_Surface* imageSurface = IMG_Load("D:/GameDevelopment/GameSource/Resources/Textures/TestEntity.png");
					m_renderComponents[id].m_texture = SDL_CreateTextureFromSurface(renderer, imageSurface); // needs sdl cleanup
					SDL_FreeSurface(imageSurface);

					m_renderComponents[id].m_dstRect.w = 64;
					m_renderComponents[id].m_dstRect.h = 64;
					m_renderComponents[id].m_dstRect.x = -32;
					m_renderComponents[id].m_dstRect.y = -32;
					m_renderComponents[id].m_angle = 0.0f;

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
				}

				int EntityMemory::LoadEntityFile(const char* entityFile, SDL_Renderer* renderer)
				{
					EntityIDType id = m_freeEntities.front();

					// loads static data
					// loads the dynamic data
					SDL_assert(false);

					m_freeEntities.pop_front();
					m_usedEntities.push_back(id);

					return id;
				}

				void EntityMemory::ReleaseEntites(std::list<EntityIDType>& entityIDs)
				{
					for (EntityIDType &c : entityIDs)
					{
						SDL_assert(false);
					}
				}

				void EntityMemory::QueryEntityWorld(std::list<EntityIDType>& entityList, b2AABB boundingArea)
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

