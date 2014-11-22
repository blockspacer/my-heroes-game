#pragma once

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicMovementComponent final
			{
			};

			struct StaticMovementComponent final
			{
				float m_movementSpeed{ -1 };
			};

			class MovementComponents : ComponentsContainer<DynamicMovementComponent, StaticMovementComponent>
			{
			public:

				MovementComponents(EntityMemory& entityMemory);
				virtual ~MovementComponents();

				// DYNAMIC GETTERS AND SETTERS

				// STATIC GETTERS

				float GetMovementSpeed_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetMovementSpeed_S(int entityStaticID, float movementSpeed);

			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes