#include <SDL_assert.h>
#include <iostream>

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
				success = success & (SDL_Init(SDL_INIT_FLAGS) == 0);
				success = success & (TTF_Init() == 0);

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

		SDL_Window* SDLUtilityTool::CreateWindow(const char *title,
												 int x, int y, int w,
												 int h, uint32_t flags)
		{
			SDL_assert(m_initialized);
			SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
			SDL_assert(window != nullptr);
			m_sdlWindows++;
			m_totalResources++;
			return window;
		}

		void SDLUtilityTool::DestroyWindow(SDL_Window* window)
		{
			SDL_assert(m_initialized);
			SDL_assert(window != nullptr);
			SDL_DestroyWindow(window);
			m_sdlWindows--;
			m_totalResources--;
		}

		SDL_Renderer* SDLUtilityTool::CreateRenderer(SDL_Window * window,
													 int index, Uint32 flags)
		{
			SDL_assert(m_initialized);
			SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
			SDL_assert(renderer != nullptr);
			m_sdlRenderers++;
			m_totalResources++;
			return renderer;
		}

		void SDLUtilityTool::DestroyRenderer(SDL_Renderer * renderer)
		{
			SDL_assert(m_initialized);
			SDL_assert(renderer != nullptr);
			SDL_DestroyRenderer(renderer);
			m_sdlRenderers--;
			m_totalResources--;
		}

		SDL_Surface* SDLUtilityTool::CreateRGBSurface
			(Uint32 flags, int width, int height, int depth)
		{
			SDL_assert(m_initialized);
			SDL_Surface* surface = SDL_CreateRGBSurface
				(flags, width, height, depth,
				0x00FF0000,
				0x0000FF00,
				0x000000FF,
				0xFF000000);
			SDL_assert(surface != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return surface;
		}
		void SDLUtilityTool::DestroySurface(SDL_Surface* surface)
		{
			SDL_assert(m_initialized);
			SDL_assert(surface != nullptr);
			SDL_FreeSurface(surface);
			m_sdlSurfaces--;
			m_totalResources--;
		}

		SDL_Texture* SDLUtilityTool::CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface)
		{
			SDL_assert(m_initialized);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_assert(texture != nullptr);
			m_sdlTextures++;
			m_totalResources++;
			return texture;
		}

		void SDLUtilityTool::DestroyTexture(SDL_Texture* texture)
		{
			SDL_assert(m_initialized);
			SDL_assert(texture != nullptr);
			SDL_DestroyTexture(texture);
			m_sdlTextures--;
			m_totalResources--;
		}

		TTF_Font* SDLUtilityTool::CreateFont(const char *file, int ptsize)
		{
			SDL_assert(m_initialized);
			TTF_Font* font = TTF_OpenFont(file, ptsize);
			SDL_assert(font != nullptr);
			m_sdlFonts++;
			m_totalResources++;
			return font;
		}

		void SDLUtilityTool::DestroyFont(TTF_Font* font)
		{
			SDL_assert(m_initialized);
			SDL_assert(font != nullptr);
			TTF_CloseFont(font);
			m_sdlFonts--;
			m_totalResources--;
		}

		SDL_Surface* SDLUtilityTool::RenderText_Blended(TTF_Font *font,
			const char *text, SDL_Color fg)
		{
			SDL_assert(m_initialized);
			SDL_Surface* surface = TTF_RenderText_Blended(font, text, fg);
			SDL_assert(surface != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return surface;
		}

		SDL_GameController* SDLUtilityTool::GameControllerOpen(int controllerNum)
		{
			SDL_assert(m_initialized);
			SDL_GameController* controller = SDL_GameControllerOpen(controllerNum);
			SDL_assert(controller != nullptr);
			m_sdlControllers++;
			m_totalResources++;
			return controller;
			
		}

		void SDLUtilityTool::GameControllerClose(SDL_GameController* controller)
		{
			SDL_assert(m_initialized);
			SDL_assert(controller != nullptr);
			SDL_GameControllerClose(controller);
			m_sdlControllers--;
			m_totalResources--;
		}

		SDL_Surface* SDLUtilityTool::LoadImageSurface(const char* file)
		{
			SDL_assert(m_initialized);
			SDL_Surface* image = IMG_Load(file);
			SDL_assert(image != nullptr);
			m_sdlSurfaces++;
			m_totalResources++;
			return image;
		}

		SDL_Texture* SDLUtilityTool::LoadImageTexture(const char* file, SDL_Renderer* renderer)
		{
			SDL_assert(m_initialized);
			SDL_Surface* imageSurface = LoadImageSurface(file);
			SDL_assert(imageSurface != nullptr);
			SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
			SDL_assert(imageTexture != nullptr);
			DestroySurface(imageSurface);
			m_sdlTextures++;
			m_totalResources++;
			return imageTexture;
		}

		SDL_Texture* LoadImageTexture(const char* file);

		void SDLUtilityTool::PrintStatus()
		{
			std::cerr << "Resources are not cleaned up." << std::endl;
			std::cerr << "Windows: " << m_sdlWindows << std::endl;
			std::cerr << "Renderers: " << m_sdlRenderers << std::endl;
			std::cerr << "Surfaces: " << m_sdlSurfaces << std::endl;
			std::cerr << "Textures: " << m_sdlTextures << std::endl;
			std::cerr << "Fonts: " << m_sdlFonts << std::endl;
			std::cerr << "Controllers: " << m_sdlControllers << std::endl;
		}

	} // namespace Graphics
} // namespace Heroes