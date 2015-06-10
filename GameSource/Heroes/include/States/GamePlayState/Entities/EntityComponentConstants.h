// Heroes Game
// Author: Samuel Hall
// Last Commented 1/30/2015

#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			/*
			 * These are the types of bodies that the Heroes game
			 * provides. They are used to decribe all objects in the 
			 * game simulation and also determine how collisions work (below).
			 * When a b2body is created it needs to have one and only one of the
			 * below types assigned to it.
			 */
			enum EntityCollisionMasks
			{
				ALLY_BODY = 0x0001,
				ALLY_SENSOR = 0x0002,
				ENEMY_BODY = 0x0004,
				ENEMY_SENSOR = 0x0008,
				ENVIRONMENT_BODY = 0x0010,
				ENVIRONMENT_SENSOR = 0x0020
				
				
			};

			/*
			* These are the collision catergories for the game body
			* types. They determine what other bodies collide with them within
			* the box2d code. For example all the body types should collide with other
			* body types since they should not occupy the same space. The sensors are more
			* complicated, they should only collide with things that the are potential targets.
			* So for example the all sensor should only collide with enemy bodies. Again
			* when a b2body is created it needs to have one and only one of the
			* below types assigned to it.
			*/
			enum EntityCollisionCategories
			{
				ALLY_BODY_COL = ALLY_BODY | ENEMY_BODY | ENEMY_SENSOR | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
				ALLY_SENSOR_COL = ENEMY_BODY,
				ENEMY_BODY_COL = ALLY_BODY | ALLY_SENSOR | ENEMY_BODY | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR,
				ENEMY_SENSOR_COL = ALLY_BODY,
				ENVIRONMENT_BODY_COL = ALLY_BODY | ENEMY_BODY | ENVIRONMENT_BODY,
				ENVIRONMENT_SENSOR_COL = ALLY_BODY | ENEMY_BODY
			};




		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
