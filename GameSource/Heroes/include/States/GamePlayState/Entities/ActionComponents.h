#pragma once

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicActionComponent final
			{
				bool m_normalAttackDamagePoint{ false };

			};

			struct StaticActionComponent final
			{
				int m_normalAttackDamage{ -1 };
				int m_normalAttackSpeed{ 0 };
				int m_normalAttackRange{ 0 };
				float m_normalAttackDamagePoint{ 0.0f };
			};

			class ActionComponents : public ComponentsContainer<DynamicActionComponent, StaticActionComponent>
			{
			public:
				ActionComponents(EntityMemory& entityMemory);
				virtual ~ActionComponents();

				// DYNAMIC GETTERS AND SETTERS
				int GetNormalAttackTime_D(int entityDynamicID);
				void SetNormalAttackTime_D(int entityDynamicID, int normalAttackTime);
				bool GetNormalAttackDamagePoint_D(int entityDynamicID);
				void SetNormalAttackDamagePoint_D(int entityDynamicID, bool normaAttackDamagePoint);

				// STATIC GETTERS

				int GetNormalAttackDamage_S(int entityStaticID);
				int GetNormalAttackSpeed_S(int entityStaticID);
				int GetNormalAttackRange_S(int entityStaticID);
				float GetNormalAttackDamagePoint_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetNormalAttackDamage_S(int entityStaticID, int normalAttackDamage);
				void SetNormalAttackSpeed_S(int entityStaticID, int normalAttackSpeed);
				void SetNormalAttackRange_S(int entityStaticID, int normalAttackRange);
				void SetNormalAttackDamagePoint_S(int entityStaticID, float normalAttackDamagePoint);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes