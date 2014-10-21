#pragma once

#include "Engine/State.h"
#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{

		const uint32_t SDL_INIT_FLAGS = SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_VIDEO;

		/**
		* This class represents the State Engine of the game. It facilitates state transformation
		* and while running and rendering the current state.
		*/
		class StateEngine final
		{
		public:
			
			StateEngine();
			virtual ~StateEngine();

			bool Init();
			void Run(StateCreationPackage firstStateCreationPackage);
			bool Destroy();

		private:
			
			bool InternalInit();
			bool InternalDestroy();

			bool m_initialized{ false };
			Engine::SDLUtilityTool m_sdlUtilityTool;

		};

	} // namespace Graphics
} // namespace Heroes