#include <SDL_assert.h>

#include "Engine/State.h"

namespace Heroes
{
	namespace Engine
	{
		State* CreateEndState(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& structData)
		{
			return nullptr;
		}

		State::State(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData) : m_sdlUtilityTool(sdlUtilityTool)
		{		
			m_sdlWindow = sdlUtilityTool.CreateWindow("Heroes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
			SDL_assert(m_sdlWindow != nullptr);

			m_sdlRenderer = sdlUtilityTool.CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_assert(m_sdlRenderer != nullptr);

			SDL_DisplayMode display;
			SDL_GetWindowDisplayMode(m_sdlWindow, &display);

			m_sdlSurface = sdlUtilityTool.CreateRGBSurface(0, display.w, display.h, 32);
			SDL_assert(m_sdlSurface != nullptr);

			m_sdlTexture = sdlUtilityTool.CreateTextureFromSurface(m_sdlRenderer, m_sdlSurface);
			SDL_assert(m_sdlTexture != nullptr);

			SDL_assert(SDL_NumJoysticks() != 0);
			if (SDL_IsGameController(0)) {
				m_controller = sdlUtilityTool.GameControllerOpen(0);
			}
			SDL_assert(m_controller != nullptr);

			// set the events to be ignored
			SDL_JoystickEventState(SDL_QUERY);
		}

		State::~State()
		{
			m_sdlUtilityTool.GameControllerClose(m_controller);
			m_sdlUtilityTool.DestroyTexture(m_sdlTexture);
			m_sdlUtilityTool.DestroySurface(m_sdlSurface);
			m_sdlUtilityTool.DestroyRenderer(m_sdlRenderer);
			m_sdlUtilityTool.DestroyWindow(m_sdlWindow);
		}

		void State::Render()
		{
			SDL_UpdateTexture(m_sdlTexture, NULL, m_sdlSurface->pixels, m_sdlSurface->w * sizeof (Uint32));
			SDL_RenderClear(m_sdlRenderer);
			SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, NULL);
			SDL_RenderPresent(m_sdlRenderer);
		}

		bool State::HasNextState() const
		{
			return m_nextState;
		}

		StateCreationPackage State::GetNextStateCreationPackage()
		{
			return m_stateCreatePackage;
		}

		void State::ClearSurface()
		{
			SDL_FillRect(m_sdlSurface, NULL, SDL_MapRGB(m_sdlSurface->format, 100, 100, 200));
		}

		void State::SetNextState(StateCreationPackage stateCreatePackage)
		{
			m_nextState = true;
			m_stateCreatePackage = stateCreatePackage;
		}

	} // namespace Engine
} // namespace Heroes