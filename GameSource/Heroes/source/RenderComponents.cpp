
#include "States/GamePlayState/Entities/RenderComponents.h"
#include "States/GamePlayState/b2Conversion.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			RenderComponents::RenderComponents(EntityMemory& entityMemory, SDL_Window* window) : ComponentsContainer<DynamicRenderComponent, StaticRenderComponent>(entityMemory),
																								 m_window(window) {}
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

			SDL_Rect* RenderComponents::GetHealthBarRect_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return &m_dynamicComponents[entityDynamicID].m_healthBarRect;
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



			int RenderComponents::GetTextureWidth_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_textureWidth;
			}

			void RenderComponents::SetTextureWidth_S(int entityStaticID, int textureWidth)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_textureWidth = textureWidth;
			}

			int RenderComponents::GetTextureHeight_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_textureHeight;
			}

			void RenderComponents::SetTextureHeight_S(int entityStaticID, int textureHeight)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_textureHeight = textureHeight;
			}

			SDL_Texture* RenderComponents::GetEntityTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_entityTexture;
			}

			void RenderComponents::SetEntityTexture_S(int entityStaticID, SDL_Texture* entityTexture)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_entityTexture = entityTexture;
			}

			SDL_Texture* RenderComponents::GetHealthBarTexture_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_healthBarTexture;
			}

			void RenderComponents::SetHealthBarTexture_S(int entityStaticID, SDL_Texture* healthBarTexture)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_healthBarTexture = healthBarTexture;
			}

			void RenderComponents::UpdateEntityRenderComponent(int dynamicEntityID)
			{
				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(m_window, &displayMode);

				EntityStaticIDType staticID = m_entityMemory.m_statusComponents.GetStaticEntityID_D(dynamicEntityID);
				b2Vec2 mainEntitylocation = m_entityMemory.m_physicsComponents.GetEntityBody_D(m_entityMemory.GetMainEntityDynamicID())->GetPosition();
				b2Vec2 location = m_entityMemory.m_physicsComponents.GetEntityBody_D(dynamicEntityID)->GetPosition();
				SDL_Rect dst;

				// determine pixel location from simulation world
				dst.x = Meter2Pixel(location.x) - m_entityMemory.m_renderComponents.GetTextureWidth_S(staticID);
				dst.y = Meter2Pixel(location.y) - m_entityMemory.m_renderComponents.GetTextureHeight_S(staticID);

				// make relative to the main entities location

				dst.x = dst.x - static_cast<int>(mainEntitylocation.x * PIXEL_TO_METER) + displayMode.w / 2;
				dst.y = dst.y - static_cast<int>(mainEntitylocation.y * PIXEL_TO_METER) + displayMode.h / 2;

				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->x = dst.x;
				m_entityMemory.m_renderComponents.GetDestinationRect_D(dynamicEntityID)->y = dst.y;

				// set health bar coordinates
				m_entityMemory.m_healthComponents.SetNormalHealth_D(dynamicEntityID, (m_entityMemory.m_healthComponents.GetNormalHealth_D(dynamicEntityID) + 1) % m_entityMemory.m_healthComponents.GetNormalHealth_S(staticID));
				float healthPercentage = (m_entityMemory.m_healthComponents.GetNormalHealth_D(dynamicEntityID) * 1.0f) / m_entityMemory.m_healthComponents.GetNormalHealth_S(staticID);
				m_entityMemory.m_renderComponents.GetHealthBarRect_D(dynamicEntityID)->w = static_cast<int>(m_entityMemory.m_renderComponents.GetTextureWidth_S(staticID) * healthPercentage);
				m_entityMemory.m_renderComponents.GetHealthBarRect_D(dynamicEntityID)->x = dst.x;
				m_entityMemory.m_renderComponents.GetHealthBarRect_D(dynamicEntityID)->y = dst.y - 10;

				b2Vec2 orientation = m_entityMemory.m_targetComponents.GetOrientation_D(dynamicEntityID);
				m_entityMemory.m_renderComponents.SetAngle_D(dynamicEntityID, (atan2(orientation.y, orientation.x)) * (180.0f / static_cast<float>(M_PI)) - 90.0f);
			}


		} // namespace GamePlay
	} // namespace States
} //namespace Heroes