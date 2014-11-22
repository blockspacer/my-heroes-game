#pragma once

#include <list>
#include <vector>
#include <map> // future find better implementation
#include <array>

#include <tinyxml2.h>

#include "Engine/SDLUtilityTool.h"

// the various component containers
#include "States/GamePlayState/Entities/SystemsComponents.h"
#include "States/GamePlayState/Entities/StatusComponents.h"
#include "States/GamePlayState/Entities/HealthComponents.h"
#include "States/GamePlayState/Entities/TargetComponents.h"
#include "States/GamePlayState/Entities/ActionComponents.h"
#include "States/GamePlayState/Entities/DirectionComponents.h"
#include "States/GamePlayState/Entities/MovementComponents.h"
#include "States/GamePlayState/Entities/PhysicsComponents.h"
#include "States/GamePlayState/Entities/RenderComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			typedef int EntityDynamicIDType;
			typedef int EntityStaticIDType;

			class EntityLoader;
			class StatusComponents;

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

				SystemsComponents m_systemsComponents{ *this };
				StatusComponents m_statusComponents{ *this };
				HealthComponents m_healthComponents{ *this };
				TargetComponents m_targetComponents{ *this };
				ActionComponents m_actionComponents{ *this };
				DirectionComponents m_directionComponents{ *this };
				MovementComponents m_movementComponents{ *this };
				RenderComponents m_renderComponents{ *this };
				PhysicsComponents m_physicsComponents{ *this };

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

