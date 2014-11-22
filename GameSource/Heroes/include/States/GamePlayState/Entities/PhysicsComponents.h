#pragma once

#include <list>
#include <Box2D/Dynamics/b2Body.h>

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicPhysicsComponent final
			{
				b2Body* m_entityBody{ nullptr }; // single body of the entity
				std::list<b2Shape*> m_entityShapes; // number of shapes that make up the entity
			};

			struct StaticPhysicsComponent final
			{
			};

			class PhysicsComponents : public ComponentsContainer<DynamicPhysicsComponent, StaticPhysicsComponent>
			{
			public:

				PhysicsComponents(EntityMemory& entityMemory);
				virtual ~PhysicsComponents();

				// DYNAMIC GETTERS AND SETTERS

				b2Body* GetEntityBody_D(int entityDynamicID);

				void SetEntityBody_D(int entityDynamicID, b2Body* entityBody);

				std::list<b2Shape*>* GetEntityShapes_D(int entityDynamicID);

				// STATIC GETTERS

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS				
				
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes