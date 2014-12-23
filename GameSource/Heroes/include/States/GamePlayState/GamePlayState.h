# pragma once

#include <list>

#include "Engine/State.h"
#include "Engine/SDLUtilityTool.h"

#include "States/GamePlayState/Camera.h"
#include "States/GamePlayState/TileMap.h"
#include "States/GamePlayState/Entities/EntityLoader.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			Engine::State* CreateGamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData);

			enum GamePlayConstants
			{
				AXIS_EPSILON = 10000
			};



			class GamePlayState final : public Engine::State
			{
			public:

				GamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData);
				virtual ~GamePlayState();

				virtual void Update(uint32_t milliTime);
				virtual void Render();

			private:

				void QuerySimulationZone(std::unordered_set<EntityDynamicIDType>& entitySet);
				void QueryVisionZone(std::unordered_set<EntityDynamicIDType>& entitySet);
				void RenderEntites(std::unordered_set<EntityDynamicIDType> entitySet);

				// temporary point for camera to follow
				b2Vec2 m_simulationPoint{ b2Vec2_zero };

				std::unordered_set<EntityDynamicIDType> m_entitySet;

				
				GamePlay::EntityLoader m_entityLoader{ m_sdlUtilityTool };
				GamePlay::EntityMemory m_entityMemory{ m_sdlUtilityTool, m_sdlWindow };
				GamePlay::Camera m_camera{ m_simulationPoint };
				GamePlay::TileMap m_tileMap{ m_sdlUtilityTool };

				int m_mainEntityID{ -1 };

				// TEMPORARY
				SDL_Texture* m_targetTexture{ nullptr };
				int targetSystemUpdateTime{ 125 };
				int targetSystemLastUpdate{ 0 };

			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes