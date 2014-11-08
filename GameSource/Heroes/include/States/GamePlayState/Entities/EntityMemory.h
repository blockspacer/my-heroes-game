﻿#pragma once

#include <list>
#include <vector>
#include "Engine/SDLUtilityTool.h"
#include "States/GamePlayState/Entities/EntityComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			typedef int EntityDynamicIDType;
			typedef int EntityStaticIDType;

			enum EntityMemoryConstants
			{
				DYNAMIC_ENTITY_MEMORY_SIZE = 1000,
				STATIC_ENTITY_MEMORY_START_SIZE = 1
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

				std::list<EntityDynamicIDType> * m_queryList{ nullptr };
			};

			class EntityMemory final
			{
			public:

				EntityMemory(Engine::SDLUtilityTool& sdlUtilityTool);
				~EntityMemory();

				EntityDynamicIDType LoadMainEntity(SDL_Renderer* renderer);

				// Loads a single entity returning its id
				EntityDynamicIDType LoadEntityFile(const char* entityFile, SDL_Renderer* renderer);

				// Releases the entities specified in the list
				void ReleaseEntites(std::list<EntityDynamicIDType>& entityIDs);

				// Queries the b2 world with the AABB and returns a list of the entities
				void QueryEntityWorld(std::list<EntityDynamicIDType>& entityList, b2AABB boundingArea);

				void UpdateEntityWorld(float time);	

				ComponentSystems m_dynamicSystemComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<ComponentSystems> m_staticSystemComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicStatusComponent m_dynamicStatusComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticStatusComponent> m_staticStatusComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicHealthComponent m_dynamicHealthComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticHealthComponent> m_staticHealthComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicTargetComponent m_dynamicTargetComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticTargetComponent> m_staticTargetComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicActionComponent m_dynamicActionComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticActionComponent> m_staticActionComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicDirectionComponent m_dynamicDirectionComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticDirectionComponent> m_staticDirectionComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicMovementComponent m_dynamicMovementComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticMovementComponent> m_staticMovementComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicRenderComponent m_dynamicRenderComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticRenderComponent> m_staticRenderComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

				DynamicPhysicsComponent m_dynamicPhysicsComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticPhysicsComponent> m_staticPhysicsComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

			private:

				Engine::SDLUtilityTool& m_sdlUtilityTool;

				b2World m_entityWorld{ b2Vec2_zero };

				// internally management system
				std::list<EntityDynamicIDType> m_freeEntities;
				std::list<EntityDynamicIDType> m_usedEntities;

			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

