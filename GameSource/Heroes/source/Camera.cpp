#pragma once

#include <SDL_assert.h>

#include "Engine/Log.h"

#include "States/GamePlayState/Camera.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			Camera::Camera()
			{
				Engine::g_Log_Write_L1("Constructed GamePlay Camera");
			}

			Camera::Camera(const b2Vec2& cameraFollow)
			{
				m_cameraFollow = cameraFollow;
			}

			Camera::~Camera()
			{
				Engine::g_Log_Write_L1("Destructed GamePlay Camera");
			}

			void Camera::SetCameraFollow(const b2Vec2& cameraFollow)
			{
				m_cameraFollow = cameraFollow;
			}

			void Camera::GetActiveZone(b2AABB& zone)
			{

				zone.lowerBound = b2Vec2(m_cameraFollow.x - CameraActiveRegion::ACTIVE_AREA_METER_WIDTH / 2.0f,
					m_cameraFollow.y - CameraActiveRegion::ACTIVE_AREA_METER_HEIGHT / 2.0f);
			
				zone.upperBound = b2Vec2(m_cameraFollow.x + CameraActiveRegion::ACTIVE_AREA_METER_WIDTH / 2.0f,
					m_cameraFollow.y + CameraActiveRegion::ACTIVE_AREA_METER_HEIGHT / 2.0f);
			
			}

			void Camera::GetVisionZone(b2AABB& zone, SDL_Window* window)
			{

				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(window, &displayMode);

				zone.lowerBound = b2Vec2(m_cameraFollow.x - (displayMode.w / (2.0f * ConversionScale::PIXEL_TO_METER)) - CameraVisionError::ERROR_IN_METERS,
					m_cameraFollow.y - (displayMode.h / (2.0f * ConversionScale::PIXEL_TO_METER)) - CameraVisionError::ERROR_IN_METERS);
				
				zone.upperBound = b2Vec2(m_cameraFollow.x + (displayMode.w / (2.0f * ConversionScale::PIXEL_TO_METER)) + CameraVisionError::ERROR_IN_METERS,
					m_cameraFollow.y + (displayMode.h / (2.0f * ConversionScale::PIXEL_TO_METER)) + CameraVisionError::ERROR_IN_METERS);
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
