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
			
			Engine::State* CreateGamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData)
			{
				return new GamePlayState(sdlUtilityTool, stateCreationData);
			}

			GamePlayState::GamePlayState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData) : State(sdlUtilityTool, stateCreationData)
				
			{

				

				m_tileMap.Load("./Resources/Levels/Maps/TestMap.map", m_sdlWindow, m_sdlRenderer);

				std::string warrior = m_entityLoader.LoadEntityFile("./Resources/Entities/Warrior.xml", m_entityMemory, m_sdlRenderer);
				std::string testEntity = m_entityLoader.LoadEntityFile("./Resources/Entities/TestEntity.xml", m_entityMemory, m_sdlRenderer);
				std::string rock = m_entityLoader.LoadEntityFile("./Resources/Entities/Rock.xml", m_entityMemory, m_sdlRenderer);

				b2Vec2 warriorOrientation;
				warriorOrientation.x = -1;
				warriorOrientation.y = 0;
				EntityDynamicIDType one = m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(7, 7), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 5), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 7), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 9), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 5), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 7), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 9), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 5), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 7), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 9), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 5), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 7), warriorOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(warrior, b2Vec2(5, 9), warriorOrientation, m_entityMemory);

				b2Vec2 testEntityOrientation;
				testEntityOrientation.x = 1;
				testEntityOrientation.y = 0;
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(11, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 5), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 9), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(11, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 5), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 9), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(11, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 5), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 9), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(11, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 5), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 7), testEntityOrientation, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(testEntity, b2Vec2(13, 9), testEntityOrientation, m_entityMemory);

				m_entityLoader.LoadDynamicEntity(rock, b2Vec2(9, 4), b2Vec2_zero, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(rock, b2Vec2(10, 11), b2Vec2_zero, m_entityMemory);
				m_entityLoader.LoadDynamicEntity(rock, b2Vec2(6, 6), b2Vec2_zero, m_entityMemory);

				m_mainEntityID = m_entityMemory.OverrideMainEntity(one);

				m_targetTexture = m_sdlUtilityTool.LoadImageTexture("./Resources/Textures/Target.png", m_sdlRenderer);

				g_Log_Write_L1(LOG_CONSTRUCTION_EVENT, "Created Game Play State");
			}

			GamePlayState::~GamePlayState()
			{
				m_sdlUtilityTool.DestroyTexture(m_targetTexture); // temporary
				g_Log_Write_L1(LOG_DESTRUCTION_EVENT, "Destroyed Game Play State");
			}

			void GamePlayState::Update(uint32_t milliTime)
			{
				// test the luaState here
				//LuaStateLoader luaLoader;
				//lua_State* luaState = luaLoader.GetGerneralEntityLuaState(m_entityMemory);

				//luabind::module(luaState)[
				//	luabind::def("printInfo", &printInfo),
				//	luabind::def("GetInt", &GetInt)
				//];

				//luabind::object f = luabind::globals(luaState); 
				//g_assert(f.is_valid());
				//luabind::object t = f["StatusComponents"];
				//g_assert(t.is_valid());
				//try {
				//	// Now call our function in a lua script
				//	luaL_dostring(
				//		luaState,
				//		"b = B2Vec2\n"
				//		"b.x = 6\n"
				//		//"d = Test\n"
				//		//"d:SetDeathTimer(5)\n"
				//		//"b.x = d.m_staticEntityID\n"
				//		"c = StatusComponents:GetDeathTimer_D(0)\n"
				//		"printInfo(c)\n"
				//		"StatusComponents:SetDeathTimer_D(0, 30)\n"

				//		"c = StatusComponents:GetDeathTimer_D(0)\n"
				//		//"z = d:GetDeathTimer()\n"
				//		//"b.x = c\n"
				//		//"b.y = 5.5\n"
				//		//"print(4)\n"
				//		"printInfo(c)\n"
				//		);
				//}
				//catch (const std::exception &TheError) {
				//	std::cout << TheError.what() << std::endl;
				//}

				//std::cout << m_entityMemory.m_statusComponents.GetDeathTimer_S(0) << std::endl;

				//SDL_Event sdlEvent;
				//if (SDL_WaitEventTimeout(&sdlEvent, 0)) {}

				ButtonState state = m_sdlUtilityTool.GetInputHandler().GetButton(SDL_CONTROLLER_BUTTON_BACK);

				// read the buttons and axis
				//Uint8 buttonBack = SDL_GameControllerGetButton(m_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK);

				if (state == ButtonState::BUTTON_PRESSED)
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
				
				std::unordered_set<GamePlay::EntityDynamicIDType> entityList;

				 // update camera
				m_entityMemory.UpdateEntityWorld(0.030f);
				m_camera.SetCameraFollow(static_cast<b2Vec2>(m_entityMemory.m_physicsComponents.GetEntityBody_D(m_mainEntityID)->GetPosition()));

				 // list for entities
				m_entitySet.clear();
				QuerySimulationZone(m_entitySet);

				// Status
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::ACTOR ||
						m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::EFFECT)
					{
						m_entityMemory.m_statusComponents.UpdateEntityStatusComponent_D(entityID);
					}
					
				}

				// Health
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::ACTOR ||
						m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::EFFECT)
					{
						m_entityMemory.m_systemsComponents.GetHealthSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
					}
				}

				// AI
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::ACTOR ||
						m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::EFFECT)
					{
						if (m_entityMemory.m_statusComponents.GetBusyStatus_D(entityID) == BusyStatusType::NONE)
						{
							m_entityMemory.m_systemsComponents.GetAISystem_D(entityID)(entityID, m_entityMemory, m_sdlUtilityTool.GetInputHandler());
						}
					}
				}
				

				// Action
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::ACTOR ||
						m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::EFFECT)
					{
						if (m_entityMemory.m_statusComponents.GetBusyStatus_D(entityID) != BusyStatusType::NONE)
						{
							// no death ai
							m_entityMemory.m_systemsComponents.GetActionSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);

							if (m_entityMemory.m_statusComponents.GetBusyStatus_D(entityID) == BusyStatusType::BASIC_ATTACK)
							{
								// remove the velocity of entity for basic attacks
								m_entityMemory.m_physicsComponents.GetEntityBody_D(entityID)->SetLinearVelocity(b2Vec2_zero);
							}
						}
					}
				}

				// Movement
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::ACTOR ||
						m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::EFFECT)
					{
						if (m_entityMemory.m_statusComponents.GetBusyStatus_D(entityID) == BusyStatusType::NONE)
						{
							m_entityMemory.m_systemsComponents.GetMovementSystem_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID))(entityID, m_entityMemory);
						}
						
					}
				}

				// Render
				for (auto entityID : m_entitySet)
				{
					m_entityMemory.m_renderComponents.UpdateEntityRenderComponent(entityID, m_camera, m_sdlWindow);
				}

				// Cleanup
				for (auto entityID : m_entitySet)
				{
					if (m_entityMemory.m_statusComponents.GetActiveStatus_D(entityID) == ActiveStatusType::TOMBSTONE)
					{
						m_entityLoader.UnloadDynamicEntity(entityID, m_entityMemory);
					}
				}
				
			}

			void GamePlayState::QuerySimulationZone(std::unordered_set<EntityDynamicIDType>& entitySet)
			{
				b2AABB activeSimulationRegion;
				m_camera.GetActiveZone(activeSimulationRegion); // get active region
				m_entityMemory.QueryEntityWorld(entitySet, activeSimulationRegion); // get entities in active region
			}

			void GamePlayState::QueryVisionZone(std::unordered_set<EntityDynamicIDType>& entitySet)
			{
				b2AABB visibleSimulationRegion;
				m_camera.GetVisionZone(visibleSimulationRegion, m_sdlWindow); // get visible region
				m_entityMemory.QueryEntityWorld(entitySet, visibleSimulationRegion); // get entities in visible region
			}

			void GamePlayState::Render()
			{
				// get the entities
				m_entitySet.clear();
				QueryVisionZone(m_entitySet);

				// render the game
				SDL_RenderClear(m_sdlRenderer);

				ClearSurface();
				m_tileMap.Render(m_camera.GetSimCenter(), m_sdlRenderer);
				m_entitySet.clear();
				QuerySimulationZone(m_entitySet);
				RenderEntites(m_entitySet);

				SDL_RenderPresent(m_sdlRenderer);
			}

			void GamePlayState::RenderEntites(std::unordered_set<EntityDynamicIDType> entitySet)
			{
				// shadows
				int mainEntityTarget = m_entityMemory.m_AIComponents.GetTarget_D(m_mainEntityID, m_entityMemory);

				// render the textures
				for (auto entityID : entitySet)
				{
					

					SDL_RenderCopyEx(m_sdlRenderer, 
						m_entityMemory.m_renderComponents.GetAnimationTexture_D(entityID),
						m_entityMemory.m_renderComponents.GetSourceRect_D(entityID), 
						m_entityMemory.m_renderComponents.GetDestinationRect_D(entityID), m_entityMemory.m_renderComponents.GetAngle_D(entityID),
						NULL, 
						SDL_FLIP_NONE);

					if (entityID == mainEntityTarget)
					{
						SDL_RenderCopy(m_sdlRenderer, m_targetTexture, NULL, m_entityMemory.m_renderComponents.GetDestinationRect_D(entityID));
					}
				}

				// render the Status TODO
				for (auto entityID : entitySet)
				{
					SDL_RenderCopy(m_sdlRenderer, 
						m_entityMemory.m_renderComponents.GetStatusTexture_S(m_entityMemory.m_statusComponents.GetStaticEntityID_D(entityID)),
						NULL, 
						m_entityMemory.m_renderComponents.GetStatusRect_D(entityID));
				}
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes