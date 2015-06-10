// Heroes Game
// Author: Samuel Hall
// Last Commented 1/23/2015

#pragma once

#include <stdint.h>

#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{
		// ************************** HOW TO CREATE A STATE ******************************* //
		/*
		
		1) Create a new class that extends State
		2) You must implement an update function for your new state.
		   The update function should progress the state in some way, either
		   by getting input from the InputHandler or changing the next state to have a
		   value (aka a StateCreationFunction and an optional void* data for that state). This can 
		   be done easily by the SetNextState function. Finally the m_hasNextState has to be set to true
		   for the state engine to know that it is time to transition.
		3) (Optionally) override the render function for your state
		4) The state engine will take care of the rest by calling Update, Render, HasNextState, GetNextState
		
		*/
		// ******************************************************************************** //

		/*
		* This class represents the state creation data which is used for things like creating a
		* game play state with a particula level. In general it is the method that states can use to
		* send information to each other.
		*/
		class StateCreationData;

		/*
		* This class encapsulates the state create function so that nullptr can be avoided
		* It provides the ability to see if there is a function and to call that function.
		*/
		class StateCreationFunction;

		/*
		* This is a class that holds all relevant information for how to make a state.
		* It holds the construction function and the data that the state expects to
		* recieve (if any).
		*/
		class StateCreationPackage;

		/*
		* States represent the different functionality of the game. They are used for things like
		* the main menu, level loading, gameplay. It is the object that the state engine uses to
		* transition through the game.
		*/
		class State;

		// type for void* data for state
		typedef void* UserDataType;

		/*
		 * Function to create the EndState which is just a nullptr for the creation state function.
		 */
		State* CreateEndState(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& structData);
		
		const nullptr_t NoStateCreationData = nullptr;

		class StateCreationData
		{
		public:

			/*
			 * Constructor requires a void* userData and a bool to indicate whether is
			 * was allocated in memory or not.
			 */
			StateCreationData(UserDataType userData, bool dataAllocated);
			~StateCreationData() {}

			// self explanatory
			bool HasUserData();
			UserDataType GetUserData();

		private:

			bool m_dateAllocated{ false };
			UserDataType m_userData{ nullptr };
		};

		
		class StateCreationFunction
		{
		public:
			typedef State* (*CreateStateFunc)(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData);

			/*
			* Constructor requires a creation function
			*/
			StateCreationFunction(CreateStateFunc createStateFunc);

			// self explanatory
			bool HasStateCreationFunc();
			State* CallStateCreationFunction(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData);

		private:

			CreateStateFunc m_createStateFunc{ nullptr };
		};

		
		class StateCreationPackage
		{
		public:

			/*
			* Constructor requires a StateCreationFunction and a StateCreationData
			*/
			StateCreationPackage(StateCreationFunction createStateFunc, StateCreationData stateCreationData) : m_createStateFunc(createStateFunc), m_stateCreationData(stateCreationData) {}

			StateCreationFunction m_createStateFunc{ nullptr };

			StateCreationData m_stateCreationData;

		};

		class State
		{
		public:

			/*
			 * Constructor requires sdlUtilityTool because only the state engine should
			 * be responsible for making new states.
			 */
			State(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData);
			virtual ~State();

			virtual void Update(uint32_t milliTime) = 0; 

			/*
			 * This is an overridable renderer. By default it copies the surface to a
			 * texture and then renders to the texture to the screen.
			 */
			virtual void Render();

			/*
			 * Returns whether there is a valid next state.
			 */
			bool HasNextState() const;

			/*
			* This returns the next state by setting the next state package to the paramter passed in.
			* Assumes that m_nextState is true.
			*/
			StateCreationPackage GetNextStateCreationPackage();

		protected:

			/*
			 * This clears the surface for this state.
			 */
			void ClearSurface();

			/*
			* This sets m_nextState to the parameter passed in.
			*/
			void SetNextState(StateCreationPackage stateCreatePackage);

			bool m_nextState{ false };
			StateCreationPackage m_stateCreatePackage;

			SDLUtilityTool& m_sdlUtilityTool;

			// all states will have a basic sdl visuals and input
			SDL_Window* m_sdlWindow{ nullptr };
			SDL_Renderer* m_sdlRenderer{ nullptr };
			SDL_Surface* m_sdlSurface{ nullptr };
			SDL_Texture* m_sdlTexture{ nullptr };

		};

	} // namespace Engine
} // namespace Heroes