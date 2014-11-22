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
			};

			struct StaticActionComponent final
			{
				int m_normalAttackDamage{ -1 };
			};

			class ActionComponents : public ComponentsContainer<DynamicActionComponent, StaticActionComponent>
			{
			public:
				ActionComponents(EntityMemory& entityMemory);
				virtual ~ActionComponents();

				// DYNAMIC GETTERS AND SETTERS

				// STATIC GETTERS

				int GetNormalAttackDamage_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetNormalAttackDamage_S(int entityStaticID, int normalAttackDamage);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes