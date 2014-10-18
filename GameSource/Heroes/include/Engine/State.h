#pragma once

#include <stdint.h>

#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace Engine
	{

		/**
		* This class is to represent the void* data in a clean way to the states so they never
		* have to test for null themselves.
		*/
		class StateCreationData;

		/**
		* This class is to represent the void* data in a clean way to the states so they never
		* have to test for null themselves, might be made into template.
		*/
		class StateCreationFunction;

		/**
		* This is a class for the complete package of the function to call to create
		* particular state along with the StateCreationData for the state, might be made into template.
		*/
		class StateCreationPackage;

		/**
		* States represent the major functions of the game such as the main menu or playing a level
		*/
		class State;

		// type for void* data for state
		typedef void* UserDataType;

		/**
		* Function to create the EndState.
		*/
		State* CreateEndState(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& structData);
		
		class StateCreationData
		{
		public:

			StateCreationData() {}
			StateCreationData(UserDataType userData) : m_userData(userData) {}

			bool HasUserData()
			{
				return m_userData != nullptr;
			}

			UserDataType GetUserData()
			{
				return m_userData;
			}

		private:

			UserDataType m_userData{ nullptr };
		};

		class StateCreationFunction
		{
		public:
			typedef State* (*CreateStateFunc)(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData);

			StateCreationFunction() {}
			StateCreationFunction(CreateStateFunc createStateFunc) : m_createStateFunc(createStateFunc) {}

			bool HasStateCreationFunc()
			{
				return m_createStateFunc != nullptr;
			}

			CreateStateFunc GetStateCreationFunction()
			{
				return m_createStateFunc;
			}

		private:

			CreateStateFunc m_createStateFunc{ nullptr };
		};

		class StateCreationPackage
		{
		public:

			StateCreationPackage() {}

			StateCreationPackage(StateCreationFunction createStateFunc, StateCreationData stateCreationData) : m_createStateFunc(createStateFunc), m_stateCreationData(stateCreationData) {}

			StateCreationFunction m_createStateFunc{ nullptr };

			StateCreationData m_stateCreationData;

		};

		class State
		{
		public:

			State(Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData);
			virtual ~State();

			virtual void Update(uint32_t milliTime) = 0; 
			virtual void Render();
			bool HasNextState() const;
			StateCreationPackage GetNextStateCreationPackage();

		protected:

			void ClearSurface();
			void SetNextState(StateCreationPackage stateCreatePackage);

			bool m_nextState{ false };
			StateCreationPackage m_stateCreatePackage;

			SDLUtilityTool& m_sdlUtilityTool;

			// all states will have a window to render
			SDL_Window* m_sdlWindow{ nullptr };
			SDL_Renderer* m_sdlRenderer{ nullptr };
			SDL_Surface* m_sdlSurface{ nullptr };
			SDL_Texture* m_sdlTexture{ nullptr };
			SDL_GameController* m_controller{ nullptr };

		};

	} // namespace Engine
} // namespace Heroes