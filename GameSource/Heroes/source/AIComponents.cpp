#pragma once

#include <Box2D/Box2D.h>

#include "Engine/Log.h"
#include "States/GamePlayState/Entities/AIComponents.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

#include <iostream>

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			AIComponents::AIComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicTargetComponent, StaticTargetComponent>(entityMemory) {}
			AIComponents::~AIComponents() {}

			void AIComponents::AddTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory)
			{
				CheckDynamicEntityID(entityDynamicID);
				CheckDynamicEntityID(target);
				if (entityDynamicID != target) // have a contains method
				{
					m_dynamicComponents[entityDynamicID].m_targets.AddTargetFront(target, entityMemory);
				}			
			}

			void AIComponents::RemoveTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory)
			{
				CheckDynamicEntityID(entityDynamicID);
				CheckDynamicEntityID(target);
				if (entityDynamicID != target) // add contains check
				{
					m_dynamicComponents[entityDynamicID].m_targets.RemoveTarget(target);
				}
			}

			void AIComponents::SwitchTargets_D(int entityDynamicID, EntityMemory& entityMemory)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targets.SwitchTargets(entityMemory);
				//m_dynamicComponents[entityDynamicID].m_target = m_dynamicComponents[entityDynamicID].m_targets.GetTargetFront();
			}

			void AIComponents::SwitchToTarget_D(int entityDynamicID, int target, EntityMemory& entityMemory)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targets.SwitchToTarget(target, entityMemory);
			}

			int AIComponents::GetTarget_D(int entityDynamicID, EntityMemory& entityMemory)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_targets.GetTarget(entityMemory);
			}

			float AIComponents::GetTargetDistance_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_targetDistance;
			}

			void AIComponents::SetTargetDistance_D(int entityDynamicID, float targetDistance)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targetDistance = targetDistance;
			}

			b2Vec2 AIComponents::GetOrientation_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation;
			}

			void AIComponents::SetOrientation_D(int entityDynamicID, b2Vec2 orientation)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_orientation = orientation;
			}

			float AIComponents::GetTrackingRange_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_trackingRange;
			}

			void AIComponents::SetTrackingRange_S(int entityStaticID, float trackingRange)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_trackingRange = trackingRange;
			}

			float AIComponents::GetOrientationX_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation.x;
			}

			float AIComponents::GetOrientationY_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_orientation.y;
			}

			void AIComponents::SetOrientation_D(int entityDynamicID, float x, float y)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_orientation.x = x;
				m_dynamicComponents[entityDynamicID].m_orientation.y = y;
			}

			void AIComponents::SetTargetMapSource_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targets.SetSourceEntity(entityDynamicID);
			}

			b2Vec2 AIComponents::GetDirection_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction;
			}

			void AIComponents::SetDirection_D(int entityDynamicID, b2Vec2 direction)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_direction = direction;
			}

			float AIComponents::GetMovementPercentage_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_movementPercentage;
			}

			void AIComponents::SetMovementPercentage_D(int entityDynamicID, float movementPercentage)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_movementPercentage = movementPercentage;
			}

			float AIComponents::GetDirectionX_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction.x;
			}

			float AIComponents::GetDirectionY_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction.y;
			}

			void AIComponents::SetDirection_D(int entityDynamicID, float x, float y)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_direction.x = x;
				m_dynamicComponents[entityDynamicID].m_direction.y = y;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes