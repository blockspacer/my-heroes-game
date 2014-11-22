#pragma once

#include <SDL.h>
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicRenderComponent final
			{
				SDL_Rect m_srcRect; // location on sprite sheet
				SDL_Rect m_dstRect; // location in world
				SDL_Rect m_healthBarRect;
				float m_angle{ -1.0f }; // direction of texture
			};

			struct StaticRenderComponent final
			{
				int m_textureWidth{ 0 };
				int m_textureHeight{ 0 };
				SDL_Texture* m_entityTexture{ nullptr }; // not an animation surface
				SDL_Texture* m_healthBarTexture{ nullptr };
			};

			class RenderComponents final : ComponentsContainer<DynamicRenderComponent, StaticRenderComponent>
			{
			public:

				RenderComponents(EntityMemory& entityMemory, SDL_Window* window);
				virtual ~RenderComponents();
				
				// DYNAMIC GETTERS AND SETTERS

				SDL_Rect* GetDestinationRect_D(int entityDynamicID);

				SDL_Rect* GetSourceRect_D(int entityDynamicID);

				SDL_Rect* GetHealthBarRect_D(int entityDynamicID);

				float GetAngle_D(int entityDynamicID);

				void SetAngle_D(int entityDynamicID, float angle);

				// STATIC GETTERS

				int GetTextureWidth_S(int entityStaticID);

				int GetTextureHeight_S(int entityStaticID);

				SDL_Texture* GetEntityTexture_S(int entityStaticID);

				SDL_Texture* GetHealthBarTexture_S(int entityStaticID);				

				// UTILITY FUNCTIONS

				void UpdateEntityRenderComponent(int dynamicEntityID);
			
			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetTextureWidth_S(int entityStaticID, int textureWidth);

				void SetTextureHeight_S(int entityStaticID, int textureHeight);

				void SetEntityTexture_S(int entityStaticID, SDL_Texture* entityTexture);

				void SetHealthBarTexture_S(int entityStaticID, SDL_Texture* healthBarTexture);

			

				SDL_Window* m_window;
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes