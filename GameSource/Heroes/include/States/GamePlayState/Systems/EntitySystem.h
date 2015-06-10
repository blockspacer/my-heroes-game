// Heroes Game
// Author: Samuel Hall
// Last Commented 1/30/2015

#pragma once

#include <Engine/SDLUtilityTool.h>
#include <Engine/InputHandler.h>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			// for use of the EntityMemory class below
			class EntityMemory;

			// Below are the two types of entity functions (these will probably be temporary until 
			// the Lua scripting is figured out)

			// this typedef defines the functions that never change for an entity. That means that
			// when an entity performs an attack there will be a function that handles the attack.
			// This will make more sense when the next typedef is understood.
			typedef void(*EntitySystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory);
			
			// This typedef defines decision logic for an entity. THat means that an entity could be controlled
			// by some type of "AI" defined in this function or by a function that reads controller input. These can
			// dynamically change during the game and result in the EntitySystemFunc functions to be called when 
			// "AI" wants to.
			typedef void(*EntityDecisionSystemFunc)(int targetEntity, GamePlay::EntityMemory& entityMemory, Engine::InputHandler& inputHandler);

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
