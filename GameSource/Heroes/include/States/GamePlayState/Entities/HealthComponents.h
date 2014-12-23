#pragma once

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicHealthComponent final
			{
				int m_healthNormal{ -1 };
				int m_damageDirect{ -1 };
				int m_damageDirectSource{ -1 };
				int m_deathStartTime{ -1 }; // amount until this entity should be cleaned up
			};

			struct StaticHealthComponent final
			{
				int m_healthNormal{ -1 };
				int m_deathTime{ -1 }; // max death count down
			};

			class HealthComponents : public ComponentsContainer<DynamicHealthComponent, StaticHealthComponent>
			{
			public:

				HealthComponents(EntityMemory& entityMemory);
				virtual ~HealthComponents();

				// DYNAMIC GETTERS AND SETTERS

				int GetNormalHealth_D(int entityDynamicID);

				void SetNormalHealth_D(int entityDynamicID, int normalHealth);

				int GetDirectDamage_D(int entityDynamicID);

				void SetDirectDamage_D(int entityDynamicID, int directDamage);

				int GetDirectDamageSource_D(int entityDynamicID);

				void SetDirectDamageSource_D(int entityDynamicID, int directDamageSource);

				int GetDeathTimer_D(int entityDynamicID);

				void SetDeathTimer_D(int entityDynamicID, int deathTimer);

				// STATIC GETTERS

				int GetNormalHealth_S(int entityStaticID);

				int GetDeathTimer_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetNormalHealth_S(int entityStaticID, int normalHealth);

				void SetDeathTimer_S(int entityStaticID, int deathTimer);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes