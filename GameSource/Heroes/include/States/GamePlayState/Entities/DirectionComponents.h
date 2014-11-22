#pragma once

#include <Box2D/Common/b2Math.h>
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicDirectionComponent final
			{
				b2Vec2 m_direction{ b2Vec2_zero }; // vector for the x and y component
				float m_movementPercentage{ -1.0f };
			};

			struct StaticDirectionComponent final
			{
			};

			class DirectionComponents : public ComponentsContainer<DynamicDirectionComponent, StaticDirectionComponent>
			{
			public:

				DirectionComponents(EntityMemory& entityMemory);
				virtual ~DirectionComponents();

				// DYNAMIC GETTERS AND SETTERS

				b2Vec2 GetDirection_D(int entityDynamicID);

				void SetDirection_D(int entityDynamicID, b2Vec2 direction);

				float GetMovementPercentage_D(int entityDynamicID);

				void SetMovementPercentage_D(int entityDynamicID, float movementPercentage);

				// STATIC GETTERS

				// UTILITY FUNCTIONS			

				float GetDirectionX_D(int entityDynamicID);

				float GetDirectionY_D(int entityDynamicID);

				void SetDirection_D(int entityDynamicID, float x, float y);

			private:

				friend class EntityLoader;

				// STATIC SETTERS
			
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes