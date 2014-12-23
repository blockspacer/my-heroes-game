#pragma once

#include "Engine/Log.h"
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

			bool ActionComponents::GetNormalAttackDamagePoint_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_normalAttackDamagePoint;
			}

			void ActionComponents::SetNormalAttackDamagePoint_D(int entityDynamicID, bool normalAttackDamagePoint)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_normalAttackDamagePoint = normalAttackDamagePoint;
			}

			int ActionComponents::GetNormalAttackDamage_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_normalAttackDamage;
			}

			int ActionComponents::GetNormalAttackSpeed_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_normalAttackSpeed;
			}

			int ActionComponents::GetNormalAttackRange_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_normalAttackRange;
			}

			float ActionComponents::GetNormalAttackDamagePoint_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_normalAttackDamagePoint;
			}

			void ActionComponents::SetNormalAttackDamage_S(int entityStaticID, int normalAttackDamage)
			{
				CheckStaticEntityID(entityStaticID);
				g_assert(normalAttackDamage > 0);
				m_staticComponents[entityStaticID].m_normalAttackDamage = normalAttackDamage;
			}

			void ActionComponents::SetNormalAttackSpeed_S(int entityStaticID, int normalAttackSpeed)
			{
				CheckStaticEntityID(entityStaticID);
				g_assert(normalAttackSpeed > 0);
				m_staticComponents[entityStaticID].m_normalAttackSpeed = normalAttackSpeed;
			}

			void ActionComponents::SetNormalAttackRange_S(int entityStaticID, int normalAttackRange)
			{
				CheckStaticEntityID(entityStaticID);
				g_assert(normalAttackRange > 0);
				m_staticComponents[entityStaticID].m_normalAttackRange = normalAttackRange;
			}

			void ActionComponents::SetNormalAttackDamagePoint_S(int entityStaticID, float normalAttackDamagePoint)
			{
				CheckStaticEntityID(entityStaticID);
				g_assert(normalAttackDamagePoint > 0.0f && normalAttackDamagePoint < 1.0f);
				m_staticComponents[entityStaticID].m_normalAttackDamagePoint = normalAttackDamagePoint;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes