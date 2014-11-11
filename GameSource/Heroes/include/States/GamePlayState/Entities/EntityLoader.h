#pragma once

#include <list>
#include <vector>
#include <map> // future find better implementation

#include <tinyxml2.h>

#include "Engine/SDLUtilityTool.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			class EntityLoader final
			{
			public:

				EntityLoader(Engine::SDLUtilityTool& sdlUtilityTool);
				~EntityLoader();

				// Loads a single entity returning its id
				void LoadEntityFile(const char* entityFile, EntityMemory& entityMemory, SDL_Renderer* renderer);

			private:

				Engine::SDLUtilityTool& m_sdlUtilityTool;

				tinyxml2::XMLDocument m_loadingDoc;
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

