#pragma once

#include <list>

#include <Box2D/Box2D.h>

#include "States/GamePlayState/Systems/EntitySystem.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			typedef int StaticEntityIDType;

			enum EntityCollisionMasks
			{
				ENVIRONMENT_BODY = 0x0001,
				ENVIRONMENT_SENSOR = 0x0002,
				ENEMY_BODY = 0x0004,
				ENEMY_SENSOR = 0x0008,
				ALLY_BODY = 0x0010,
				ALLY_SENSOR = 0x0020
			};

			enum EntityCollisionCategories
			{
				ALLY_BODY_COL = ALLY_BODY | ENEMY_BODY | ENEMY_SENSOR | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
				ALLY_SENSOR_COL = ENEMY_BODY,
				ENEMY_BODY_COL = ALLY_BODY | ALLY_SENSOR | ENEMY_BODY | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
				ENEMY_SENSOR_COL = ALLY_BODY,
				ENVIRONMENT_BODY_COL = ALLY_BODY | ENEMY_BODY | ENVIRONMENT_BODY,
				ENVIRONMENT_SENSOR_COL = ALLY_BODY | ENEMY_BODY
			};

			struct DynamicSystemsComponent
			{
				GamePlay::EntityDecisionSystemFunc m_targetSystem;
				GamePlay::EntityDecisionSystemFunc m_directionSystem;
			};

			struct StaticSystemsComponent
			{
				GamePlay::EntitySystemFunc m_statusSystem;
				GamePlay::EntitySystemFunc m_healthSystem;
				GamePlay::EntitySystemFunc m_actionSystem;
				GamePlay::EntitySystemFunc m_movementSystem;
				GamePlay::EntityRenderFunc m_renderUpdateSystem;
			};

			enum ActionType
			{
				NO_ACTION,
				CLOSE_COMBAT
			};

			enum MovementType
			{
				NO_MOVEMENT,
				MOVING
			};

			enum StatusType
			{
				ALIVE,
				DEAD
			};

			struct DynamicStatusComponent
			{
				ActionType m_action{ ActionType::NO_ACTION }; // whether entity is actively doing something (busy)
				MovementType m_movement{ MovementType::NO_MOVEMENT };
				StatusType m_status{ StatusType::DEAD }; // whether entity is dead
				int m_deathTimer{ -1 }; // amount until this entity should be cleaned up
				StaticEntityIDType m_staticEntityID{ -1 };
			};

			struct StaticStatusComponent
			{
				int m_deathTimer{ -1 }; // max death count down
			};

			// HEALTH SYSTEM
			// ACTION SYSTEM
			struct DynamicHealthComponent
			{
				int m_healthNormalCurrent{ -1 };
				int m_damageDirect{ -1 };
				int m_damageDirectSource{ -1 };
			};

			struct StaticHealthComponent
			{
				int m_healthNormal{ -1 };
				int m_resistanceNormal{ -1 };
			};

			// TARGET SYSTEM
			struct DynamicTargetComponent {
				int target{ -1 };
				float targetDistance{ -1.0f };

				// vision cones
				b2Joint* connectionJoint{ nullptr }; // not sure why this is here don't delete
				b2Body* visionBody{ nullptr };
				b2Shape* smallSightShape{ nullptr };
				b2FixtureDef smallSightFixDef;
				b2Shape* largeSightShape{ nullptr };
				b2FixtureDef largeSightFixDef;

				// direction that this entity is facing
				b2Vec2 m_orientation;
			};

			struct StaticTargetComponent {
				float trackingRange{ -1.0f };
			};

			// ACTION SYSTEM
			struct DynamicActionComponent
			{
			};

			struct StaticActionComponent
			{
				int m_normalAttackDamage{ -1 };
			};

			// PHYSICS data not needed by a system
			struct DynamicPhysicsComponent
			{
				b2Body* body{ nullptr }; // single body of the entity
				std::list<b2Shape*> shapes; // number of shapes that make up the entity
			};

			struct StaticPhysicsComponent
			{
			};

			// MOVEMENT SYSTEM
			// ACTION SYSTEM
			struct DynamicMovementComponent
			{
			};

			struct StaticMovementComponent
			{
				float m_speed{ -1 };
			};

			struct DynamicDirectionComponent
			{
				b2Vec2 m_direction{ b2Vec2_zero }; // vector for the x and y component
				float m_movementPercentage{ -1.0f };
			};

			struct StaticDirectionComponent
			{
			};

			struct DynamicRenderComponent
			{
				SDL_Rect m_srcRect; // location on sprite sheet
				SDL_Rect m_dstRect; // location in world
				SDL_Rect m_healthBarRect;
				float m_angle{ -1.0f }; // direction of texture
			};

			struct StaticRenderComponent
			{
				int m_textureWidth{ 0 };
				int m_textureHeight{ 0 };
				SDL_Texture* m_entityTexture{ nullptr }; // not an animation surface
				SDL_Texture* m_healthBarTexture{ nullptr };
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
