#pragma once

#include <list>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

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
			};

			struct StaticPhysicsComponent final
			{
				b2FixtureDef m_bodyDefA; // memory leak
				b2FixtureDef m_bodyDefB; // memory leak
				b2FixtureDef m_visionDef; // memory leak
				int m_width{ 0 };
				int m_length{ 0 };
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

				int GetWidth_S(int entityStaticID);

				int GetLength_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS				
				
				void SetBodyType_S(int entityStaticID, b2BodyType bodyType);

				b2FixtureDef GetBodyDefA_S(int entityStaticID);
				b2FixtureDef GetBodyDefB_S(int entityStaticID);

				void SetBodyDefA_S(int entityStaticID, b2FixtureDef bodyDef);
				void SetBodyDefB_S(int entityStaticID, b2FixtureDef bodyDef);

				b2FixtureDef GetVisionDef_S(int entityStaticID);

				void SetVisionDef_S(int entityStaticID, b2FixtureDef visionDef);

				void SetWidth_S(int entityStaticID, int width);

				void SetLength_S(int entityStaticID, int length);
			};
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes