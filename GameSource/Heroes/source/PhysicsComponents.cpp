#pragma once

#include "States/GamePlayState/Entities/PhysicsComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			PhysicsComponents::PhysicsComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicPhysicsComponent, StaticPhysicsComponent>(entityMemory) {}
			PhysicsComponents::~PhysicsComponents() {}

			// DYNAMIC GETTERS AND SETTERS

			// STATIC GETTERS

			// UTILITY FUNCTIONS			

			// STATIC SETTERS

			b2Body* PhysicsComponents::GetEntityBody_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_entityBody;
			}

			void PhysicsComponents::SetEntityBody_D(int entityDynamicID, b2Body* entityBody)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_entityBody = entityBody;
			}

			std::list<b2Shape*>* PhysicsComponents::GetEntityShapes_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return &m_dynamicComponents[entityDynamicID].m_entityShapes;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes