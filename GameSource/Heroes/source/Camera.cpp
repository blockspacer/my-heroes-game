#pragma once

#include "Engine/Log.h"

#include "States/GamePlayState/Camera.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			Camera::Camera(const b2Vec2& cameraFollow)
			{
				m_cameraFollow = cameraFollow;
				g_Log_Write_L1(LOG_CONSTRUCTION_EVENT, "Constructed GamePlay Camera");
			}

			Camera::~Camera()
			{
				g_Log_Write_L1(LOG_DESTRUCTION_EVENT, "Destructed GamePlay Camera");
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

				zone.lowerBound = b2Vec2(m_cameraFollow.x - (displayMode.w / (2.0f * ConversionScale::PIXEL_TO_SIM)) - CameraVisionError::ERROR_IN_METERS,
					m_cameraFollow.y - (displayMode.h / (2.0f * ConversionScale::PIXEL_TO_SIM)) - CameraVisionError::ERROR_IN_METERS);
				
				zone.upperBound = b2Vec2(m_cameraFollow.x + (displayMode.w / (2.0f * ConversionScale::PIXEL_TO_SIM)) + CameraVisionError::ERROR_IN_METERS,
					m_cameraFollow.y + (displayMode.h / (2.0f * ConversionScale::PIXEL_TO_SIM)) + CameraVisionError::ERROR_IN_METERS);
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
