// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#pragma once

// used for maintaining SDL threads
#include <unordered_map>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "InputHandler.h"

namespace Heroes
{
	namespace Engine
	{
		// Flags for how SDL and SDL_IMG should be initialized
		// Fairly self explanatory
		const uint32_t SDL_INIT_FLAGS = SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_VIDEO;
		const uint32_t SDL_IMG_INIT_FLAGS = IMG_INIT_PNG;

		/*
		 * This is a class that handles all the SDL object creation.
		 * It should be used as the only way to create or destroy SDL resources.
		 * It keeps track of all resources allocated which can be accessed through various methods
		 * Most of the methods are nearly identical to the SDL counter parts in both name and arguments.
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
			SDL_Thread* CreateThread(SDL_ThreadFunction, const char* name, void* data);
			void WaitThread(SDL_Thread* thread, int* returnValue);
			void WaitThread(const char* name, int* returnValue);

			// SDL ttf
			TTF_Font* CreateFont(const char *file, int ptsize);
			void DestroyFont(TTF_Font* font);
			SDL_Surface* RenderText_Blended(TTF_Font *font,
				const char *text, SDL_Color fg);

			SDL_Surface* LoadImageSurface(const char* file);
			SDL_Texture* LoadImageTexture(const char* file, SDL_Renderer* renderer);

			InputHandler& GetInputHandler();

			/*
			 * Returns a status string the has useful information about the current state of the SDLUtilityTool.
			 * The tool can be 3 states, resources are currently allocated, no resources are allocated or something is
			 * wrong with the SDLUtilityTool because the numbers of resources allocated is negative. The third state should
			 * never happen.
			 */
			std::string StatusString();

			/*
			 * Return the number of active SDL resources
			 */
			int GetNumberOfSDLResources() { return m_totalResources; }

		private:

			// only the state engine can create this class, this is to control the access and creation of SDL resources
			friend class StateEngine;

			SDLUtilityTool();
			virtual ~SDLUtilityTool();

			// These intialize and destroy SDL and SDL_IMG to the flags above and additionally initialize SDL_TTF
			bool Init();
			bool Destroy();

			// called internally
			bool InitInputHandler();
			void DestroyInputHandler();

			// This is called after any SDL call to log an error is there is one. It checks the value of the error string
			// and then clears it to avoid duplicate error logging.
			void LogSDLError();
			// these two are technically not needed but they treat the libraries as being independent
			void LogTTFError();
			void LogIMGError();

			// flag for knowing the state of tool
			bool m_initialized{ false };

			// InputHandler
			InputHandler m_inputHandler;
			SDL_GameController* m_inputController;
			SDL_Thread* m_inputThread;

			// variables to hold the number of resources
			int m_sdlWindows{ 0 };
			int m_sdlRenderers{ 0 };
			int m_sdlSurfaces{ 0 };
			int m_sdlTextures{ 0 };
			int m_sdlControllers{ 0 };
			int m_sdlThreads{ 0 };

			// this map contains information for cleaning up the threads and allows threads to be accessed
			// by names
			std::unordered_map<std::string, SDL_Thread*> m_threadMap;

			// number of fonts that are allocated
			int m_sdlFonts{ 0 };

			int m_totalResources{ 0 };

			// this is used to catch errors within sdl
			std::string m_sdlErrorString{ "" };

		};

	} // namespace Engine
} // namespace Heroes

