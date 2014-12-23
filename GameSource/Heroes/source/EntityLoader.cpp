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

			const char* ENTITY = "Entity";

			const char* SYSTEMS_COMPONENT = "SystemsComponent";

			const char* STATUS_COMPONENT = "StatusComponent";
			const char* STATUS_COMPONENT_NAME = "Name";

			const char* HEALTH_COMPONENT = "HealthComponent";
			const char* HEALTH_COMPONENT_HEALTH_NORMAL = "HealthNormal";
			const char* HEALTH_COMPONENT_DEATH_TIMER = "DeathTimer";

			const char* AI_COMPONENT = "AIComponent";
			const char* AI_COMPONENT_TRACKING_RANGE = "TrackingRange";

			const char* ACTION_COMPONENT = "ActionComponent";
			const char* ACTION_COMPONENT_NORMAL_ATTACK_DAMAGE = "NormalAttackDamage";
			const char* ACTION_COMPONENT_NORMAL_ATTACK_SPEED = "NormalAttackSpeed";
			const char* ACTION_COMPONENT_NORMAL_ATTACK_RANGE = "NormalAttackRange";
			const char* ACTION_COMPONENT_NORMAL_ATTACK_DAMAGE_POINT = "NormalAttackDamagePoint";

			const char* MOVEMENT_COMPONENT = "MovementComponent";
			const char* MOVEMENT_COMPONENT_MOVEMENT_SPEED = "MovementSpeed";

			const char* PHYSICS_COMPONENT = "PhysicsComponent";
			const char* PHYSICS_COMPONENT_ENTITY_BODY = "EntityBody";
			// these are the sub categories of EntityBody
			const char* ENTITY_TYPE_ALLY_BODY = "AllyBody";
			const char* ENTITY_TYPE_ALLY_SENSOR = "AllySensor";
			const char* ENTITY_TYPE_ENEMY_BODY = "EnemyBody";
			const char* ENTITY_TYPE_ENEMY_SENSOR = "EnemySensor";
			const char* ENTITY_TYPE_ENVIRONMENT_BODY = "EnvironmentBody";
			const char* ENTITY_TYPE_ENVIRONMENT_SENSOR = "EnvironmentSensor";
			// end of subcategories
			const char* PHYSICS_COMPONENT_BODY_TYPE = "BodyType";
			const char* PHYSICS_COMPONENT_BODY_DENSITY = "BodyDensity";
			const char* PHYSICS_COMPONENT_BODY_FRICTION = "BodyFriction";
			const char* PHYSICS_COMPONENT_BODY_SHAPE = "BodyShape";
			const char* PHYSICS_COMPONENT_ENTITY_SENSOR = "EntitySensor";
			const char* PHYSICS_COMPONENT_SENSOR_SHAPE = "SensorShape";
			// these are the sub categories of EntityType
			const char* SHAPE_CIRCLE = "Circle";
			// end of subcategories
			
			const char* RENDER_COMPONENT = "RenderComponent";
			const char* RENDER_COMPONENT_STATUS_TEXTURE = "StatusTexture";
			const char* RENDER_COMPONENT_STANDING_ANIMATION = "StandingAnimation";
			const char* RENDER_COMPONENT_STANDING_ANIMATION_FRAMES = "StandingAnimationFrames";
			const char* RENDER_COMPONENT_STANDING_ANIMATION_TIME = "StandingAnimationTime";
			const char* RENDER_COMPONENT_MOVING_ANIMATION = "MovingAnimation";
			const char* RENDER_COMPONENT_MOVING_ANIMATION_FRAMES = "MovingAnimationFrames";
			const char* RENDER_COMPONENT_MOVING_ANIMATION_TIME = "MovingAnimationTime";
			const char* RENDER_COMPONENT_BASIC_ATTACKING_ANIMATION = "BasicAttackingAnimation";
			const char* RENDER_COMPONENT_BASIC_ATTACKING_ANIMATION_FRAMES = "BasicAttackingAnimationFrames";

			EntityLoader::EntityLoader(Engine::SDLUtilityTool& sdlUtilityTool) : m_sdlUtilityTool(sdlUtilityTool)
			{

			}

			EntityLoader::~EntityLoader()
			{

			}

			int EntityLoader::LoadDynamicEntity(std::string staticName, b2Vec2 position, b2Vec2 orientation, EntityMemory& entityMemory)
			{
				EntityStaticIDType staticID = entityMemory.m_staticEntityMap[staticName];

				EntityDynamicIDType id = entityMemory.m_freeEntities.front();


				// manually load the player controlled entity


				// system component
				entityMemory.m_systemsComponents.SetAISystem_D(id, entityMemory.m_systemsComponents.GetAISystem_S(staticID));

				// status component
				entityMemory.m_statusComponents.SetStaticEntityID_D(id, staticID); // warrior is the only static entity
				entityMemory.m_statusComponents.SetActiveStatus_D(id, ActiveStatusType::ACTOR);
				entityMemory.m_statusComponents.SetIdleStatus_D(id, IdleStatusType::STANDING);
				
				// health component
				entityMemory.m_healthComponents.SetNormalHealth_D(id, entityMemory.m_healthComponents.GetNormalHealth_S(staticID));
				entityMemory.m_healthComponents.SetDeathTimer_D(id, entityMemory.m_healthComponents.GetDeathTimer_S(staticID));

				// target component

				// action component
				entityMemory.m_healthComponents.SetDirectDamage_D(id, 0);
				entityMemory.m_healthComponents.SetDirectDamageSource_D(id, -1);

				// TODO
				// physics component
				b2BodyDef def;

				def.type = static_cast<b2BodyType>(entityMemory.m_physicsComponents.GetBodyType_S(staticID));
				def.position = position; // center
				def.angle = 0;
				def.fixedRotation = true;
				entityMemory.m_physicsComponents.SetEntityBody_D(id, entityMemory.m_entityWorld.CreateBody(&def));
				entityMemory.m_physicsComponents.GetEntityBody_D(id)->SetUserData((void*)id);

				
				entityMemory.m_physicsComponents.GetEntityBody_D(id)->CreateFixture(&entityMemory.m_physicsComponents.GetBodyDef_S(staticID));
				if (!entityMemory.m_physicsComponents.GetBodyDef_S(staticID).isSensor)
				{
					entityMemory.m_physicsComponents.GetEntityBody_D(id)->CreateFixture(&entityMemory.m_physicsComponents.GetVisionDef_S(staticID));
				}			
				// m_AIComponents
				// m_actionComponents
				// m_directionComponents
				entityMemory.m_AIComponents.SetDirection_D(id, orientation);
				entityMemory.m_AIComponents.SetOrientation_D(id, orientation);
				entityMemory.m_AIComponents.SetTargetMapSource_D(id);
				// m_movementComponents
				// m_renderComponents

				entityMemory.m_renderComponents.GetStatusRect_D(id)->h = 8;
				entityMemory.m_renderComponents.GetStatusRect_D(id)->w = 64; // TODO
				//m_renderComponents.SetAngle_D(id, 0.0f);

				entityMemory.m_freeEntities.pop_front();
				entityMemory.m_usedEntities.push_back(id);

				return id;
			}

			// Loads a single entity returning its id
			std::string EntityLoader::LoadEntityFile(const char* entityFile, EntityMemory& entityMemory, SDL_Renderer* renderer)
			{
				std::string elementName;
				std::string text;
				std::string returnString;

				int staticID = entityMemory.GetStaticID();

				tinyxml2::XMLDocument doc;
				tinyxml2::XMLError error = doc.LoadFile(entityFile);
				if (error != tinyxml2::XML_NO_ERROR)
				{
					g_Log_Write_L2(LOG_FILE_LOAD_EVENT, doc.GetErrorStr1());
				}

				g_assert(error == tinyxml2::XML_NO_ERROR);

				tinyxml2::XMLElement* rootElement = doc.RootElement();

				elementName = rootElement->Name();
				g_assert(elementName.compare(ENTITY) == 0);
				g_assert(rootElement->NoChildren() == false);

				tinyxml2::XMLElement* element = rootElement->FirstChildElement();
				

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					tinyxml2::XMLElement* firstChild = element->FirstChildElement();

					if (elementName.compare(SYSTEMS_COMPONENT) == 0)
					{
						g_assert(LoadSystemsComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(STATUS_COMPONENT) == 0)
					{
						g_assert(LoadStatusComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(HEALTH_COMPONENT) == 0)
					{
						g_assert(LoadHealthComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(AI_COMPONENT) == 0)
					{
						g_assert(LoadAIComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(ACTION_COMPONENT) == 0)
					{
						g_assert(LoadActionComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(MOVEMENT_COMPONENT) == 0)
					{
						g_assert(LoadMovementComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(PHYSICS_COMPONENT) == 0)
					{
						g_assert(LoadPhysicsComponent(firstChild, staticID, entityMemory));
					}
					else if (elementName.compare(RENDER_COMPONENT) == 0)
					{
						g_assert(LoadRenderComponent(firstChild, staticID, entityMemory, renderer));
					}
					else
					{
						g_assert(false);
					}

					element = element->NextSiblingElement();
				}

				returnString = entityMemory.m_statusComponents.GetName_S(staticID);

				g_Log_Write_L2(LOG_FILE_LOAD_EVENT, entityFile);

				return returnString;
			}

			bool EntityLoader::LoadSystemsComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// loads the lua script files
				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					return false;

					element = element->NextSiblingElement();
				}

				// manually load the systems these will eventually be scripts
				entityMemory.m_systemsComponents.SetStatusSystem_S(staticID, WarriorSystems::WarriorStatusSystem);
				entityMemory.m_systemsComponents.SetHealthSystem_S(staticID, WarriorSystems::WarriorHealthSystem);
				entityMemory.m_systemsComponents.SetAISystem_S(staticID, WarriorSystems::WarriorAISystem);
				entityMemory.m_systemsComponents.SetActionSystem_S(staticID, WarriorSystems::WarriorActionSystem);
				entityMemory.m_systemsComponents.SetMovementSystem_S(staticID, WarriorSystems::WarriorMovementSystem);

				return true;
			}

			bool EntityLoader::LoadStatusComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// death timer

				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(STATUS_COMPONENT_NAME) == 0)
					{
						text = element->GetText();

						entityMemory.m_staticEntityMap[text] = staticID;

						entityMemory.m_statusComponents.SetName_S(staticID, text);
						g_assert(entityMemory.m_statusComponents.GetName_S(staticID).compare("") != 0);
					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				return true;
			}

			bool EntityLoader::LoadHealthComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// normal health

				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(HEALTH_COMPONENT_HEALTH_NORMAL) == 0)
					{
						text = element->GetText();

						entityMemory.m_healthComponents.SetNormalHealth_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_healthComponents.GetNormalHealth_S(staticID) >= 0);
					}
					else if (elementName.compare(HEALTH_COMPONENT_DEATH_TIMER) == 0)
					{
						text = element->GetText();

						entityMemory.m_healthComponents.SetDeathTimer_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_healthComponents.GetDeathTimer_S(staticID) > 0);
					}
					else
					{
						return false;
					}
					
					element = element->NextSiblingElement();
				}

				return true;
			}

			bool EntityLoader::LoadAIComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// TrackingRange

				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(AI_COMPONENT_TRACKING_RANGE) == 0)
					{
						text = element->GetText();

						entityMemory.m_AIComponents.SetTrackingRange_S(staticID, static_cast<float>(atof(text.c_str())));
						g_assert(entityMemory.m_AIComponents.GetTrackingRange_S(staticID) > 0);
					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				return true;
			}

			bool EntityLoader::LoadActionComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// normalAttackDamage
				// normalAttackSpeed
				// normalAttackDamagePoint

				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(ACTION_COMPONENT_NORMAL_ATTACK_DAMAGE) == 0)
					{
						text = element->GetText();

						entityMemory.m_actionComponents.SetNormalAttackDamage_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_actionComponents.GetNormalAttackDamage_S(staticID) >= 0);
					}
					else if(elementName.compare(ACTION_COMPONENT_NORMAL_ATTACK_SPEED) == 0)
					{
						text = element->GetText();

						entityMemory.m_actionComponents.SetNormalAttackSpeed_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_actionComponents.GetNormalAttackSpeed_S(staticID) > 0);
					}
					else if (elementName.compare(ACTION_COMPONENT_NORMAL_ATTACK_RANGE) == 0)
					{
						text = element->GetText();

						entityMemory.m_actionComponents.SetNormalAttackRange_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_actionComponents.GetNormalAttackRange_S(staticID) > 0);
					}
					else if (elementName.compare(ACTION_COMPONENT_NORMAL_ATTACK_DAMAGE_POINT) == 0)
					{
						text = element->GetText();

						entityMemory.m_actionComponents.SetNormalAttackDamagePoint_S(staticID, static_cast<float>(atof(text.c_str())));
						g_assert(entityMemory.m_actionComponents.GetNormalAttackDamagePoint_S(staticID) >= 0.0 &&
							     entityMemory.m_actionComponents.GetNormalAttackDamagePoint_S(staticID) <= 1.0);
					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				return true;
			}

			bool EntityLoader::LoadMovementComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// movement speed

				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(MOVEMENT_COMPONENT_MOVEMENT_SPEED) == 0)
					{
						text = element->GetText();

						entityMemory.m_movementComponents.SetMovementSpeed_S(staticID, static_cast<float>(atof(text.c_str())));
						g_assert(entityMemory.m_movementComponents.GetMovementSpeed_S(staticID) >= 0);
					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				return true;
			}

			bool EntityLoader::LoadPhysicsComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory)
			{
				// Loads:
				// Body Type

				std::string elementName;
				std::string text;

				b2FixtureDef bodyDef;
				b2FixtureDef visionDef;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(PHYSICS_COMPONENT_BODY_TYPE) == 0)
					{
						text = element->GetText();
						entityMemory.m_physicsComponents.SetBodyType_S(staticID, static_cast<b2BodyType>(atoi(text.c_str())));
						g_assert(entityMemory.m_physicsComponents.GetBodyType_S(staticID) == 0 ||
							     entityMemory.m_physicsComponents.GetBodyType_S(staticID) == 2);
					}
					else if(elementName.compare(PHYSICS_COMPONENT_ENTITY_BODY) == 0)
					{
						text = element->GetText();

						if (text.compare(ENTITY_TYPE_ALLY_BODY) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ALLY_BODY;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ALLY_BODY_COL;
							bodyDef.isSensor = false;
						}
						else if (text.compare(ENTITY_TYPE_ALLY_SENSOR) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ALLY_SENSOR;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ALLY_SENSOR_COL;
							bodyDef.isSensor = true;
						}
						else if (text.compare(ENTITY_TYPE_ENEMY_BODY) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ENEMY_BODY;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ENEMY_BODY_COL;
							bodyDef.isSensor = false;
						}
						else if (text.compare(ENTITY_TYPE_ENEMY_SENSOR) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ENEMY_SENSOR;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ENEMY_SENSOR_COL;
							bodyDef.isSensor = true;
						}
						else if (text.compare(ENTITY_TYPE_ENVIRONMENT_BODY) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ENVIRONMENT_BODY;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ENVIRONMENT_BODY_COL;
							bodyDef.isSensor = false;
						}
						else if (text.compare(ENTITY_TYPE_ENVIRONMENT_SENSOR) == 0)
						{
							bodyDef.filter.maskBits = EntityCollisionMasks::ENVIRONMENT_SENSOR;
							bodyDef.filter.categoryBits = EntityCollisionCategories::ENVIRONMENT_SENSOR_COL;
							bodyDef.isSensor = true;
						}
						else
						{
							return false;
						}

					}
					else if (elementName.compare(PHYSICS_COMPONENT_BODY_DENSITY) == 0)
					{
						text = element->GetText();
						bodyDef.density = static_cast<float>(atof(text.c_str()));
						
					}
					else if (elementName.compare(PHYSICS_COMPONENT_BODY_FRICTION) == 0)
					{
						text = element->GetText();
						bodyDef.friction = static_cast<float>(atof(text.c_str()));
						
					}
					else if (elementName.compare(PHYSICS_COMPONENT_BODY_SHAPE) == 0)
					{
						text = element->GetText();

						if (text.compare(SHAPE_CIRCLE) == 0)
						{
							b2CircleShape* shape = new b2CircleShape; // im responsible
							shape->m_radius = 0.5;
							shape->m_p = b2Vec2(0, 0.25);
							bodyDef.shape = shape;
						}
						else
						{
							return false;
						}

					}
					else if (elementName.compare(PHYSICS_COMPONENT_ENTITY_SENSOR) == 0)
					{
						text = element->GetText();

						if (text.compare(ENTITY_TYPE_ALLY_SENSOR) == 0)
						{
							visionDef.filter.maskBits = EntityCollisionMasks::ALLY_SENSOR;
							visionDef.filter.categoryBits = EntityCollisionCategories::ALLY_SENSOR_COL;
							visionDef.isSensor = true;
						}
						else if (text.compare(ENTITY_TYPE_ENEMY_SENSOR) == 0)
						{
							visionDef.filter.maskBits = EntityCollisionMasks::ENEMY_SENSOR;
							visionDef.filter.categoryBits = EntityCollisionCategories::ENEMY_SENSOR_COL;
							visionDef.isSensor = true;
						}
						else if (text.compare(ENTITY_TYPE_ENVIRONMENT_SENSOR) == 0)
						{
							visionDef.filter.maskBits = EntityCollisionMasks::ENVIRONMENT_SENSOR;
							visionDef.filter.categoryBits = EntityCollisionCategories::ENVIRONMENT_SENSOR_COL;
							visionDef.isSensor = true;
						}
						else
						{
							return false;
						}

					}
					else if (elementName.compare(PHYSICS_COMPONENT_SENSOR_SHAPE) == 0)
					{
						text = element->GetText();

						if (text.compare(SHAPE_CIRCLE) == 0)
						{
							b2CircleShape* shape = new b2CircleShape; // im responsible
							shape->m_radius = 5;
							shape->m_p = b2Vec2(0, 0.25);
							visionDef.shape = shape;
						}
						else
						{
							return false;
						}

					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				// test the components of fixdef then assign
				g_assert(bodyDef.shape != nullptr);
				g_assert(bodyDef.filter.maskBits != 0);
				g_assert(bodyDef.filter.categoryBits != 0);
				g_assert(bodyDef.density > 0.0f);
				g_assert(bodyDef.friction > 0.0f);

				// not a sensor
				if (!bodyDef.isSensor)
				{
					g_assert(visionDef.shape != nullptr);
					g_assert(visionDef.filter.maskBits != 0);
					g_assert(visionDef.filter.categoryBits != 0);
				}

				entityMemory.m_physicsComponents.SetBodyDef_S(staticID, bodyDef);
				entityMemory.m_physicsComponents.SetVisionDef_S(staticID, visionDef);

				return true;
			}

			bool EntityLoader::LoadRenderComponent(tinyxml2::XMLElement* element, int staticID, EntityMemory& entityMemory, SDL_Renderer* renderer)
			{
				// Loads:
				// Status Texture
				// Normal Animation
				// Normal Animation Frames
				// Normal Animation Time
				// Moving Animation
				// Moving Animation Frames
				// Moving Animation Time
				// Basic Attacking Animation
				// Basic Attacking Animation Frames
				// Basic Attacking Animation Time

				int animationSize = 0;
				std::string elementName;
				std::string text;

				while (element != nullptr)
				{
					text.clear();
					elementName.clear();
					elementName = element->Name();

					// decision on what part of the static entity we are loading
					if (elementName.compare(RENDER_COMPONENT_STANDING_ANIMATION) == 0)
					{
						animationSize = 0;
						text = element->GetText();

						entityMemory.m_renderComponents.SetStandingFramesTexture_S(staticID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
						g_assert(entityMemory.m_renderComponents.GetStandingFramesTexture_S(staticID) != nullptr);

						SDL_QueryTexture(entityMemory.m_renderComponents.GetStandingFramesTexture_S(staticID),
							NULL,
							NULL,
							nullptr,
							&animationSize);

						entityMemory.m_renderComponents.SetStandingTextureSize_S(staticID, animationSize);
						g_assert(entityMemory.m_renderComponents.GetStandingTextureSize_S(staticID) > 0);
						
						
					}
					else if (elementName.compare(RENDER_COMPONENT_STANDING_ANIMATION_FRAMES) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetStandingFrames_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_renderComponents.GetStandingFrames_S(staticID) > 0);
					}
					else if (elementName.compare(RENDER_COMPONENT_STANDING_ANIMATION_TIME) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetStandingAnimationTimeMilli_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_renderComponents.GetStandingAnimationTimeMilli_S(staticID) > 0);
					}
					else if(elementName.compare(RENDER_COMPONENT_MOVING_ANIMATION) == 0)
					{
						animationSize = 0;
						text = element->GetText();

						entityMemory.m_renderComponents.SetMovingFramesTexture_S(staticID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
						g_assert(entityMemory.m_renderComponents.GetMovingFramesTexture_S(staticID) != nullptr);

						SDL_QueryTexture(entityMemory.m_renderComponents.GetMovingFramesTexture_S(staticID),
							NULL,
							NULL,
							nullptr,
							&animationSize);

						entityMemory.m_renderComponents.SetMovingTextureSize_S(staticID, animationSize);
						g_assert(entityMemory.m_renderComponents.GetMovingTextureSize_S(staticID) > 0);
						animationSize = 0;
					}
					else if (elementName.compare(RENDER_COMPONENT_MOVING_ANIMATION_FRAMES) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetMovingFrames_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_renderComponents.GetMovingFrames_S(staticID) > 0);
					}
					else if (elementName.compare(RENDER_COMPONENT_MOVING_ANIMATION_TIME) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetMovingAnimationTimeMilli_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_renderComponents.GetMovingAnimationTimeMilli_S(staticID) > 0);
					}
					else if(elementName.compare(RENDER_COMPONENT_BASIC_ATTACKING_ANIMATION) == 0)
					{
						animationSize = 0;
						text = element->GetText();

						entityMemory.m_renderComponents.SetBasicAttackFramesTexture_S(staticID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
						g_assert(entityMemory.m_renderComponents.GetBasicAttackFramesTexture_S(staticID) != nullptr);

						SDL_QueryTexture(entityMemory.m_renderComponents.GetBasicAttackFramesTexture_S(staticID),
							NULL,
							NULL,
							nullptr,
							&animationSize);

						entityMemory.m_renderComponents.SetBasicAttackTextureSize_S(staticID, animationSize);
						g_assert(entityMemory.m_renderComponents.GetBasicAttackTextureSize_S(staticID) > 0);
						animationSize = 0;
					}
					else if (elementName.compare(RENDER_COMPONENT_BASIC_ATTACKING_ANIMATION_FRAMES) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetBasicAttackFrames_S(staticID, atoi(text.c_str()));
						g_assert(entityMemory.m_renderComponents.GetBasicAttackFrames_S(staticID) > 0);
					}
					else if (elementName.compare(RENDER_COMPONENT_STATUS_TEXTURE) == 0)
					{
						text = element->GetText();

						entityMemory.m_renderComponents.SetStatusTexture_S(staticID, m_sdlUtilityTool.LoadImageTexture(text.c_str(), renderer));
						g_assert(entityMemory.m_renderComponents.GetStatusTexture_S(staticID) != nullptr);
					}
					else
					{
						return false;
					}

					element = element->NextSiblingElement();
				}

				return true;
			}

			void EntityLoader::UnloadDynamicEntity(int dynamicID, EntityMemory& entityMemory)
			{
				// manually load the player controlled entity


				// system component
				entityMemory.m_systemsComponents.SetAISystem_D(dynamicID, nullptr);

				// status component
				entityMemory.m_statusComponents.SetStaticEntityID_D(dynamicID, -1); // warrior is the only static entity
				entityMemory.m_statusComponents.SetActiveStatus_D(dynamicID, ActiveStatusType::NA);
				entityMemory.m_statusComponents.SetIdleStatus_D(dynamicID, IdleStatusType::STANDING);

				// health component
				entityMemory.m_healthComponents.SetNormalHealth_D(dynamicID, 0);
				entityMemory.m_healthComponents.SetDeathTimer_D(dynamicID, 0);

				// target component

				// action component
				entityMemory.m_healthComponents.SetDirectDamage_D(dynamicID, 0);
				entityMemory.m_healthComponents.SetDirectDamageSource_D(dynamicID, -1);

				b2Body* body = entityMemory.m_physicsComponents.GetEntityBody_D(dynamicID);
				entityMemory.m_entityWorld.DestroyBody(body);

				// m_AIComponents
				// m_actionComponents
				// m_directionComponents
				entityMemory.m_AIComponents.SetDirection_D(dynamicID, b2Vec2_zero);
				entityMemory.m_AIComponents.SetOrientation_D(dynamicID, b2Vec2_zero);
				// clear targets

				entityMemory.m_renderComponents.GetStatusRect_D(dynamicID)->h = 0;
				entityMemory.m_renderComponents.GetStatusRect_D(dynamicID)->w = 0; // TODO
				//m_renderComponents.SetAngle_D(id, 0.0f);

				

				entityMemory.m_freeEntities.push_front(dynamicID);
				//entityMemory.m_usedEntities.push_back(dynamicID); // TODO fix this

			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes