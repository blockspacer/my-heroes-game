#pragma once

#include "States/GamePlayState/Entities/ActionComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			ActionComponents::ActionComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicActionComponent, StaticActionComponent>(entityMemory) {}
			ActionComponents::~ActionComponents() {}

			// getters and setters				

			int ActionComponents::GetNormalAttackDamage_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_normalAttackDamage;
			}

			void ActionComponents::SetNormalAttackDamage_S(int entityStaticID, int normalAttackDamage)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_normalAttackDamage = normalAttackDamage;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes