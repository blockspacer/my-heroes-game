#include <SDL_assert.h>

#include "Engine/Log.h"

#include "States/MainMenuState/MainMenuState.h"
#include "States/GamePlayState/GamePlayState.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			
			Engine::State* CreateGamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData)
			{
				return new GamePlayState(sdlUtilityTool, stateCreationData);
			}

			GamePlayState::GamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData) : State(sdlUtilityTool, stateCreationData)
				
			{
				m_tileMap.Load("./Resources/Levels/Maps/TestMap.map", m_sdlWindow, m_sdlRenderer);

				m_entityMemory.LoadStaticWarriorFile(nullptr, m_sdlRenderer);

				EntityDynamicIDType one = m_entityMemory.LoadDynamicWarrior(b2Vec2_zero, b2Vec2_zero);
				m_entityMemory.LoadDynamicWarrior(b2Vec2(1, 1), b2Vec2_zero);
				m_entityMemory.LoadDynamicWarrior(b2Vec2(2, 2), b2Vec2_zero);

				m_mainEntityID = m_entityMemory.OverrideMainEntity(one);

				g_Log_Write_L1(LOG_CONSTRUCTION_EVENT, "Created Game Play State");
			}

			GamePlayState::~GamePlayState()
			{
				g_Log_Write_L1(LOG_DESTRUCTION_EVENT, "Destroyed Game Play State");
			}

			void GamePlayState::Update(uint32_t milliTime)
			{
				SDL_Event sdlEvent;
				if (SDL_WaitEventTimeout(&sdlEvent, 0)) {}

				// read the buttons and axis
				Uint8 buttonBack = SDL_GameControllerGetButton(m_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK);

				if (buttonBack)
				{
					SetNextState(Engine::StateCreationPackage(MainMenu::CreateMainMenuState, Engine::StateCreationData(Engine::NoStateCreationData, false)));
				}

				// List of things to do in update

				// 1) Get the list of active entities from camera
				// 2) Run the Systems
				//    i) Run Death System (contained)
				//    ii) Run Target System (not contained)
				//    iii) Run Action System (not contained)
				//    iv) Run Health System (contained)
				//    v) Run Direction System (not contained)
				//    vi) Run Movement System (not contained)

				// Notes camera should be attached
				// list of active entiites should be local
				// threading does not affect this scheme
				
				std::list<GamePlay::EntityDynamicIDType> entityList;

				

				 // update camera
				m_entityMemory.UpdateEntityWorld(0.030f);
				m_camera.SetCameraFollow(static_cast<b2Vec2>(m_entityMemory.m_dynamicPhysicsComponents[m_mainEntityID].body->GetPosition()));

				 // list for entities
				m_entityList.clear();
				QuerySimulationZone(m_entityList);
				

				//// RUN THE SYSYTEMS
				//m_entityMemory.m_dynamicSystemComponents[m_mainEntityID].m_directionSystem(m_mainEntityID, m_entityMemory, m_controller);
				////m_entityMemory.m_systemComponents[m_mainEntityID].m_movementSystem(m_mainEntityID, m_entityMemory, nullptr);

				//for (auto entityID : m_entityList)
				//{
				//	m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_movementSystem(entityID, m_entityMemory, nullptr);
				//	m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_renderUpdateSystem(entityID, m_entityMemory, nullptr);
				//	//m_entityMemory.m_systemComponents[entityID].m_directionSystem(entityID, m_entityMemory, m_controller);
				//	
				//}

				// Status
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_statusSystem(entityID, m_entityMemory, nullptr);
				}

				// Health
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_healthSystem(entityID, m_entityMemory, nullptr);
				}

				// Target
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_dynamicSystemComponents[entityID].m_targetSystem(entityID, m_entityMemory, m_controller);
				}

				// Action
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_actionSystem(entityID, m_entityMemory, nullptr);
				}

				// Direction
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_dynamicSystemComponents[entityID].m_directionSystem(entityID, m_entityMemory, m_controller);
				}

				// Movement
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_movementSystem(entityID, m_entityMemory, nullptr);
				}

				// Render
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_staticSystemComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_renderUpdateSystem(entityID, m_entityMemory, nullptr);
				}
				
			}

			void GamePlayState::QuerySimulationZone(std::list<EntityDynamicIDType>& entityList)
			{
				b2AABB activeSimulationRegion;
				m_camera.GetActiveZone(activeSimulationRegion); // get active region
				m_entityMemory.QueryEntityWorld(entityList, activeSimulationRegion); // get entities in active region
			}

			void GamePlayState::QueryVisionZone(std::list<EntityDynamicIDType>& entityList)
			{
				b2AABB visibleSimulationRegion;
				m_camera.GetVisionZone(visibleSimulationRegion, m_sdlWindow); // get visible region
				m_entityMemory.QueryEntityWorld(entityList, visibleSimulationRegion); // get entities in visible region
			}

			void GamePlayState::Render()
			{
				// get the entities
				m_entityList.clear();
				QueryVisionZone(m_entityList);

				// render the game
				SDL_RenderClear(m_sdlRenderer);

				ClearSurface();
				m_tileMap.Render(m_camera.GetSimCenter(), m_sdlRenderer);
				RenderEntites(m_entityList);

				SDL_RenderPresent(m_sdlRenderer);
			}

			void GamePlayState::RenderEntites(std::list<EntityDynamicIDType> entityList)
			{
				// render the textures
				for (auto entityID : entityList)
				{
					SDL_RenderCopyEx(m_sdlRenderer, m_entityMemory.m_staticRenderComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_entityTexture, NULL, &m_entityMemory.m_dynamicRenderComponents[entityID].m_dstRect, m_entityMemory.m_dynamicRenderComponents[entityID].m_angle, NULL, SDL_FLIP_NONE);
				}

				// render the health bars
				for (auto entityID : entityList)
				{
					SDL_RenderCopy(m_sdlRenderer, m_entityMemory.m_staticRenderComponents[m_entityMemory.m_dynamicStatusComponents[entityID].m_staticEntityID].m_lifeBarTexture, NULL, &m_entityMemory.m_dynamicRenderComponents[entityID].m_healthBarRect);
				}
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes