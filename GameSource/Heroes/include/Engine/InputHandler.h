// Heroes Game
// Author: Samuel Hall
// Last Commented ? Needs to have all GameController code migrated here

#pragma once

#include <mutex>

namespace Heroes
{

	enum ButtonState
	{
		BUTTON_PRESSED,
		BUTTON_HELD,
		BUTTON_UNPRESSED,
	};

	namespace Engine
	{
		class StateEngine;
		class SDLUtilityTool;

		/*
		 * This class should be the one place in the program that user input is recieved, if
		 * not the desing is wrong. This class is not extendable and should be a singleton.
		 */
		class InputHandler final
		{
		public:

			// Returns that acive status of the InputHandler
			bool IsActive();
			
			Sint16 Left_Stick_X();
			Sint16 Left_Stick_Y();
			Sint16 Right_Stick_X();
			Sint16 Right_Stick_Y();

			ButtonState GetButton(SDL_GameControllerButton button);

		private:

			// only the state engine can create this class, this is to control the access and creation of the InputHandler
			friend class SDLUtilityTool;

			friend int ProcessInputFunctionXboxController(void* inputHandler);

			void SetButton(SDL_GameControllerButton button, ButtonState state);
			void DetermineButtonAndState(SDL_GameControllerButton button, ButtonState** statePointer, std::mutex** mutexPointer);

			// Constructor does not start the InputHandler (see Start)
			InputHandler();
			virtual ~InputHandler();

			void Activate();
			void Deactivate();


			SDL_GameController* m_gameController{ nullptr };

			//SDLUtilityTool& m_sdlUtilityTool;
			//SDL_Thread* m_sdlInputThread{ nullptr };

			bool m_active{ true };

			// should prolly have mutexs for each type of input
			std::mutex m_mutex;

			// TODO - figure out the inputs are handled

			// key presses, holds and old input should be removed

			ButtonState m_start{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_startMutex;

			ButtonState m_back{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_backMutex;

			ButtonState m_a{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_aMutex;

			ButtonState m_b{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_bMutex;

			ButtonState m_x{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_xMutex;

			ButtonState m_y{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_yMutex;

			ButtonState m_up{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_upMutex;

			ButtonState m_down{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_downMutex;

			ButtonState m_left{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_leftMutex;

			ButtonState m_right{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_rightMutex;

			ButtonState m_rightBumber{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_rightBumberMutex;

			ButtonState m_leftBumber{ ButtonState::BUTTON_UNPRESSED };
			std::mutex m_leftBumberMutex;
			

		};

	} // namespace Engine
} // namespace Heroes