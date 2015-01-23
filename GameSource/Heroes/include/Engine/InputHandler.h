// Heroes Game
// Author: Samuel Hall
// Last Commented ? Needs to have all GameController code migrated here

#pragma once

#include <mutex>

namespace Heroes
{
	namespace Engine
	{
		class SDLUtilityTool;

		/*
		 * This class should be the one place in the program that user input is recieved, if
		 * not the desing is wrong. This class is not extendable and should be a singleton.
		 */
		class InputHandler final
		{
		public:

			// Constructor requires the SDLUtilityTool
			InputHandler(SDLUtilityTool& m_sdlUtilityTool);
			~InputHandler();

			void Start(const char* name);
			bool IsActive();

			
			bool GetRightBumberPressed();
			void SetRightBumberPressed();

		private:

			SDLUtilityTool& m_sdlUtilityTool;
			SDL_Thread* m_sdlInputThread{ nullptr };

			bool m_active{ true };
			std::mutex m_mutex;

			bool m_rightBumberPressed{ false };
			bool m_rightBumberReleased{ false };
			bool m_rightBumberHold{ false };

			// the state of the input
		};

	} // namespace Engine
} // namespace Heroes