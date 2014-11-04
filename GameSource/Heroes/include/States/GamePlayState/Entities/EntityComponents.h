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
			enum EntityBodyCategories
			{
				ENVIRONMENT_BODY = 0x0001,
				ALLY_SENSOR = 0x0002,
				ENEMY_BODY = 0x0004,
				ENEMY_SENSOR = 0x0008,
				ALLY_BODY = 0x0010,
				ENVIRONMENT_SENSOR = 0x0020
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

					struct ComponentSystems
					{
						GamePlay::SystemFunc m_statusSystem;
						GamePlay::SystemFunc m_healthSystem;
						GamePlay::SystemFunc m_targetSystem;
						GamePlay::SystemFunc m_actionSystem;
						GamePlay::SystemFunc m_directionSystem;
						GamePlay::SystemFunc m_movementSystem;
						GamePlay::SystemFunc m_renderUpdateSystem;
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

					// DEAD SYSTEM
					struct ComponentStatus
					{
						ActionType m_action; // whether entity is actively doing something (busy)
						MovementType m_movement;
						StatusType m_status; // whether entity is dead
						int m_countDownBase; // max death count down
						int m_countDownCurrent; // amount until this entity should be cleaned up
					};

					// HEALTH SYSTEM
					// ACTION SYSTEM
					struct ComponentHealth
					{
						// health
						int m_healthNormalBase;
						int m_healthNormalCurrent;

						int m_damageDirect;
						int m_damageDirectSource;

						int m_resistanceNormalBase;
					};

					

					// TARGET SYSTEM
					struct ComponentTarget {
						int target;
						float targetDistance;
						float trackingRange;

						// vision cones
						b2Joint* connectionJoint; // not sure why this is here don't delete
						b2Body* visionBody;
						b2Shape* smallSightShape;
						b2FixtureDef smallSightFixDef;
						b2Shape* largeSightShape;
						b2FixtureDef largeSightFixDef;

						// direction that this entity is facing
						b2Vec2 m_orientation;
					};

					// ACTION SYSTEM
					struct ComponentAction
					{
						int m_normalBase;
					};

					// PHYSICS data not needed by a system
					struct ComponentPhysics{
						b2Body* body; // single body of the entity
						std::list<b2Shape*> shapes; // number of shapes that make up the entity
					};

					// MOVEMENT SYSTEM
					// ACTION SYSTEM
					struct ComponentMovement{
						float m_baseMax;
					};

					struct ComponentDirection{
						b2Vec2 m_direction; // vector for the x and y component
						float m_movementPercentage;
					};

					struct ComponentRender {
						SDL_Texture* m_texture; // not an animation surface
						SDL_Rect m_srcRect;
						SDL_Rect m_dstRect;
						float m_angle;
					};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
