#include <SDL_assert.h> 
#include <iostream>

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
				m_mainEntityID = m_entityMemory.LoadMainEntity(m_sdlRenderer);

				int two = m_entityMemory.LoadMainEntity(m_sdlRenderer);
				int three = m_entityMemory.LoadMainEntity(m_sdlRenderer);
			}

			GamePlayState::~GamePlayState()
			{
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
				
				std::list<GamePlay::EntityIDType> entityList;

				

				 // update camera

				 // list for entities
				m_entityList.clear();
				QuerySimulationZone(m_entityList);
				

				// RUN THE SYSYTEMS
				m_entityMemory.m_systemComponents[m_mainEntityID].m_directionSystem(m_mainEntityID, m_entityMemory, m_controller);
				//m_entityMemory.m_systemComponents[m_mainEntityID].m_movementSystem(m_mainEntityID, m_entityMemory, nullptr);

				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemComponents[entityID].m_movementSystem(entityID, m_entityMemory, nullptr);
					m_entityMemory.m_systemComponents[entityID].m_renderUpdateSystem(entityID, m_entityMemory, nullptr);
					//m_entityMemory.m_systemComponents[entityID].m_directionSystem(entityID, m_entityMemory, m_controller);
					
				}

				m_entityMemory.UpdateEntityWorld(0.030f);
				m_camera.SetCameraFollow(static_cast<b2Vec2>(m_entityMemory.m_physicsComponents[m_mainEntityID].body->GetPosition()));
				// direction for main entity only
				
			}

			void GamePlayState::QuerySimulationZone(std::list<EntityIDType>& entityList)
			{
				b2AABB activeSimulationRegion;
				m_camera.GetActiveZone(activeSimulationRegion); // get active region
				m_entityMemory.QueryEntityWorld(entityList, activeSimulationRegion); // get entities in active region
			}

			void GamePlayState::QueryVisionZone(std::list<EntityIDType>& entityList)
			{
				b2AABB visibleSimulationRegion;
				m_camera.GetVisionZone(visibleSimulationRegion, m_sdlWindow); // get visible region
				m_entityMemory.QueryEntityWorld(entityList, visibleSimulationRegion); // get entities in visible region
			}

			void GamePlayState::RenderEntites(std::list<EntityIDType> entityList)
			{
				// this could be cleaner
				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(m_sdlWindow, &displayMode);
				SDL_Rect relativeEntity;

				b2Vec2 location = m_entityMemory.m_physicsComponents[m_mainEntityID].body->GetPosition();
				
				for (auto entityID : entityList)
				{
					
					// this should be done in the render update
					relativeEntity = m_entityMemory.m_renderComponents[entityID].m_dstRect;
					relativeEntity.x = relativeEntity.x - (location.x * PIXEL_TO_METER) + displayMode.w / 2;
					relativeEntity.y = relativeEntity.y - (location.y * PIXEL_TO_METER) + displayMode.h / 2;

					float angle = m_entityMemory.m_renderComponents[entityID].m_angle;
					SDL_RenderCopyEx(m_sdlRenderer, m_entityMemory.m_renderComponents[entityID].m_texture, NULL, &relativeEntity, angle, NULL, SDL_FLIP_NONE);		
				}
			}

			float GamePlayState::GetRotationAngle(b2Vec2& rotationVector)
			{
				//float tanAngle = atan2f(rotationVector.x)
				return 0.0f;
			}

			void GamePlayState::Render()
			{
				m_entityList.clear();
				QueryVisionZone(m_entityList);

				SDL_RenderClear(m_sdlRenderer);

				ClearSurface();
				m_tileMap.Render(m_camera.GetSimCenter(), m_sdlRenderer);
				RenderEntites(m_entityList);

				SDL_RenderPresent(m_sdlRenderer);
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes