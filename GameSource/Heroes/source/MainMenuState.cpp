
#include "Engine/Log.h"
#include "Engine/SDLXbox360Controller.h"

#include "States/MainMenuState/MainMenuState.h"
#include "States/GamePlayState/GamePlayState.h"

namespace Heroes
{
	namespace States
	{
		namespace MainMenu
		{
			const int NUMBER_OF_OPTIONS = 3;
			const char* START_GAME_TEXT = "FIGHT";
			const char* LOAD_GAME_TEXT = "CONTINUE";
			const char* QUIT_GAME_TEXT = "RUN";
			const char* FONTS_FILE = "./Resources/Fonts/Archeologicaps.ttf";
			const int FONT_PT_SIZE = 72;

			Engine::State* CreateMainMenuState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData)
			{
				return new MainMenuState(sdlUtilityTool, stateCreationData);
			}

			MainMenuState::MainMenuState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData) : State(sdlUtilityTool, stateCreationData)
			{
				//open the file 
				TTF_Font* font = m_sdlUtilityTool.CreateFont(FONTS_FILE, FONT_PT_SIZE);
				g_assert(font != nullptr);

				// created normal options
				SDL_Surface* normalSurface = nullptr;

				SDL_Color normalColor;
				normalColor.r = 255;
				normalColor.g = 255;
				normalColor.b = 255;
				normalColor.a = 255;

				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, START_GAME_TEXT, normalColor);
				g_assert(normalSurface != nullptr);
				m_normalOptions[0] = normalSurface;
				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, LOAD_GAME_TEXT, normalColor);
				g_assert(normalSurface != nullptr);
				m_normalOptions[1] = normalSurface;
				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, QUIT_GAME_TEXT, normalColor);
				g_assert(normalSurface != nullptr);
				m_normalOptions[2] = normalSurface;

				SDL_Color highlightedColor;
				highlightedColor.r = 255;
				highlightedColor.g = 0;
				highlightedColor.b = 0;
				highlightedColor.a = 255;

				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, START_GAME_TEXT, highlightedColor);
				g_assert(normalSurface != nullptr);
				m_highlightedOptions[0] = normalSurface;
				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, LOAD_GAME_TEXT, highlightedColor);
				g_assert(normalSurface != nullptr);
				m_highlightedOptions[1] = normalSurface;
				normalSurface = m_sdlUtilityTool.RenderText_Blended(font, QUIT_GAME_TEXT, highlightedColor);
				g_assert(normalSurface != nullptr);
				m_highlightedOptions[2] = normalSurface;

				m_sdlUtilityTool.DestroyFont(font);

				// make sure that the screen shows up correct initially
				UpdateTexture();

				g_Log_Write_L1(LOG_CONSTRUCTION_EVENT, "Created Main Menu State");
			}

			MainMenuState::~MainMenuState()
			{
				// clean up the resources
				for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
				{
					m_sdlUtilityTool.DestroySurface(m_normalOptions[i]);
					m_sdlUtilityTool.DestroySurface(m_highlightedOptions[i]);
				}

				g_Log_Write_L1(LOG_DESTRUCTION_EVENT, "Destroyed Main Menu State");
			}

			void MainMenuState::Update(uint32_t milliTime)
			{

				// read events or windows gets mad
				//SDL_Event sdlEvent;
				//if (SDL_WaitEventTimeout(&sdlEvent, 0)) {}

				// read the buttons and axis
				//Uint8 buttonA = SDL_GameControllerGetButton(m_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A);
				//Uint8 buttonUp = SDL_GameControllerGetButton(m_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP);
				//Uint8 buttonDown = SDL_GameControllerGetButton(m_controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				//Sint16 axis = SDL_GameControllerGetAxis(m_controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
				ButtonState buttonAState = m_sdlUtilityTool.GetInputHandler().GetButton(SDL_CONTROLLER_BUTTON_A);
				ButtonState buttonUpState = m_sdlUtilityTool.GetInputHandler().GetButton(SDL_CONTROLLER_BUTTON_DPAD_UP);
				ButtonState buttonDownState = m_sdlUtilityTool.GetInputHandler().GetButton(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				Sint16 leftAxisY = m_sdlUtilityTool.GetInputHandler().Left_Stick_Y();


				if (buttonAState == ButtonState::BUTTON_PRESSED)
				{
					UpdateNextStatePackage();
				}
				else
				{
					if (leftAxisY > static_cast<Sint16>(Engine::XBOX_360_AXIS::AXIS_EPSILON) || (buttonDownState == ButtonState::BUTTON_PRESSED))
					{
						m_optionDirection = 1;
					}
					else if (leftAxisY < -static_cast<Sint16>(Engine::XBOX_360_AXIS::AXIS_EPSILON) || (buttonUpState == ButtonState::BUTTON_PRESSED))
					{
						m_optionDirection = -1;
					}
					else
					{
						m_optionDirection = 0;
					}
				}

				if (m_optionDirection != 0 && m_lastOptionChange + Option::SELECTION_TIME_MILLI < SDL_GetTicks())
				{
					m_optionIndex = (m_optionIndex + NUMBER_OF_OPTIONS + m_optionDirection) % NUMBER_OF_OPTIONS;
					m_lastOptionChange = SDL_GetTicks();
					UpdateTexture();
				}
			}

			void MainMenuState::UpdateNextStatePackage()
			{
				switch (m_optionIndex)
				{
				case 0:
					SetNextState(Engine::StateCreationPackage(GamePlay::CreateGamePlayState, Engine::StateCreationData(Engine::NoStateCreationData, false)));
					break;
				case 1:
					SetNextState(Engine::StateCreationPackage(CreateMainMenuState, Engine::StateCreationData(Engine::NoStateCreationData, false)));
					break;
				case 2:
					SetNextState(Engine::StateCreationPackage(Engine::CreateEndState, Engine::StateCreationData(Engine::NoStateCreationData, false)));
					break;
				}

				SDL_Delay(500); // temporary delay
			}

			void MainMenuState::UpdateTexture()
			{
				SDL_Rect rect;
				rect.w = m_normalOptions[0]->w;
				rect.h = m_normalOptions[0]->h;
				for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
				{
					rect.x = 200;
					rect.y = 200 + (i * 100);

					if (m_optionIndex == i)
					{
						SDL_BlitSurface(m_highlightedOptions[i], NULL, m_sdlSurface, &rect);
					}
					else
					{
						SDL_BlitSurface(m_normalOptions[i], NULL, m_sdlSurface, &rect);
					}
				}
			}
		} // namespace MainMenu
	} // namespace States
} //namespace Heroes