#pragma once

#include <unordered_set>

#include <Box2D/Box2D.h>
#include "States/GamePlayState/Entities/EntityTargetMap.h"
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicTargetComponent
			{
				EntityTargetMap m_targets{ DistanceValue };
				//int m_target{ -1 };
				float m_targetDistance{ -1.0f };

				// direction that this entity is facing
				b2Vec2 m_orientation;
				b2Vec2 m_direction{ b2Vec2_zero }; // vector for the x and y component
				float m_movementPercentage{ -1.0f };
			};

			struct StaticTargetComponent final
			{
				float m_trackingRange{ -1.0f };
			};

			class AIComponents : public ComponentsContainer<DynamicTargetComponent, StaticTargetComponent>
			{
			public:
				AIComponents(EntityMemory& entityMemory);
				virtual ~AIComponents();

				// DYNAMIC GETTERS AND SETTERS

				void AddTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory);

				void RemoveTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory);

				int GetTarget_D(int entityDynamicID, EntityMemory& entityMemory);

				void SwitchTargets_D(int entityDynamicID, EntityMemory& entityMemory);

				void SwitchToTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory);

				float GetTargetDistance_D(int entityDynamicID);

				void SetTargetDistance_D(int entityDynamicID, float targetDistance);

				b2Vec2 GetOrientation_D(int entityDynamicID);

				void SetOrientation_D(int entityDynamicID, b2Vec2 orientation);

				void SetTargetMapSource_D(int entityDynamicID);

				// STATIC GETTERS

				float GetTrackingRange_S(int entityStaticID);

				// UTILITY FUNCTIONS			

				float GetOrientationX_D(int entityDynamicID);

				float GetOrientationY_D(int entityDynamicID);

				void SetOrientation_D(int entityDynamicID, float x, float y);

				b2Vec2 GetDirection_D(int entityDynamicID);

				void SetDirection_D(int entityDynamicID, b2Vec2 direction);

				float GetMovementPercentage_D(int entityDynamicID);

				void SetMovementPercentage_D(int entityDynamicID, float movementPercentage);

				// STATIC GETTERS

				// UTILITY FUNCTIONS			

				float GetDirectionX_D(int entityDynamicID);

				float GetDirectionY_D(int entityDynamicID);

				void SetDirection_D(int entityDynamicID, float x, float y);

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetTrackingRange_S(int entityStaticID, float trackingRange);
				
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes