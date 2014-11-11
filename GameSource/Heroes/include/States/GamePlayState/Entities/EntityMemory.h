#pragma once

#include <list>
#include <vector>
#include <map> // future find better implementation

#include <tinyxml2.h>

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

			class EntityLoader;

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

				EntityMemory(Engine::SDLUtilityTool& sdlUtilityTool, SDL_Window* m_window);
				~EntityMemory();

				EntityDynamicIDType OverrideMainEntity(EntityDynamicIDType entityID);

				EntityDynamicIDType LoadDynamicWarrior(b2Vec2 position, b2Vec2 orientation);

				// Releases the entities specified in the list
				void ReleaseEntites(std::list<EntityDynamicIDType>& entityIDs);

				// Queries the b2 world with the AABB and returns a list of the entities
				void QueryEntityWorld(std::list<EntityDynamicIDType>& entityList, b2AABB boundingArea);

				void UpdateEntityWorld(float time);

				//int GetWindowWidth();
				//int GetWindowHeight();
				int GetMainEntityDynamicID();

				DynamicSystemsComponent m_dynamicSystemComponents[EntityMemoryConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				std::vector<StaticSystemsComponent> m_staticSystemComponents{ STATIC_ENTITY_MEMORY_START_SIZE };

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

				friend class EntityLoader;

				Engine::SDLUtilityTool& m_sdlUtilityTool;
				int m_windowWidth{ 0 };
				int m_windowHeight{ 0 };
				int m_mainEntityDynamicID{ -1 };
				int m_freeStaticEntityID{ 0 };

				b2World m_entityWorld{ b2Vec2_zero };

				// internally management system
				std::list<EntityDynamicIDType> m_freeEntities;
				std::list<EntityDynamicIDType> m_usedEntities;

				std::map<std::string, EntityStaticIDType> m_staticEntityMap;
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

