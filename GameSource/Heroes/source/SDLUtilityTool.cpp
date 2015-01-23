// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#include <sstream>

#include "Engine/Log.h"
#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{

		SDLUtilityTool::SDLUtilityTool()
		{
		}
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
				
				if (success)
				{
					m_initialized = true;
				}
			}

			g_Log_Write_L1(LOG_INITIALIZATION_EVENT, "Initialized SDLUtilityTool");
			return success;
		}

		bool SDLUtilityTool::Destroy()
		{
			bool success = false;

			if (m_initialized)
			{
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

		SDL_GameController* SDLUtilityTool::GameControllerOpen(int controllerNum)
		{
			g_assert(m_initialized);
			SDL_GameController* controller = SDL_GameControllerOpen(controllerNum);
			LogSDLError();
			g_assert(controller != nullptr);
			m_sdlControllers++;
			m_totalResources++;
			return controller;
			
		}

		void SDLUtilityTool::GameControllerClose(SDL_GameController* controller)
		{
			g_assert(m_initialized);
			g_assert(controller != nullptr);
			SDL_GameControllerClose(controller);
			LogSDLError();
			m_sdlControllers--;
			m_totalResources--;
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

		SDL_Thread* SDLUtilityTool::CreateThread(SDL_ThreadFunction threadFunction, const char* name, void* data)
		{
			g_assert(m_initialized);
			g_assert(name != nullptr);
			g_assert(data != nullptr);
			g_assert(m_threadMap.count(name) == 0);
			SDL_Thread* thread = SDL_CreateThread(threadFunction, name, data);
			LogSDLError();
			g_assert(thread != nullptr);
			m_threadMap[name] = thread;
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