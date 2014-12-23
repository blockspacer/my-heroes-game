#pragma once

#include "States/GamePlayState/Entities/HealthComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			HealthComponents::HealthComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicHealthComponent, StaticHealthComponent>(entityMemory) {}
			HealthComponents::~HealthComponents() {}

			// DYNAMIC GETTERS AND SETTERS

			// STATIC GETTERS

			// UTILITY FUNCTIONS			

			// STATIC SETTERS

			int HealthComponents::GetNormalHealth_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_healthNormal;
			}

			void HealthComponents::SetNormalHealth_D(int entityDynamicID, int normalHealth)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_healthNormal = normalHealth;
			}

			int HealthComponents::GetDirectDamage_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_damageDirect;
			}

			void HealthComponents::SetDirectDamage_D(int entityDynamicID, int directDamage)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_damageDirect = directDamage;
			}

			int HealthComponents::GetDirectDamageSource_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_damageDirectSource;
			}

			void HealthComponents::SetDirectDamageSource_D(int entityDynamicID, int directDamageSource)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_damageDirectSource = directDamageSource;
			}

			int HealthComponents::GetDeathTimer_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_deathStartTime;
			}

			void HealthComponents::SetDeathTimer_D(int entityDynamicID, int deathStartTime)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_deathStartTime = deathStartTime;
			}


			int HealthComponents::GetNormalHealth_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_healthNormal;
			}

			void HealthComponents::SetNormalHealth_S(int entityStaticID, int normalHealth)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_healthNormal = normalHealth;
			}

			int HealthComponents::GetDeathTimer_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_deathTime;
			}

			void HealthComponents::SetDeathTimer_S(int entityStaticID, int deathTime)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_deathTime = deathTime;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes