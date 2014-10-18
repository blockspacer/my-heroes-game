#pragma once

#include <list>

#include "States/GamePlayState/Entities/EntityComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
				typedef int EntityIDType;

				enum EntityMemorySize
				{
					SIZE = 1000
				};

				enum ComponentMask
				{
					STATUS,
					HEALTH,
					TARGET,
					ACTION,
					DIRECTION,
					MOVEMENT,
					RENDER,
					PHYSICS
				};

				class EntityQuery final : public b2QueryCallback
				{
				public:

					virtual bool ReportFixture(b2Fixture* fixture);

					std::list<EntityIDType> * m_queryList{ nullptr };
				};

				class EntityMemory final
				{
				public:

					EntityMemory();
					~EntityMemory();

					EntityIDType LoadMainEntity(SDL_Renderer* renderer);

					// Loads a single entity returning its id
					EntityIDType LoadEntityFile(const char* entityFile, SDL_Renderer* renderer);

					// Releases the entities specified in the list
					void ReleaseEntites(std::list<EntityIDType>& entityIDs);

					// Queries the b2 world with the AABB and returns a list of the entities
					void QueryEntityWorld(std::list<EntityIDType>& entityList, b2AABB boundingArea);

					void UpdateEntityWorld(float time);

					// load entity file
					// the big array of entities

					// get Component list (ie get all the health components)

					// query entity based on id and bounding box

					/*
					public void Load(EntityGroup entity_group, int main_entity)
					{
						if (entity_group == null || main_entity < 0 || main_entity > (int) ENTITY_CONSTANTS.MAX_ENTITIES)
						{
							Console.WriteLine("Null/Bad parameters in Load() of EntitySystemManager");
						}
						entity_group_ = entity_group;
						main_entity_ = main_entity;
					}

					public LinkedList<int> QueryEntityWorld(Camera camera)
					{
						return entity_group_.QueryWorld(camera.GetSimBottomLeft(), camera.GetSimTopRight());
					}

					public void UpdateEntities(LinkedList<int> entities, Camera camera)
					{
						Console.WriteLine("Updating World");
						entity_group_.UpdateWorld();


						// health system
						if (health_update_ == (int)ENTITY_SYSTEM_CONSTANTS.HEALTH_UPDATE)
						{
							Console.WriteLine("Health");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].health != null)
								{
									entity_group_.entity_systems[it.Value].health.Run(it.Value, entity_group_);
								} 
							}
							health_update_ = -1;
						}

						// target system
						if (target_update_ == (int)ENTITY_SYSTEM_CONSTANTS.TARGET_UPDATE)
						{
							Console.WriteLine("Target");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].target != null)
								{
									entity_group_.entity_systems[it.Value].target.Run(it.Value, entity_group_);
								} 
							}
							target_update_ = -1;
						}

						// action system
						if (action_update_ == (int)ENTITY_SYSTEM_CONSTANTS.ACTION_UPDATE)
						{
							Console.WriteLine("Action");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].action != null)
								{
									entity_group_.entity_systems[it.Value].action.Run(it.Value, entity_group_);
								} 
							}
							action_update_ = -1;
						}

						// direction system
						if (direction_update_ == (int)ENTITY_SYSTEM_CONSTANTS.DIRECTION_UPDATE)
						{
							Console.WriteLine("Direction");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].direction != null)
								{
									entity_group_.entity_systems[it.Value].direction.Run(it.Value, entity_group_);
								} 
							}
							direction_update_ = -1;
						}

						// movement system
						if (movement_update_ == (int)ENTITY_SYSTEM_CONSTANTS.MOVEMENT_UPDATE)
						{
							Console.WriteLine("Moving");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].movement != null)
								{
									entity_group_.entity_systems[it.Value].movement.Run(it.Value, entity_group_);
								} 
							}
							movement_update_ = -1;
						}

						// render system
						if (render_update_ == (int)ENTITY_SYSTEM_CONSTANTS.RENDER_UPDATE)
						{
							Console.WriteLine("Rendering");
							for (LinkedListNode<int> it = entities.First; it != null; it = it.Next)
							{
								if (entity_group_.entity_systems[it.Value].render_update != null)
								{
									entity_group_.entity_systems[it.Value].render_update.Update(it.Value, entity_group_, camera.GetDisplayCoordinate());
								} 
							}
							render_update_ = -1;
						}

						// increment the update cycles (always happens)
						health_update_++;
						target_update_++;
						action_update_++;
						direction_update_++;
						movement_update_++;
						render_update_++;
					}

					public Vector2 GetMainEntityLocation()
					{
						return entity_group_.entity_physics[main_entity_].body.Position;
					}
					*/

					ComponentSystems m_systemComponents[EntityMemorySize::SIZE];

					ComponentStatus m_statusComponents[EntityMemorySize::SIZE];

					ComponentHealth m_healthComponents[EntityMemorySize::SIZE];

					ComponentTarget m_targetComponents[EntityMemorySize::SIZE];
					ComponentAction m_actionComponents[EntityMemorySize::SIZE];

					ComponentDirection m_directionComponents[EntityMemorySize::SIZE];
					ComponentMovement m_movementComponents[EntityMemorySize::SIZE];

					ComponentRender m_renderComponents[EntityMemorySize::SIZE];

					ComponentPhysics m_physicsComponents[EntityMemorySize::SIZE];

				private:

					b2World m_entityWorld{ b2Vec2_zero };

					// internally management system
					std::list<EntityIDType> m_freeEntities;
					std::list<EntityIDType> m_usedEntities;

				};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

