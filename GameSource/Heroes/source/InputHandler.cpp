
#include "Engine/Log.h"
#include "Engine/SDLUtilityTool.h"
#include "Engine/InputHandler.h"



namespace Heroes
{
	namespace Engine
	{
		

		InputHandler::InputHandler() {}

		InputHandler::~InputHandler() {}

		bool InputHandler::IsActive()
		{
			return m_active;
		}

		void InputHandler::Deactivate()
		{
			m_active = false;
		}

		void InputHandler::Activate()
		{
			m_active = true;
		}

		ButtonState InputHandler::GetButton(SDL_GameControllerButton button)
		{
			// figure out which button we are dealing with
			ButtonState* buttonState = nullptr;
			std::mutex* buttonMutex = nullptr;
			DetermineButtonAndState(button, &buttonState, &buttonMutex);		

			// actually get the button
			ButtonState state;
			std::lock_guard<std::mutex> lock(*buttonMutex);
			state = *buttonState;
			
			// if it is a press reset the button
			// holds should not change that the button is still
			// held
			if (state == ButtonState::BUTTON_PRESSED)
			{
				*buttonState = ButtonState::BUTTON_UNPRESSED;
			}
			
			return state;
		}

		void InputHandler::SetButton(SDL_GameControllerButton button, ButtonState state)
		{
			// figure out which button we are dealing with
			ButtonState* buttonState = nullptr;
			std::mutex* buttonMutex = nullptr;
			DetermineButtonAndState(button, &buttonState, &buttonMutex);

			// set the new state
			std::lock_guard<std::mutex> lock(*buttonMutex);
			*buttonState = state;
		}

		Sint16 InputHandler::Left_Stick_X()
		{
			return SDL_GameControllerGetAxis(m_gameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
		}

		Sint16 InputHandler::Left_Stick_Y()
		{
			return SDL_GameControllerGetAxis(m_gameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
		}

		Sint16 InputHandler::Right_Stick_X()
		{
			return SDL_GameControllerGetAxis(m_gameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX);
		}

		Sint16 InputHandler::Right_Stick_Y()
		{
			return SDL_GameControllerGetAxis(m_gameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY);
		}

		void InputHandler::DetermineButtonAndState(SDL_GameControllerButton button, ButtonState** statePointer, std::mutex** mutexPointer)
		{
			switch (button)
			{
				case SDL_CONTROLLER_BUTTON_START:
					*statePointer = &m_start;
					*mutexPointer = &m_startMutex;
					break;
				case SDL_CONTROLLER_BUTTON_BACK:
					*statePointer = &m_back;
					*mutexPointer = &m_backMutex;
					break;
				case SDL_CONTROLLER_BUTTON_A:
					*statePointer = &m_a;
					*mutexPointer = &m_aMutex;
					break;
				case SDL_CONTROLLER_BUTTON_B:
					*statePointer = &m_b;
					*mutexPointer = &m_bMutex;
					break;
				case SDL_CONTROLLER_BUTTON_X:
					*statePointer = &m_x;
					*mutexPointer = &m_xMutex;
					break;
				case SDL_CONTROLLER_BUTTON_Y:
					*statePointer = &m_y;
					*mutexPointer = &m_yMutex;
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					*statePointer = &m_up;
					*mutexPointer = &m_upMutex;
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					*statePointer = &m_down;
					*mutexPointer = &m_downMutex;
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					*statePointer = &m_left;
					*mutexPointer = &m_leftMutex;
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					*statePointer = &m_right;
					*mutexPointer = &m_rightMutex;
					break;
				case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
					*statePointer = &m_rightBumber;
					*mutexPointer = &m_rightBumberMutex;
					break;
				case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
					*statePointer = &m_leftBumber;
					*mutexPointer = &m_leftBumberMutex;
					break;
				default:
					g_assert(false);
			}
			
		}

	} // namespace Engine
} // namespace Heroes