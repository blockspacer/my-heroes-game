#pragma once

#include <list>
#include <vector>
#include <map> // future find better implementation
#include <array>
#include <mutex>

#include <tinyxml2.h>

#include "Engine/SDLUtilityTool.h"

// the various component containers
#include "States/GamePlayState/Entities/SystemsComponents.h"
#include "States/GamePlayState/Entities/StatusComponents.h"
#include "States/GamePlayState/Entities/HealthComponents.h"
#include "States/GamePlayState/Entities/AIComponents.h"
#include "States/GamePlayState/Entities/ActionComponents.h"
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

			//class EntityContactListner;
			class EntityLoader;
			class StatusComponents;

			enum ComponentMask
			{
				STATUS,
				HEALTH,
				TARGET,
				ACTION,
				MOVEMENT,
				RENDER,
				PHYSICS
			};




			class EntityQuery final : public b2QueryCallback
			{
			public:

				virtual bool ReportFixture(b2Fixture* fixture);

				std::unordered_set<EntityDynamicIDType> * m_querySet{ nullptr };
			};

			class EntityMemory final
			{
			public:

				EntityMemory(Engine::SDLUtilityTool& sdlUtilityTool, SDL_Window* m_window);
				~EntityMemory();

				EntityDynamicIDType OverrideMainEntity(EntityDynamicIDType entityID);

				// Queries the b2 world with the AABB and returns a list of the entities
				void QueryEntityWorld(std::unordered_set<EntityDynamicIDType>& entitySet, b2AABB boundingArea);

				void UpdateEntityWorld(float time);

				//int GetWindowWidth();
				//int GetWindowHeight();
				int GetMainEntityDynamicID();

				int GetStaticID();

				SystemsComponents m_systemsComponents{ *this };
				StatusComponents m_statusComponents{ *this };
				HealthComponents m_healthComponents{ *this };
				AIComponents m_AIComponents{ *this };
				ActionComponents m_actionComponents{ *this };
				MovementComponents m_movementComponents{ *this };
				RenderComponents m_renderComponents{ *this };
				PhysicsComponents m_physicsComponents{ *this };

			private:

				class EntityContactListener : public b2ContactListener
				{
				public:

					EntityContactListener(EntityMemory& entityMemory);

				private:
					void BeginContact(b2Contact* contact);

					void EndContact(b2Contact* contact);

					EntityMemory& m_entityMemory;

				};

				friend class EntityLoader;

				Engine::SDLUtilityTool& m_sdlUtilityTool;
				int m_windowWidth{ 0 };
				int m_windowHeight{ 0 };
				int m_mainEntityDynamicID{ -1 };
				int m_freeStaticEntityID{ 0 };

				std::mutex m_lock; // for static IDs

				b2World m_entityWorld{ b2Vec2_zero };
				EntityContactListener m_entityContactListener{ *this };

				// internally management system
				std::list<EntityDynamicIDType> m_freeEntities;
				std::list<EntityDynamicIDType> m_usedEntities;

				std::map<std::string, EntityStaticIDType> m_staticEntityMap;
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

