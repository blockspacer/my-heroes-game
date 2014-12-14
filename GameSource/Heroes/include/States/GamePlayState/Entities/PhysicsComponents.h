#pragma once

#include <list>
#include <Box2D/Dynamics/b2Body.h>

#include "States/GamePlayState/Entities/EntityComponentConstants.h"
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
				EntityCollisionMasks m_collisionMask{ ENVIRONMENT_BODY };
				EntityCollisionCategories m_collisionCategory{ ENVIRONMENT_BODY_COL };
				b2BodyType m_bodyType{ b2_staticBody };
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

				int GetBodyType_S(int entityStaticID);

				int GetCollisionMask_S(int entityStaticID);

				int GetCollisionCategory_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS				
				
				void SetBodyType_S(int entityStaticID, b2BodyType bodyType);

				void SetCollisionMask_S(int entityStaticID, EntityCollisionMasks collisionMask);

				void SetCollisionCategory_S(int entityStaticID, EntityCollisionCategories collisionCategory);
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes