#pragma once

#include "Engine/Log.h"
#include "Engine/State.h"
#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{

		/**
		* This class represents the State Engine of the game. It facilitates state transformation
		* and handles updating and rendering the current state. The state engine in only in one state
		* at any given time
		*/
		class StateEngine final
		{
		public:
			
			// empty constructor/destructor
			StateEngine();
			~StateEngine();

			/*
			 * Initializes the state engine, return true whether it was succesful or
			 * false whether there was a failure.
			 */
			bool Init();

			/*
			* Returns whether the state engine has been initialized
			*/
			bool IsInit();

			/*
			* This starts the state engine based on the state that is
			* passed
			*/
			void Run(StateCreationPackage firstStateCreationPackage);

			/*
			* This destroys (unitializes) the state engine
			*/
			bool Destroy();

		private:

			bool m_initialized{ false };
			Engine::SDLUtilityTool m_sdlUtilityTool;

		};

	} // namespace Graphics
} // namespace Heroes