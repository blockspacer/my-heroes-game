#include "Engine/Log.h"

#include "States/GamePlayState/Systems/WarriorSystems.h"
#include "States/GamePlayState/Entities/EntityLoader.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			const char* STATIC_FILE_NAME = "Name";
			const char* STATIC_FILE_DEATH_TIMER = "DeathTimer";
			const char* STATIC_FILE_HEALTH = "Health";
			const char* STATIC_FILE_RESISTANCE = "Resistance";
			const char* STATIC_FILE_ATTACK_DAMAGE = "AttackDamage";
			const char* STATIC_FILE_MOVEMENT_SPEED = "MovementSpeed";
			const char* STATIC_FILE_ENTITY_TEXTURE = "EntityTexture";
			const char* STATIC_FILE_HEALTH_BAR_TEXTURE = "HealthBarTexture";

			EntityLoader::EntityLoader(Engine::SDLUtilityTool& sdlUtilityTool) : m_sdlUtilityTool(sdlUtilityTool)
			{

			}

			EntityLoader::~EntityLoader()
			{

			}

			// Loads a single entity returning its id
			void EntityLoader::LoadEntityFile(const char* entityFile, EntityMemory& entityMemory, SDL_Renderer* renderer)
			{
				tinyxml2::XMLDocument doc;
				tinyxml2::XMLError error = doc.LoadFile(entityFile);
				if (error != tinyxml2::XML_NO_ERROR)
				{
					g_Log_Write_L2(LOG_FILE_LOAD_EVENT, doc.GetErrorStr1());
				}

				SDL_assert(error == tinyxml2::XML_NO_ERROR);

				tinyxml2::XMLElement* rootElement = doc.RootElement();

				SDL_assert(rootElement->NoChildren() == false);

				tinyxml2::XMLElement* element = rootElement->FirstChildElement();
				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(STATIC_FILE_NAME) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticEntityMap[text] = entityMemory.m_freeStaticEntityID;

						// there needs to be a way to attach functions to this entity
						entityMemory.m_staticSystemComponents[entityMemory.m_freeStaticEntityID].m_statusSystem = WarriorSystems::WarriorStatusSystem;
						entityMemory.m_staticSystemComponents[entityMemory.m_freeStaticEntityID].m_healthSystem = WarriorSystems::WarriorHealthSystem;
						entityMemory.m_staticSystemComponents[entityMemory.m_freeStaticEntityID].m_actionSystem = WarriorSystems::WarriorActionSystem;
						entityMemory.m_staticSystemComponents[entityMemory.m_freeStaticEntityID].m_movementSystem = WarriorSystems::WarriorMovementSystem;
						entityMemory.m_staticSystemComponents[entityMemory.m_freeStaticEntityID].m_renderUpdateSystem = WarriorSystems::WarriorRenderUpdateSystem;

					}
					else if (elementName.compare(STATIC_FILE_DEATH_TIMER) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticStatusComponents[entityMemory.m_freeStaticEntityID].m_deathTimer = atoi(text.c_str());
						SDL_assert(entityMemory.m_staticStatusComponents[entityMemory.m_freeStaticEntityID].m_deathTimer >= 0);
					}
					else if (elementName.compare(STATIC_FILE_HEALTH) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticHealthComponents[entityMemory.m_freeStaticEntityID].m_healthNormal = atoi(text.c_str());
						SDL_assert(entityMemory.m_staticHealthComponents[entityMemory.m_freeStaticEntityID].m_healthNormal >= 0);
					}
					else if (elementName.compare(STATIC_FILE_RESISTANCE) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticHealthComponents[entityMemory.m_freeStaticEntityID].m_resistanceNormal = atoi(text.c_str());
						SDL_assert(entityMemory.m_staticHealthComponents[entityMemory.m_freeStaticEntityID].m_resistanceNormal >= 0);
					}
					else if (elementName.compare(STATIC_FILE_ATTACK_DAMAGE) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticActionComponents[entityMemory.m_freeStaticEntityID].m_normalAttackDamage = atoi(text.c_str());
						SDL_assert(entityMemory.m_staticActionComponents[entityMemory.m_freeStaticEntityID].m_normalAttackDamage >= 0);
					}
					else if (elementName.compare(STATIC_FILE_MOVEMENT_SPEED) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticMovementComponents[entityMemory.m_freeStaticEntityID].m_speed = atoi(text.c_str());
						SDL_assert(entityMemory.m_staticMovementComponents[entityMemory.m_freeStaticEntityID].m_speed >= 0);
					}
					else if (elementName.compare(STATIC_FILE_ENTITY_TEXTURE) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticRenderComponents[entityMemory.m_freeStaticEntityID].m_entityTexture = m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer);
						SDL_QueryTexture(entityMemory.m_staticRenderComponents[entityMemory.m_freeStaticEntityID].m_entityTexture, 
							NULL, 
							NULL, 
							&(entityMemory.m_staticRenderComponents[entityMemory.m_freeStaticEntityID].m_textureWidth), 
							&(entityMemory.m_staticRenderComponents[entityMemory.m_freeStaticEntityID].m_textureHeight));
					}
					else if (elementName.compare(STATIC_FILE_HEALTH_BAR_TEXTURE) == 0)
					{
						text = element->GetText();
						entityMemory.m_staticRenderComponents[entityMemory.m_freeStaticEntityID].m_healthBarTexture = m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer);
					}

					element = element->NextSiblingElement();
				}

				entityMemory.m_freeStaticEntityID++; // increment the nex free static entity ID

				g_Log_Write_L2(LOG_FILE_LOAD_EVENT, entityFile);
			}
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes