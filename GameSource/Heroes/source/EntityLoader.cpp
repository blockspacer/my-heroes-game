#include "Engine/Log.h"

#include "States/GamePlayState/Systems/WarriorSystems.h"
#include "States/GamePlayState/Entities/EntityComponentConstants.h"
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

				g_assert(error == tinyxml2::XML_NO_ERROR);

				tinyxml2::XMLElement* rootElement = doc.RootElement();

				g_assert(rootElement->NoChildren() == false);

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
						entityMemory.m_staticEntityMap[text] = entityMemory.m_freeStaticEntityID; // FIX THIS
						int staticEntityID = entityMemory.m_freeStaticEntityID;

						// there needs to be a way to attach functions to this entity
						entityMemory.m_systemsComponents.SetStatusSystem_S(staticEntityID, WarriorSystems::WarriorStatusSystem);
						entityMemory.m_systemsComponents.SetHealthSystem_S(staticEntityID, WarriorSystems::WarriorHealthSystem);
						entityMemory.m_systemsComponents.SetTargetSystem_S(staticEntityID, WarriorSystems::WarriorTargetSystem);
						entityMemory.m_systemsComponents.SetActionSystem_S(staticEntityID, WarriorSystems::WarriorActionSystem);
						entityMemory.m_systemsComponents.SetDirectionSystem_S(staticEntityID, WarriorSystems::WarriorDirectionSystem);
						entityMemory.m_systemsComponents.SetMovementSystem_S(staticEntityID, WarriorSystems::WarriorMovementSystem);
						entityMemory.m_systemsComponents.SetRenderUpdateSystem_S(staticEntityID, WarriorSystems::WarriorRenderUpdateSystem);

					}
					else if (elementName.compare(STATIC_FILE_DEATH_TIMER) == 0)
					{
						text = element->GetText();
						entityMemory.m_statusComponents.SetDeathTimer_S(entityMemory.m_freeStaticEntityID, atoi(text.c_str()));
						g_assert(entityMemory.m_statusComponents.GetDeathTimer_S(entityMemory.m_freeStaticEntityID) >= 0);
					}
					else if (elementName.compare(STATIC_FILE_HEALTH) == 0)
					{
						text = element->GetText();
						entityMemory.m_healthComponents.SetNormalHealth_S(entityMemory.m_freeStaticEntityID, atoi(text.c_str()));
						g_assert(entityMemory.m_healthComponents.GetNormalHealth_S(entityMemory.m_freeStaticEntityID) >= 0);
					}
					else if (elementName.compare(STATIC_FILE_RESISTANCE) == 0)
					{
						//text = element->GetText();
						//entityMemory.m_staticHealthComponents.at(entityMemory.m_freeStaticEntityID).m_resistanceNormal = atoi(text.c_str());
						//g_assert(entityMemory.m_staticHealthComponents.at(entityMemory.m_freeStaticEntityID).m_resistanceNormal >= 0);
					}
					else if (elementName.compare(STATIC_FILE_ATTACK_DAMAGE) == 0)
					{
						text = element->GetText();
						entityMemory.m_actionComponents.SetNormalAttackDamage_S(entityMemory.m_freeStaticEntityID, atoi(text.c_str()));
						g_assert(entityMemory.m_actionComponents.GetNormalAttackDamage_S(entityMemory.m_freeStaticEntityID) >= 0);
					}
					else if (elementName.compare(STATIC_FILE_MOVEMENT_SPEED) == 0)
					{
						text = element->GetText();
						entityMemory.m_movementComponents.SetMovementSpeed_S(entityMemory.m_freeStaticEntityID, static_cast<float>(atof(text.c_str())));
						g_assert(entityMemory.m_movementComponents.GetMovementSpeed_S(entityMemory.m_freeStaticEntityID) >= 0);
					}
					else if (elementName.compare(STATIC_FILE_ENTITY_TEXTURE) == 0)
					{
						text = element->GetText();
						entityMemory.m_renderComponents.SetEntityTexture_S(entityMemory.m_freeStaticEntityID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
						int textureWidth = 0;
						int textureHeight = 0;
						SDL_QueryTexture(entityMemory.m_renderComponents.GetEntityTexture_S(entityMemory.m_freeStaticEntityID), 
							NULL, 
							NULL, 
							&textureWidth, 
							&textureHeight);
						entityMemory.m_renderComponents.SetTextureWidth_S(entityMemory.m_freeStaticEntityID, textureWidth);
						entityMemory.m_renderComponents.SetTextureHeight_S(entityMemory.m_freeStaticEntityID, textureHeight);
					}
					else if (elementName.compare(STATIC_FILE_HEALTH_BAR_TEXTURE) == 0)
					{
						text = element->GetText();
						entityMemory.m_renderComponents.SetStatusTexture_S(entityMemory.m_freeStaticEntityID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
					}

					element = element->NextSiblingElement();
				}

				// manually add the animation stuff
				// standing animation
				entityMemory.m_renderComponents.SetStandingFramesTexture_S(entityMemory.m_freeStaticEntityID, m_sdlUtilityTool.LoadImageTexture("./Resources/Textures/WarriorStandingAnimation.png", renderer));
				int animationSize = 0;
				SDL_QueryTexture(entityMemory.m_renderComponents.GetStandingFramesTexture_S(entityMemory.m_freeStaticEntityID),
					NULL,
					NULL,
					nullptr,
					&animationSize);

				entityMemory.m_renderComponents.SetStandingTextureSize_S(entityMemory.m_freeStaticEntityID, animationSize);
				entityMemory.m_renderComponents.SetStandingFrames_S(entityMemory.m_freeStaticEntityID, 12);
				entityMemory.m_renderComponents.SetStandingAnimationTimeMilli_S(entityMemory.m_freeStaticEntityID, 750);

				// moving animation
				entityMemory.m_renderComponents.SetMovingFramesTexture_S(entityMemory.m_freeStaticEntityID, m_sdlUtilityTool.LoadImageTexture("./Resources/Textures/WarriorMovingAnimation.png", renderer));
				SDL_QueryTexture(entityMemory.m_renderComponents.GetMovingFramesTexture_S(entityMemory.m_freeStaticEntityID),
					NULL,
					NULL,
					nullptr,
					&animationSize);

				entityMemory.m_renderComponents.SetMovingTextureSize_S(entityMemory.m_freeStaticEntityID, animationSize);
				entityMemory.m_renderComponents.SetMovingFrames_S(entityMemory.m_freeStaticEntityID, 12);
				entityMemory.m_renderComponents.SetMovingAnimationTimeMilli_S(entityMemory.m_freeStaticEntityID, 750);

				// basic attack animation animation
				entityMemory.m_renderComponents.SetBasicAttackFramesTexture_S(entityMemory.m_freeStaticEntityID, m_sdlUtilityTool.LoadImageTexture("./Resources/Textures/WarriorAttackAnimation.png", renderer));
				SDL_QueryTexture(entityMemory.m_renderComponents.GetBasicAttackFramesTexture_S(entityMemory.m_freeStaticEntityID),
					NULL,
					NULL,
					nullptr,
					&animationSize);

				entityMemory.m_renderComponents.SetBasicAttackTextureSize_S(entityMemory.m_freeStaticEntityID, animationSize);
				entityMemory.m_renderComponents.SetBasicAttackFrames_S(entityMemory.m_freeStaticEntityID, 12);
				entityMemory.m_renderComponents.SetBasicAttackAnimationTimeMilli_S(entityMemory.m_freeStaticEntityID, 750);

				entityMemory.m_freeStaticEntityID++; // increment the nex free static entity ID

				g_Log_Write_L2(LOG_FILE_LOAD_EVENT, entityFile);
			}
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes