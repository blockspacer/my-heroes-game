#include "Engine/SDLUtilityTool.h"
#include "Engine/InputHandler.h"

#include <iostream>

namespace Heroes
{
	namespace Engine
	{
		int ProcessInputFunction(void* inputHandler)
		{
			InputHandler* input = (InputHandler*) inputHandler;

			SDL_Event sdlEvent;

			while (input->IsActive())
			{
				// proccess an event
				
				if (SDL_PollEvent(&sdlEvent))
				{
					switch (sdlEvent.type)
					{
					case SDL_KEYDOWN:
						/* handle keyboard stuff here */
						break;

					case SDL_QUIT:
						/* Set whatever flags are necessary to */
						/* end the main game loop here */
						break;
					case SDL_CONTROLLERBUTTONDOWN:
						if (sdlEvent.cbutton.state == SDL_PRESSED && sdlEvent.cbutton.button == SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
						{
							/* code goes here */
							std::cout << "Pressed a button" << std::endl;
							input->SetRightBumberPressed();
						}
						break;
						break;
					}
				}

			}

			return 0;
		}

		InputHandler::InputHandler(SDLUtilityTool& sdlUtilityTool) : m_sdlUtilityTool(sdlUtilityTool)
		{
			// create the thread for listening for input

			
		}

		InputHandler::~InputHandler()
		{
			// destroy the thread for listening for input
			m_active = false;
			int returnValue = 0;
			m_sdlUtilityTool.WaitThread(m_sdlInputThread, &returnValue);
		}

		bool InputHandler::GetRightBumberPressed()
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			bool value = m_rightBumberPressed;
			m_rightBumberPressed = false;
			return value;
		}

		void InputHandler::SetRightBumberPressed()
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			m_rightBumberPressed = true;
		}

		void InputHandler::Start(const char* name)
		{
			m_sdlInputThread = m_sdlUtilityTool.CreateThread(ProcessInputFunction, name, this);
		}

		bool InputHandler::IsActive()
		{
			return m_active;
		}

	} // namespace Engine
} // namespace Heroes