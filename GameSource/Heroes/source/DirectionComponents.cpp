#pragma once

#include "States/GamePlayState/Entities/DirectionComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			DirectionComponents::DirectionComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicDirectionComponent, StaticDirectionComponent>(entityMemory) {}

			DirectionComponents::~DirectionComponents() {}

			b2Vec2 DirectionComponents::GetDirection_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction;
			}

			void DirectionComponents::SetDirection_D(int entityDynamicID, b2Vec2 direction)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_direction = direction;
			}

			float DirectionComponents::GetMovementPercentage_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_movementPercentage;
			}

			void DirectionComponents::SetMovementPercentage_D(int entityDynamicID, float movementPercentage)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_movementPercentage = movementPercentage;
			}

			float DirectionComponents::GetDirectionX_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction.x;
			}

			float DirectionComponents::GetDirectionY_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_direction.y;
			}

			void DirectionComponents::SetDirection_D(int entityDynamicID, float x, float y)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_direction.x = x;
				m_dynamicComponents[entityDynamicID].m_direction.y = y;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes