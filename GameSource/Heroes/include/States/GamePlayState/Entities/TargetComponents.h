#pragma once

#include <Box2D/Box2D.h>
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicTargetComponent final
			{
				int m_target{ -1 };
				float m_targetDistance{ -1.0f };

				// vision cones
				b2Body* m_visionBody{ nullptr };
				b2Shape* m_smallSightShape{ nullptr };
				b2Shape* m_largeSightShape{ nullptr };

				// direction that this entity is facing
				b2Vec2 m_orientation;
			};

			struct StaticTargetComponent final
			{
				float m_trackingRange{ -1.0f };
				b2FixtureDef m_smallSightFixDef;
				b2FixtureDef m_largeSightFixDef;
			};

			class TargetComponents : public ComponentsContainer<DynamicTargetComponent, StaticTargetComponent>
			{
			public:
				TargetComponents(EntityMemory& entityMemory);
				virtual ~TargetComponents();

				// DYNAMIC GETTERS AND SETTERS

				b2Shape* GetLargeSightShape_D(int entityDynamicID);

				void SetLargeSightShape_D(int entityDynamicID, b2Shape* largeSightShape);

				b2Shape* GetSmallSightShape_D(int entityDynamicID);

				void SetSmallSightShape_D(int entityDynamicID, b2Shape* smallSightShape);

				b2Body* GetVisionBody_D(int entityDynamicID);

				void SetSmallSightShape_D(int entityDynamicID, b2Body* visionBody);

				int GetTarget_D(int entityDynamicID);

				void SetTarget_D(int entityDynamicID, int target);

				float GetTargetDistance_D(int entityDynamicID);

				void SetTargetDistance_D(int entityDynamicID, float targetDistance);

				b2Vec2 GetOrientation_D(int entityDynamicID);

				void SetOrientation_D(int entityDynamicID, b2Vec2 orientation);

				// STATIC GETTERS

				b2FixtureDef GetLargeSightDef_S(int entityStaticID);

				b2FixtureDef GetSmallSightDef_S(int entityStaticID);

				float GetTrackingRange_S(int entityStaticID);

				// UTILITY FUNCTIONS			

				float GetOrientationX_D(int entityDynamicID);

				float GetOrientationY_D(int entityDynamicID);

				void SetOrientation_D(int entityDynamicID, float x, float y);

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetLargeSightDef_S(int entityStaticID, b2FixtureDef largeSightDef);

				void SetSmallSightDef_S(int entityStaticID, b2FixtureDef smallSightDef);

				void SetTrackingRange_S(int entityStaticID, float trackingRange);
				
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes