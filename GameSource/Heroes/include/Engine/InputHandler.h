#pragma once

#include <mutex>

namespace Heroes
{
	namespace Engine
	{
		class SDLUtilityTool;

		class InputHandler final
		{
		public:

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