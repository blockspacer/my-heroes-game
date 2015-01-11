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
				std::string LoadEntityFile(const char* entityFile, EntityMemory& entityMemory, SDL_Renderer* renderer);
				int LoadDynamicEntity(std::string staticName, b2Vec2 position, b2Vec2 orientation, EntityMemory& entityMemory);
				void UnloadDynamicEntity(int dynamicID, EntityMemory& entityMemory);

			private:

				// These functions recieve the first element in the respective category
				// * not the element of that category
				bool LoadSystemsComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadStatusComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadHealthComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadAIComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadActionComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadMovementComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadPhysicsComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory);
				bool LoadBodyDef(tinyxml2::XMLElement* element, b2FixtureDef& bodyDef);
				bool LoadRenderComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory, SDL_Renderer* renderer);

				Engine::SDLUtilityTool& m_sdlUtilityTool;

				tinyxml2::XMLDocument m_loadingDoc;
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

