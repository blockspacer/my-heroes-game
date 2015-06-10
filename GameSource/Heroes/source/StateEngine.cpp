#include "Engine/Log.h" 
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

			g_Log_Write_L1(LOG_INITIALIZATION_EVENT, "Intialized State Engine");

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
							g_Log_Write_L1(LOG_SDL_RESOURCES, m_sdlUtilityTool.StatusString());		
						}

						// check that sdl resources are cleaned up
						g_assert(m_sdlUtilityTool.GetNumberOfSDLResources() == 0);

						if (stateCreationPackage.m_createStateFunc.HasStateCreationFunc())
						{
							state = stateCreationPackage.m_createStateFunc.CallStateCreationFunction(m_sdlUtilityTool, stateCreationPackage.m_stateCreationData);
						}

						// these should always be true except for endstate
						if (state != nullptr)
						{
							g_assert(!state->HasNextState());
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
			
			g_assert(IsInit() == false);
			g_Log_Write_L1(LOG_UNINITIALIZATION_EVENT, "Destroyed State Engine");

			return IsInit();
		}

		bool StateEngine::IsInit()
		{
			return m_initialized;
		}

	} // namespace Engine
} // namespace Heroes