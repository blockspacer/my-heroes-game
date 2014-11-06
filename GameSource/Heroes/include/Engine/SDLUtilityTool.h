#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

namespace Heroes
{
	namespace Engine
	{
		const uint32_t SDL_INIT_FLAGS = SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_VIDEO;

		/**
		 * This is a class that handles all the SDL object 
		 * creation
		 */
		class SDLUtilityTool final
		{
		public:

			// SDL
			SDL_Window* CreateWindow(const char *title,
									int x, int y, int w,
									int h, uint32_t flags);
			void DestroyWindow(SDL_Window* window);
			SDL_Renderer* CreateRenderer(SDL_Window * window,
										 int index, Uint32 flags);
			void DestroyRenderer(SDL_Renderer * renderer);
			SDL_Surface* CreateRGBSurface
				(Uint32 flags, int width, int height, int depth);
			void DestroySurface(SDL_Surface* surface);
			SDL_Texture* CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface);
			void DestroyTexture(SDL_Texture* texture);

			// SDL ttf
			TTF_Font* CreateFont(const char *file, int ptsize);
			void DestroyFont(TTF_Font* font);
			SDL_Surface* RenderText_Blended(TTF_Font *font,
				const char *text, SDL_Color fg);
			SDL_GameController* GameControllerOpen(int controllerNum);
			void GameControllerClose(SDL_GameController* controller);
			SDL_Surface* LoadBMP(const char* file);


			/**
			* Prints what current resources are being used
			*/
			void PrintStatus();

			/**
			 * Return the number of active SDL resources
			 */
			int GetNumberOfSDLResources() { return m_totalResources; }

		private:

			// only the state engine can create this class
			friend class StateEngine;

			SDLUtilityTool();
			virtual ~SDLUtilityTool();

			bool Init();
			bool Destroy();

			bool m_initialized{ false };

			// variables to hold the number of resources
			int m_sdlWindows{ 0 };
			int m_sdlRenderers{ 0 };
			int m_sdlSurfaces{ 0 };
			int m_sdlTextures{ 0 };
			int m_sdlControllers{ 0 };

			int m_sdlFonts{ 0 };

			int m_totalResources{ 0 };

		};

	} // namespace Engine
} // namespace Heroes

