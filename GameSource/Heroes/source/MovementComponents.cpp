#pragma once

#include "States/GamePlayState/Entities/MovementComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			MovementComponents::MovementComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicMovementComponent, StaticMovementComponent>(entityMemory) {}

			MovementComponents::~MovementComponents() {}

			float MovementComponents::GetMovementSpeed_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movementSpeed;
			}

			void MovementComponents::SetMovementSpeed_S(int entityStaticID, float movementSpeed)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movementSpeed = movementSpeed;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes