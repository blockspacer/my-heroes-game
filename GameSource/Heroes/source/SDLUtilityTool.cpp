// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#include <sstream>
#include <iostream> // temporary

#include "Engine/Log.h"
#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{

		int ProcessInputFunctionXboxController(void* inputHandler)
		{
			InputHandler* input = (InputHandler*)inputHandler;

			SDL_Event sdlEvent;

			while (input->IsActive())
			{
				// proccess an event

				if (SDL_PollEvent(&sdlEvent))
				{
					switch (sdlEvent.type)
					{
					case SDL_KEYDOWN:
						/* handle keyboard stuff here */
						break;

					case SDL_QUIT:
						/* Set whatever flags are necessary to */
						/* end the main game loop here */
						break;
					case SDL_CONTROLLERBUTTONDOWN:
						
						switch (sdlEvent.cbutton.button)
						{
						// Start, Back
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START:
							input->SetButton(SDL_CONTROLLER_BUTTON_START, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK:
							input->SetButton(SDL_CONTROLLER_BUTTON_BACK, ButtonState::BUTTON_HELD);
							break;
						// A,B,X,y
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
							input->SetButton(SDL_CONTROLLER_BUTTON_A, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B:
							input->SetButton(SDL_CONTROLLER_BUTTON_B, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:
							input->SetButton(SDL_CONTROLLER_BUTTON_X, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y:
							input->SetButton(SDL_CONTROLLER_BUTTON_Y, ButtonState::BUTTON_HELD);
							break;
						// D - Pad
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_UP, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_DOWN, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_LEFT, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, ButtonState::BUTTON_HELD);
							break;
						// Bumbers
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
							input->SetButton(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, ButtonState::BUTTON_HELD);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
							input->SetButton(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, ButtonState::BUTTON_HELD);
							break;
						default:
							g_assert(false);
							break;
						}
						break;
					case SDL_CONTROLLERBUTTONUP:

						switch (sdlEvent.cbutton.button)
						{
							// Start, Back
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START:
							input->SetButton(SDL_CONTROLLER_BUTTON_START, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK:
							input->SetButton(SDL_CONTROLLER_BUTTON_BACK, ButtonState::BUTTON_PRESSED);
							break;
							// A,B,X,y
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:
							input->SetButton(SDL_CONTROLLER_BUTTON_A, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B:
							input->SetButton(SDL_CONTROLLER_BUTTON_B, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:
							input->SetButton(SDL_CONTROLLER_BUTTON_X, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y:
							input->SetButton(SDL_CONTROLLER_BUTTON_Y, ButtonState::BUTTON_PRESSED);
							break;
							// D - Pad
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_UP, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_DOWN, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_LEFT, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
							input->SetButton(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, ButtonState::BUTTON_PRESSED);
							break;
							// Bumbers
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
							input->SetButton(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, ButtonState::BUTTON_PRESSED);
							break;
						case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
							input->SetButton(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, ButtonState::BUTTON_PRESSED);
							break;
						default:
							g_assert(false);
							break;
						}
						break;
					}
				}

			}

			return 0;
		}

		// Very dangerous operation to type cast a pointer to create reference
		SDLUtilityTool::SDLUtilityTool() {}

		SDLUtilityTool::~SDLUtilityTool() {}

		bool SDLUtilityTool::Init()
		{
			bool success = true;
			if (!m_initialized)
			{
				success = success & (IMG_Init(SDL_IMG_INIT_FLAGS) == SDL_IMG_INIT_FLAGS);
				LogSDLError();
				success = success & (TTF_Init() == 0);
				LogTTFError();
				success = success & (SDL_Init(SDL_INIT_FLAGS) == 0);
				LogIMGError();
				success = success & InitInputHandler();
				
				if (success)
				{
					m_initialized = true;
				}
			}

			g_Log_Write_L1(LOG_INITIALIZATION_EVENT, "Initialized SDLUtilityTool");
			return success;
		}

		bool SDLUtilityTool::InitInputHandler()
		{
			// create the game controller and give the InputHandler a copy
			g_assert(SDL_NumJoysticks() != 0);
			g_assert(SDL_IsGameController(0));
			m_inputController = SDL_GameControllerOpen(0);
			LogSDLError();
			g_assert(m_inputController != nullptr);
			m_inputHandler.m_gameController = m_inputController;
			g_assert(m_inputHandler.m_gameController != nullptr);

			// sets the flag that the input thread watches to true
			m_inputHandler.Activate();

			// create the input thread
			m_inputThread = SDL_CreateThread(ProcessInputFunctionXboxController, "InputThread", &m_inputHandler);
			LogSDLError();
			g_assert(m_inputThread != nullptr);

			

			// any failure here is critical
			return true;
		}

		void SDLUtilityTool::DestroyInputHandler()
		{
			int returnValue = 0;

			// wait on the thread
			g_assert(m_inputHandler.IsActive());
			m_inputHandler.Deactivate();
			g_assert(m_inputThread != nullptr);
			SDL_WaitThread(m_inputThread, &returnValue);
			LogSDLError();
			

			// cleanup the game controller
			g_assert(m_inputController != nullptr);
			SDL_GameControllerClose(m_inputController);
			LogSDLError();
			m_inputController = nullptr;
			m_inputHandler.m_gameController = nullptr;
			
		}

		bool SDLUtilityTool::Destroy()
		{
			bool success = false;

			if (m_initialized)
			{
				// destroy input handler, controller and thread
				// TODO
				DestroyInputHandler();

				// then quit sdl
				SDL_Quit();

				
				m_initialized = false;
				success = true;
			}

			g_Log_Write_L1(LOG_UNINITIALIZATION_EVENT, "Destroyed SDLUtilityTool");
			return success;
		}

		void SDLUtilityTool::LogSDLError()
		{
			m_sdlErrorString = SDL_GetError();
			if (m_sdlErrorString.compare("") != 0)
			{
				g_Log_Write_L2(LOG_SDL_ERROR, m_sdlErrorString.c_str());
				m_sdlErrorString.clear();
			}
		}

		void SDLUtilityTool::LogTTFError()
		{
			m_sdlErrorString = TTF_GetError();
			if (m_sdlErrorString.compare("") != 0)
			{
				g_Log_Write_L2(LOG_SDL_TTF_ERROR, m_sdlErrorString.c_str());
				m_sdlErrorString.clear();
			}
		}

		void SDLUtilityTool::LogIMGError()
		{
			m_sdlErrorString = IMG_GetError();
			if (m_sdlErrorString.compare("") != 0)
			{
				g_Log_Write_L2(LOG_SDL_IMG_ERROR, m_sdlErrorString.c_str());
				m_sdlErrorString.clear();
			}
		}

		/*
		 * All the methods are fairly similar. They check the parameters and the
		 * make the calls to the SDL functions and return the resource. They also
		 * are responsible for maintaining the resource count of each resource type.
		 */

		SDL_Window* SDLUtilityTool::CreateWindow(const char *title,
												 int x, int y, int w,
												 int h, uint32_t flags)
		{
			g_assert(m_initialized);
			SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
			LogSDLError();
			g_assert(window != nullptr);
			m_sdlWindows++;
			m_totalResources++;
			return window;
		}

		void SDLUtilityTool::DestroyWindow(SDL_Window* window)
		{
			g_assert(m_initialized);
			g_assert(window != nullptr);
			SDL_DestroyWindow(window);
			LogSDLError();
			m_sdlWindows--;
			m_totalResources--;
		}

		SDL_Renderer* SDLUtilityTool::CreateRenderer(SDL_Window * window,
													 int index, Uint32 flags)
		{
			g_assert(m_initialized);
			SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
			LogSDLError();
			g_assert(renderer != nullptr);
			m_sdlRenderers++;
			m_totalResources++;
			return renderer;
		}

		void SDLUtilityTool::DestroyRenderer(SDL_Renderer * renderer)
		{
			g_assert(m_initialized);
			g_assert(renderer != nullptr);
			SDL_DestroyRenderer(renderer);
			LogSDLError();
			m_sdlRenderers--;
			m_totalResources--;
		}

		SDL_Surface* SDLUtilityTool::CreateRGBSurface
			(Uint32 flags, int width, int height, int depth)
		{
			g_assert(m_initialized);
			SDL_Surface* surface = SDL_CreateRGBSurface
				(flags, width, height, depth,
				0x00FF0000,
				0x0000FF00,
				0x000000FF,
				0xFF000000);
			LogSDLError();
			g_assert(surface != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return surface;
		}
		void SDLUtilityTool::DestroySurface(SDL_Surface* surface)
		{
			g_assert(m_initialized);
			g_assert(surface != nullptr);
			SDL_FreeSurface(surface);
			LogSDLError();
			m_sdlSurfaces--;
			m_totalResources--;
		}

		SDL_Texture* SDLUtilityTool::CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface)
		{
			g_assert(m_initialized);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			LogSDLError();
			g_assert(texture != nullptr);
			m_sdlTextures++;
			m_totalResources++;
			return texture;
		}

		void SDLUtilityTool::DestroyTexture(SDL_Texture* texture)
		{
			g_assert(m_initialized);
			g_assert(texture != nullptr);
			SDL_DestroyTexture(texture);
			LogSDLError();
			m_sdlTextures--;
			m_totalResources--;
		}

		TTF_Font* SDLUtilityTool::CreateFont(const char *file, int ptsize)
		{
			g_assert(m_initialized);
			TTF_Font* font = TTF_OpenFont(file, ptsize);
			LogTTFError();
			g_assert(font != nullptr);
			m_sdlFonts++;
			m_totalResources++;
			return font;
		}

		void SDLUtilityTool::DestroyFont(TTF_Font* font)
		{
			g_assert(m_initialized);
			g_assert(font != nullptr);
			TTF_CloseFont(font);
			LogTTFError();
			m_sdlFonts--;
			m_totalResources--;
		}

		SDL_Surface* SDLUtilityTool::RenderText_Blended(TTF_Font *font,
			const char *text, SDL_Color fg)
		{
			g_assert(m_initialized);
			SDL_Surface* surface = TTF_RenderText_Blended(font, text, fg);
			LogTTFError();
			g_assert(surface != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return surface;
		}

		SDL_Surface* SDLUtilityTool::LoadImageSurface(const char* file)
		{
			g_assert(m_initialized);
			SDL_Surface* image = IMG_Load(file);
			LogIMGError();
			g_assert(image != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return image;
		}

		SDL_Texture* SDLUtilityTool::LoadImageTexture(const char* file, SDL_Renderer* renderer)
		{
			g_assert(m_initialized);
			SDL_Surface* imageSurface = LoadImageSurface(file);
			g_assert(imageSurface != nullptr);
			SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
			LogSDLError();
			g_assert(imageTexture != nullptr);
			DestroySurface(imageSurface);
			LogSDLError();
			m_sdlTextures++;
			m_totalResources++;
			return imageTexture;
		}

		SDL_Thread* SDLUtilityTool::CreateThread(SDL_ThreadFunction threadFunction, const char* threadName, void* data)
		{
			g_assert(m_initialized);
			g_assert(threadName != nullptr);
			g_assert(data != nullptr);
			g_assert(m_threadMap.count(threadName) == 0);
			SDL_Thread* thread = SDL_CreateThread(threadFunction, threadName, data);
			LogSDLError();
			g_assert(thread != nullptr);
			m_threadMap[threadName] = thread;
			m_sdlThreads++;
			m_totalResources++;
			return thread;
		}

		void SDLUtilityTool::WaitThread(SDL_Thread* thread, int* returnValue)
		{
			g_assert(thread != nullptr);
			g_assert(returnValue != nullptr);
			m_threadMap.erase(SDL_GetThreadName(thread));
			LogSDLError();
			SDL_WaitThread(thread, returnValue);
			LogSDLError();
			m_sdlThreads--;
			m_totalResources--;
		}

		void SDLUtilityTool::WaitThread(const char* threadName, int* returnValue)
		{
			g_assert(threadName != nullptr);
			g_assert(returnValue != nullptr);
			g_assert(m_threadMap.count(threadName) == 1);
			SDL_Thread* thread = m_threadMap[threadName];
			m_threadMap.erase(threadName);
			SDL_WaitThread(thread, returnValue);
			LogSDLError();
			m_sdlThreads--;
			m_totalResources--;
		}

		InputHandler& SDLUtilityTool::GetInputHandler()
		{
			return m_inputHandler;
		}

		std::string SDLUtilityTool::StatusString()
		{
			std::string status;
			std::stringstream stringCreator;
			if (m_totalResources > 0)
			{
				stringCreator << "Resources are not cleaned up.\n\r";

				// windows
				stringCreator << "Windows: ";
				stringCreator << m_sdlWindows;
				stringCreator << "\n\r";

				// renderers
				stringCreator << "Renderers: ";
				stringCreator << m_sdlRenderers;
				stringCreator << "\n\r";

				// surfaces
				stringCreator << "Surfaces: ";
				stringCreator << m_sdlSurfaces;
				stringCreator << "\n\r";

				// textures
				stringCreator << "Textures: ";
				stringCreator << m_sdlTextures;
				stringCreator << "\n\r";

				// threads
				stringCreator << "Threads: ";
				stringCreator << m_sdlThreads;
				stringCreator << "\n\r";

				// textures
				stringCreator << "Controllers: ";
				stringCreator << m_sdlControllers;
				stringCreator << "\n\r";

				// fonts
				stringCreator << "Fonts: ";
				stringCreator << m_sdlFonts;
				stringCreator << "\n\r";

			}
			else if (m_totalResources == 0)
			{
				status.append("No Resources.\n\r");
			}
			else
			{
				status.append("Problem with Resource Management number of resources is negative ");
				stringCreator << m_totalResources;
				stringCreator << "\n\r";
			}

			status.append(stringCreator.str());
			return status;
		}

	} // namespace Graphics
} // namespace Heroes