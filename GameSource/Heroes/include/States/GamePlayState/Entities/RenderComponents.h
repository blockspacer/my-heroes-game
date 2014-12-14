#pragma once

#include <SDL.h>
#include "States/GamePlayState/Camera.h"
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			enum AnimationType
			{
				STANDING_ANIMATION,
				MOVING_ANIMATION
			};


			struct DynamicRenderComponent final
			{
				SDL_Rect m_srcRect; // location on sprite sheet
				SDL_Rect m_dstRect; // location in world

				int m_frame{ 0 };
				int m_animationTimeMilli{ 0 };
				SDL_Texture* m_animationTexture{ nullptr };

				float m_angle{ -1.0f }; // direction of texture

				bool m_busyStartAnimation{ true };

				SDL_Rect m_statusRect;
			};

			struct StaticRenderComponent final
			{
				// new texture stuff
				int m_standingFrameSize{ 0 };
				int m_standingFrames{ 0 };
				int m_standingAnimationTimeMilli{ 0 };
				SDL_Texture* m_standingFramesTexture{ nullptr };

				int m_movingFrameSize{ 0 };
				int m_movingFrames{ 0 };
				int m_movingAnimationTimeMilli{ 0 };
				SDL_Texture* m_movingFramesTexture{ nullptr };

				int m_basicAttackFrameSize{ 0 };
				int m_basicAttackFrames{ 0 };
				SDL_Texture* m_basicAttackFramesTexture{ nullptr };

				SDL_Texture* m_statusTexture{ nullptr };
			};

			class RenderComponents final : ComponentsContainer<DynamicRenderComponent, StaticRenderComponent>
			{
			public:

				RenderComponents(EntityMemory& entityMemory);
				virtual ~RenderComponents();
				
				// DYNAMIC GETTERS AND SETTERS

				SDL_Rect* GetDestinationRect_D(int entityDynamicID);

				SDL_Rect* GetSourceRect_D(int entityDynamicID);

				SDL_Rect* GetStatusRect_D(int entityDynamicID);

				float GetAngle_D(int entityDynamicID);

				void SetAngle_D(int entityDynamicID, float angle);

				// animation stuff

				int GetFrame_D(int entityDynamicID);
				void SetFrame_D(int entityDynamicID, int frame);
				int GetAnimationTimeMilli_D(int entityDynamicID);
				void SetAnimationTimeMilli_D(int entityDynamicID, int animationTimeMilli);
				SDL_Texture* GetAnimationTexture_D(int entityDynamicID);

				// STATIC GETTERS

				SDL_Texture* GetStatusTexture_S(int entityStaticID);

				// new animation functions

				int GetStandingTextureSize_S(int entityStaticID);
				int GetStandingFrames_S(int entityStaticID);
				int GetStandingAnimationTimeMilli_S(int entityStaticID);
				SDL_Texture* GetStandingFramesTexture_S(int entityStaticID);

				int GetMovingTextureSize_S(int entityStaticID);
				int GetMovingFrames_S(int entityStaticID);
				int GetMovingAnimationTimeMilli_S(int entityStaticID);
				SDL_Texture* GetMovingFramesTexture_S(int entityStaticID);

				int GetBasicAttackTextureSize_S(int entityStaticID);
				int GetBasicAttackFrames_S(int entityStaticID);
				SDL_Texture* GetBasicAttackFramesTexture_S(int entityStaticID);

				// UTILITY FUNCTIONS

				void UpdateEntityRenderComponent(int dynamicEntityID, Camera& camera, SDL_Window* window);
			
			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetStatusTexture_S(int entityStaticID, SDL_Texture* statusTexture);

				// new animation

				void SetStandingTextureSize_S(int entityStaticID, int standingTextureSize);
				void SetStandingFrames_S(int entityStaticID, int standingFrames);
				void SetStandingAnimationTimeMilli_S(int entityStaticID, int standingAnimationTimeMilli);
				void SetStandingFramesTexture_S(int entityStaticID, SDL_Texture* standingFramesTextures);

				void SetMovingTextureSize_S(int entityStaticID, int movingTextureSize);
				void SetMovingFrames_S(int entityStaticID, int movingFrames);
				void SetMovingAnimationTimeMilli_S(int entityStaticID, int movingAnimationTimeMilli);
				void SetMovingFramesTexture_S(int entityStaticID, SDL_Texture* movingFramesTextures);

				void SetBasicAttackTextureSize_S(int entityStaticID, int basicAttackTextureSize);
				void SetBasicAttackFrames_S(int entityStaticID, int basicAttackFrames);
				void SetBasicAttackFramesTexture_S(int entityStaticID, SDL_Texture* basicAttackFramesTextures);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes