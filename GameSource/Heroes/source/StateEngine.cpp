#include <SDL_assert.h> 
#include <iostream>

#include "Engine/StateEngine.h"

namespace Heroes
{
	namespace Engine
	{

		StateEngine::StateEngine() {}
		StateEngine::~StateEngine() {}

		bool StateEngine::Init()
		{
			bool success = false;

			if (!IsInit())
			{
				success = m_sdlUtilityTool.Init();
				if (success)
				{
					m_initialized = true;
				}
			}

			return IsInit();
		}

		void StateEngine::Run(StateCreationPackage stateCreationPackage)
		{
			// create the first state

			State* state = nullptr;
			

			if (stateCreationPackage.m_createStateFunc.HasStateCreationFunc())
			{
				state = stateCreationPackage.m_createStateFunc.CallStateCreationFunction(m_sdlUtilityTool, stateCreationPackage.m_stateCreationData);
			}

			Uint32 currentTime = SDL_GetTicks();

			while (state != nullptr)
			{

				// time controlled conditional
				if (currentTime + 33 < SDL_GetTicks())
				{
					

					// Get the time for the state of this update
					currentTime = SDL_GetTicks();

					// run the state for 33 milliseconds
					state->Update(33);

					// render the state
					state->Render();

					// See if we have found the next state
					if (state->HasNextState())
					{

						stateCreationPackage = state->GetNextStateCreationPackage();
						delete state;
						state = nullptr;

						// print the state of resources if they are not cleaned up
						if (m_sdlUtilityTool.GetNumberOfSDLResources() != 0)
						{
							m_sdlUtilityTool.PrintStatus();
						}

						// check that sdl resources are cleaned up
						SDL_assert(m_sdlUtilityTool.GetNumberOfSDLResources() == 0);

						if (stateCreationPackage.m_createStateFunc.HasStateCreationFunc())
						{
							state = stateCreationPackage.m_createStateFunc.CallStateCreationFunction(m_sdlUtilityTool, stateCreationPackage.m_stateCreationData);
						}

						// these should always be true except for endstate
						if (state != nullptr)
						{
							SDL_assert(!state->HasNextState());
						}

						
					}
				}
				
			}
		}

		bool StateEngine::Destroy()
		{
			bool success = false;

			if (IsInit())
			{
				success = m_sdlUtilityTool.Destroy();
				if (success)
				{
					m_initialized = false;
				}
			}
			
			SDL_assert(IsInit() == false);
			return IsInit();
		}

		bool StateEngine::IsInit()
		{
			return m_initialized;
		}

	} // namespace Engine
} // namespace Heroes