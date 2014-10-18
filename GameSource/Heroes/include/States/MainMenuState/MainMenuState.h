# pragma once

#include "Engine/State.h"
#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace States
	{
		namespace MainMenu
		{

			Engine::State* CreateMainMenuState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData);

			enum Option
			{
				SELECTION_TIME_MILLI = 150
			};

			class MainMenuState final : public Engine::State
			{
			public:

				MainMenuState(Engine::SDLUtilityTool& sdlUtilityTool, Engine::StateCreationData& stateCreationData);
				virtual ~MainMenuState();

				virtual void Update(uint32_t milliTime);

			private:

				void UpdateNextStatePackage();
				void UpdateTexture();

				int m_optionIndex{ 0 };
				int m_optionDirection{ 0 };
				Uint32 m_lastOptionChange{ SDL_GetTicks() };

				SDL_Surface* m_normalOptions[3];
				SDL_Surface* m_highlightedOptions[3];

			};
		} // namespace MainMenu
	} // namespace States
} //namespace Heroes