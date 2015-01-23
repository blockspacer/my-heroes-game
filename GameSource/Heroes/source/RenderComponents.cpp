
#include <iostream>
#include <algorithm>
#include "Engine/Log.h"
#include "States/GamePlayState/Entities/RenderComponents.h"
#include "States/GamePlayState/b2Conversion.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			RenderComponents::RenderComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicRenderComponent, StaticRenderComponent>(entityMemory) {}
			RenderComponents::~RenderComponents() {}

			// getters and setters

			SDL_Rect* RenderComponents::GetDestinationRect_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return &m_dynamicComponents[entityDynamicID].m_dstRect;
			}

			SDL_Rect* RenderComponents::GetSourceRect_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return &m_dynamicComponents[entityDynamicID].m_srcRect;
			}

			SDL_Rect* RenderComponents::GetStatusRect_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return &m_dynamicComponents[entityDynamicID].m_statusRect;
			}

			float RenderComponents::GetAngle_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_angle;
			}

			void RenderComponents::SetAngle_D(int entityDynamicID, float angle)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_angle = angle;
			}

			SDL_Texture* RenderComponents::GetStatusTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_statusTexture;
			}

			void RenderComponents::SetStatusTexture_S(int entityStaticID, SDL_Texture* statusTexture)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_statusTexture = statusTexture;
			}

			void RenderComponents::UpdateEntityRenderComponent(int dynamicEntityID, Camera& camera, SDL_Window* window)
			{
				// 1) Get some useful data for calculating render rectangles

				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(window, &displayMode);

				EntityStaticIDType staticID = m_entityMemory.m_statusComponents.GetStaticEntityID_D(dynamicEntityID);
				b2Vec2 cameraLocation = camera.GetSimCenter();
				b2Vec2 entitylocation = m_entityMemory.m_physicsComponents.GetEntityBody_D(dynamicEntityID)->GetPosition();
				b2Vec2 entityOrientation = m_entityMemory.m_AIComponents.GetOrientation_D(dynamicEntityID);

				// determine the static data

				int staticFrames = 0;
				int staticAnimationFrameSize = 0;
				int staticAnimationTimeMilli = 0;
				SDL_Texture* animationTexture = nullptr;

				if (m_entityMemory.m_statusComponents.GetBusyStatus_D(dynamicEntityID) == BusyStatusType::NONE)
				{
					// idle animations
					if (m_entityMemory.m_statusComponents.GetIdleStatus_D(dynamicEntityID) == IdleStatusType::STANDING)
					{
						staticFrames = m_staticComponents[staticID].m_standingFrames;
						staticAnimationTimeMilli = m_staticComponents[staticID].m_standingAnimationTimeMilli;
						staticAnimationFrameSize = m_staticComponents[staticID].m_standingFrameSize;
						animationTexture = m_staticComponents[staticID].m_standingFramesTexture;
					}
					else if (m_entityMemory.m_statusComponents.GetIdleStatus_D(dynamicEntityID) == IdleStatusType::MOVING)
					{
						staticFrames = m_staticComponents[staticID].m_movingFrames;
						staticAnimationTimeMilli = m_staticComponents[staticID].m_movingAnimationTimeMilli;
						staticAnimationFrameSize = m_staticComponents[staticID].m_movingFrameSize;
						animationTexture = m_staticComponents[staticID].m_movingFramesTexture;
	
					}

				}
				else
				{
					// busy animations

					// basic animation
					if (m_entityMemory.m_statusComponents.GetBusyStatus_D(dynamicEntityID) == BusyStatusType::BASIC_ATTACK)
					{
						staticFrames = m_staticComponents[staticID].m_basicAttackFrames;
						staticAnimationTimeMilli = m_entityMemory.m_actionComponents.GetNormalAttackSpeed_S(staticID) * 100;
						staticAnimationFrameSize = m_staticComponents[staticID].m_basicAttackFrameSize;
						animationTexture = m_staticComponents[staticID].m_basicAttackFramesTexture;
					}
					else if (m_entityMemory.m_statusComponents.GetBusyStatus_D(dynamicEntityID) == BusyStatusType::DEAD)
					{
						staticFrames = m_staticComponents[staticID].m_basicAttackFrames;
						staticAnimationTimeMilli = m_entityMemory.m_healthComponents.GetDeathTimer_S(staticID) * 100;
						staticAnimationFrameSize = m_staticComponents[staticID].m_basicAttackFrameSize;
						animationTexture = m_staticComponents[staticID].m_basicAttackFramesTexture;
					}
				}

				g_assert(staticFrames > 0);
				g_assert(staticAnimationTimeMilli > 0);
				g_assert(staticAnimationFrameSize > 0);
				g_assert(animationTexture != nullptr);

				// 2) Determine the Destination Rectangle

				SDL_Rect dst;

				// determine pixel location from simulation world
				dst.x = Meter2Pixel(entitylocation.x) - staticAnimationFrameSize / 2;
				dst.y = Meter2Pixel(entitylocation.y) - staticAnimationFrameSize / 2;

				// make relative to the main entities location

				dst.x = dst.x - static_cast<int>(cameraLocation.x * PIXEL_TO_SIM) + displayMode.w / 2;
				dst.y = dst.y - static_cast<int>(cameraLocation.y * PIXEL_TO_SIM) + displayMode.h / 2;

				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->w = staticAnimationFrameSize;
				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->h = staticAnimationFrameSize;
				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->x = dst.x;
				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->y = dst.y;

				// set the orientation of animation
				m_entityMemory.m_renderComponents.SetAngle_D(dynamicEntityID, (atan2(entityOrientation.y, entityOrientation.x)) * (180.0f / static_cast<float>(M_PI)) - 90.0f);

				// 3) Determine the Source Rectangle and Animation

				// animation stuff
				int currentTime = SDL_GetTicks();

				if (m_entityMemory.m_statusComponents.GetBusyStatus_D(dynamicEntityID) == BusyStatusType::NONE)
				{
					// idle 
					if (currentTime - m_dynamicComponents[dynamicEntityID].m_animationTimeMilli >= staticAnimationTimeMilli)
					{
						m_dynamicComponents[dynamicEntityID].m_animationTimeMilli = currentTime;
					}
					m_dynamicComponents[dynamicEntityID].m_busyStartAnimation = true;

				}
				else
				{
					if (m_dynamicComponents[dynamicEntityID].m_busyStartAnimation == true)
					{
						// set the current time to now
						m_dynamicComponents[dynamicEntityID].m_animationTimeMilli = currentTime;
						m_dynamicComponents[dynamicEntityID].m_busyStartAnimation = false;
					}
					else if (currentTime - m_dynamicComponents[dynamicEntityID].m_animationTimeMilli >= staticAnimationTimeMilli)
					{
						//m_dynamicComponents[dynamicEntityID].m_animationTimeMilli = currentTime;
						m_dynamicComponents[dynamicEntityID].m_busyStartAnimation = true;
						return; // busy animation has ended so leave
					}
				}

				

				// frame is not necessary but is helpful for understanding
				m_dynamicComponents[dynamicEntityID].m_frame = std::min(staticFrames - 1, ((currentTime - m_dynamicComponents[dynamicEntityID].m_animationTimeMilli) * staticFrames / staticAnimationTimeMilli));
				m_dynamicComponents[dynamicEntityID].m_srcRect.w = staticAnimationFrameSize;
				m_dynamicComponents[dynamicEntityID].m_srcRect.h = staticAnimationFrameSize;
				m_dynamicComponents[dynamicEntityID].m_srcRect.x = m_dynamicComponents[dynamicEntityID].m_frame * (staticAnimationFrameSize);
				m_dynamicComponents[dynamicEntityID].m_srcRect.y = 0;
				m_dynamicComponents[dynamicEntityID].m_animationTexture = animationTexture;

				// 4) Determine the Status Rectangle

				// this needs to be re though
				float healthPercentage = (m_entityMemory.m_healthComponents.GetNormalHealth_D(dynamicEntityID) * 1.0f) / m_entityMemory.m_healthComponents.GetNormalHealth_S(staticID);
				m_entityMemory.m_renderComponents.GetStatusRect_D(dynamicEntityID)->w = static_cast<int>(staticAnimationFrameSize * healthPercentage);
				m_entityMemory.m_renderComponents.GetStatusRect_D(dynamicEntityID)->x = dst.x;
				m_entityMemory.m_renderComponents.GetStatusRect_D(dynamicEntityID)->y = dst.y - 10;
			}

			int RenderComponents::GetStandingTextureSize_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_standingFrameSize;
			}

			int RenderComponents::GetStandingFrames_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_standingFrames;
			}

			int RenderComponents::GetStandingAnimationTimeMilli_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_standingAnimationTimeMilli;
			}

			SDL_Texture* RenderComponents::GetStandingFramesTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_standingFramesTexture;
			}

			void RenderComponents::SetStandingTextureSize_S(int entityStaticID, int standingTextureSize)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_standingFrameSize = standingTextureSize;
			}

			void RenderComponents::SetStandingFrames_S(int entityStaticID, int standingFrames)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_standingFrames = standingFrames;
			}

			void RenderComponents::SetStandingAnimationTimeMilli_S(int entityStaticID, int standingAnimationTimeMilli)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_standingAnimationTimeMilli = standingAnimationTimeMilli;
			}

			void RenderComponents::SetStandingFramesTexture_S(int entityStaticID, SDL_Texture* standingFramesTexture)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_standingFramesTexture = standingFramesTexture;
			}

			int RenderComponents::GetFrame_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_frame;
			}

			void RenderComponents::SetFrame_D(int entityDynamicID, int frame)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_frame = frame;
			}

			int RenderComponents::GetAnimationTimeMilli_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_animationTimeMilli;
			}

			void RenderComponents::SetAnimationTimeMilli_D(int entityDynamicID, int animationTimeMilli)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_animationTimeMilli = animationTimeMilli;
			}

			SDL_Texture* RenderComponents::GetAnimationTexture_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_animationTexture;
			}

			int RenderComponents::GetMovingTextureSize_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movingFrameSize;
			}

			int RenderComponents::GetMovingFrames_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movingFrames;
			}

			int RenderComponents::GetMovingAnimationTimeMilli_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movingAnimationTimeMilli;
			}

			SDL_Texture* RenderComponents::GetMovingFramesTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movingFramesTexture;
			}

			void RenderComponents::SetMovingTextureSize_S(int entityStaticID, int movingTextureSize)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movingFrameSize = movingTextureSize;
			}

			void RenderComponents::SetMovingFrames_S(int entityStaticID, int movingFrames)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movingFrames = movingFrames;
			}

			void RenderComponents::SetMovingAnimationTimeMilli_S(int entityStaticID, int movingAnimationTimeMilli)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movingAnimationTimeMilli = movingAnimationTimeMilli;
			}

			void RenderComponents::SetMovingFramesTexture_S(int entityStaticID, SDL_Texture* movingFramesTexture)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movingFramesTexture = movingFramesTexture;
			}

			int RenderComponents::GetBasicAttackTextureSize_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_basicAttackFrameSize;
			}

			int RenderComponents::GetBasicAttackFrames_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_basicAttackFrames;
			}

			SDL_Texture* RenderComponents::GetBasicAttackFramesTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_basicAttackFramesTexture;
			}

			void RenderComponents::SetBasicAttackTextureSize_S(int entityStaticID, int basicAttackTextureSize)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_basicAttackFrameSize = basicAttackTextureSize;
			}

			void RenderComponents::SetBasicAttackFrames_S(int entityStaticID, int basicAttackFrames)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_basicAttackFrames = basicAttackFrames;
			}

			void RenderComponents::SetBasicAttackFramesTexture_S(int entityStaticID, SDL_Texture* basicAttackFramesTextures)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_basicAttackFramesTexture = basicAttackFramesTextures;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes