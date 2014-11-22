#include <SDL_assert.h>

#include "Engine/Log.h"

#include "States/MainMenuState/MainMenuState.h"
#include "States/GamePlayState/GamePlayState.h"

#include <States/GamePlayState/LuaStateLoader.h>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			void printInfo(float x) {
				std::cout << x << std::endl;
			}

			int GetInt()
			{
				return 5;
			}
			
			Engine::State* CreateGamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData)
			{
				return new GamePlayState(sdlUtilityTool, stateCreationData);
			}

			GamePlayState::GamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData) : State(sdlUtilityTool, stateCreationData)
				
			{

				m_tileMap.Load("./Resources/Levels/Maps/TestMap.map", m_sdlWindow, m_sdlRenderer);

				m_entityLoader.LoadEntityFile("./Resources/Entities/Warrior.xml", m_entityMemory, m_sdlRenderer);

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
				// test the luaState here
				LuaStateLoader luaLoader;
				lua_State* luaState = luaLoader.GetGerneralEntityLuaState(m_entityMemory);

				luabind::module(luaState)[
					luabind::def("printInfo", &printInfo),
					luabind::def("GetInt", &GetInt)
				];

				luabind::object f = luabind::globals(luaState); 
				SDL_assert(f.is_valid());
				luabind::object t = f["StatusComponents"];
				SDL_assert(t.is_valid());
				try {
					// Now call our function in a lua script
					luaL_dostring(
						luaState,
						"b = B2Vec2\n"
						"b.x = 6\n"
						//"d = Test\n"
						//"d:SetDeathTimer(5)\n"
						//"b.x = d.m_staticEntityID\n"
						"c = StatusComponents:GetDeathTimer_D(0)\n"
						"printInfo(c)\n"
						"StatusComponents:SetDeathTimer_D(0, 30)\n"

						"c = StatusComponents:GetDeathTimer_D(0)\n"
						//"z = d:GetDeathTimer()\n"
						//"b.x = c\n"
						//"b.y = 5.5\n"
						//"print(4)\n"
						"printInfo(c)\n"
						);
				}
				catch (const std::exception &TheError) {
					std::cout << TheError.what() << std::endl;
				}

				std::cout << m_entityMemory.m_statusComponents.GetDeathTimer_S(0) << std::endl;

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
				m_camera.SetCameraFollow(static_cast<b2Vec2>(m_entityMemory.m_physicsComponents.GetEntityBody_D(m_mainEntityID)->GetPosition()));

				 // list for entities
				m_entityList.clear();
				QuerySimulationZone(m_entityList);

				// Status
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetStatusSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
				}

				// Health
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetHealthSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
				}

				// Target
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetTargetSystem_D(entityID)(entityID, m_entityMemory, m_controller);
				}

				// Action
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetActionSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
				}

				// Direction
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetDirectionSystem_D(entityID)(entityID, m_entityMemory, m_controller);
				}

				// Movement
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_systemsComponents.GetMovementSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
				}

				// Render
				for (auto entityID : m_entityList)
				{
					m_entityMemory.m_renderComponents.UpdateEntityRenderComponent(entityID, m_camera, m_sdlWindow);
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
				// shadows

				// render the textures
				for (auto entityID : entityList)
				{
					SDL_RenderCopyEx(m_sdlRenderer, 
						m_entityMemory.m_renderComponents.GetEntityTexture_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID)),
						NULL, 
						m_entityMemory.m_renderComponents.GetDestinationRect_D(entityID), m_entityMemory.m_renderComponents.GetAngle_D(entityID), 
						NULL, 
						SDL_FLIP_NONE);
				}

				// render the health bars
				for (auto entityID : entityList)
				{
					SDL_RenderCopy(m_sdlRenderer, 
						m_entityMemory.m_renderComponents.GetHealthBarTexture_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID)),
						NULL, 
						m_entityMemory.m_renderComponents.GetHealthBarRect_D(entityID));
				}
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes