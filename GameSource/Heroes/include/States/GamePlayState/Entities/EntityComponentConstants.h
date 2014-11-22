#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{


			enum EntityCollisionMasks
			{
				ALLY_BODY = 0x0001,
				ALLY_SENSOR = 0x0002,
				ENEMY_BODY = 0x0004,
				ENEMY_SENSOR = 0x0008,
				ENVIRONMENT_BODY = 0x0010,
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




		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
