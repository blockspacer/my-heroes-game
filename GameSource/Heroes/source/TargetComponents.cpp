#pragma once

#include <Box2D/Box2D.h>
#include "States/GamePlayState/Entities/TargetComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			TargetComponents::TargetComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicTargetComponent, StaticTargetComponent>(entityMemory) {}
			TargetComponents::~TargetComponents() {}

			// DYNAMIC GETTERS AND SETTERS

			// STATIC GETTERS

			// UTILITY FUNCTIONS			

			// STATIC SETTERS

			b2Shape* TargetComponents::GetLargeSightShape_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_largeSightShape;
			}

			void TargetComponents::SetLargeSightShape_D(int entityDynamicID, b2Shape* largeSightShape)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_largeSightShape = largeSightShape;
			}

			b2Shape* TargetComponents::GetSmallSightShape_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_smallSightShape;
			}

			void TargetComponents::SetSmallSightShape_D(int entityDynamicID, b2Shape* smallSightShape)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_smallSightShape = smallSightShape;
			}

			b2Body* TargetComponents::GetVisionBody_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_visionBody;
			}

			void TargetComponents::SetSmallSightShape_D(int entityDynamicID, b2Body* visionBody)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_visionBody = visionBody;
			}

			int TargetComponents::GetTarget_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_target;
			}

			void TargetComponents::SetTarget_D(int entityDynamicID, int target)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_target = target;
			}

			float TargetComponents::GetTargetDistance_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_targetDistance;
			}

			void TargetComponents::SetTargetDistance_D(int entityDynamicID, float targetDistance)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targetDistance = targetDistance;
			}

			b2Vec2 TargetComponents::GetOrientation_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation;
			}

			void TargetComponents::SetOrientation_D(int entityDynamicID, b2Vec2 orientation)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_orientation = orientation;
			}

			b2FixtureDef TargetComponents::GetLargeSightDef_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_largeSightFixDef;
			}

			void TargetComponents::SetLargeSightDef_S(int entityStaticID, b2FixtureDef largeSightDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_largeSightFixDef = largeSightDef;
			}

			b2FixtureDef TargetComponents::GetSmallSightDef_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_smallSightFixDef;
			}

			void TargetComponents::SetSmallSightDef_S(int entityStaticID, b2FixtureDef smallSightDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_smallSightFixDef = smallSightDef;
			}

			float TargetComponents::GetTrackingRange_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_trackingRange;
			}

			void TargetComponents::SetTrackingRange_S(int entityStaticID, float trackingRange)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_trackingRange = trackingRange;
			}

			float TargetComponents::GetOrientationX_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation.x;
			}

			float TargetComponents::GetOrientationY_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation.y;
			}

			void TargetComponents::SetOrientation_D(int entityDynamicID, float x, float y)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_orientation.x = x;
				m_dynamicComponents[entityDynamicID].m_orientation.y = y;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes