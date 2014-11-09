#pragma once

#include <SDL_video.h>
#include <Box2D/Box2D.h>

#include "States/GamePlayState/b2Conversion.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			enum CameraActiveRegion
			{
				ACTIVE_AREA_METER_WIDTH = 48,
				ACTIVE_AREA_METER_HEIGHT = 48
			};

			enum CameraVisionError
			{
				ERROR_IN_METERS = 5
			};

			/*
			 * This class represents the camera of the game, more specifically it represents the 
			 * "active" region of the game and does not have any relation to the size of the screen.
			 */
			class Camera final
			{
			public:

				Camera(const b2Vec2& cameraFollow);
				~Camera();

				void SetCameraFollow(const b2Vec2& cameraFollow);
				void GetActiveZone(b2AABB& zone);
				void GetVisionZone(b2AABB& zone, SDL_Window* window);
				b2Vec2 GetSimCenter() { return m_cameraFollow; }

			private:

				b2Vec2 m_cameraFollow{ b2Vec2_zero };
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
