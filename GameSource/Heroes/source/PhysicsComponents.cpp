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

			int PhysicsComponents::GetBodyType_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_bodyType;
			}

			int PhysicsComponents::GetCollisionMask_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_collisionMask;
			}

			int PhysicsComponents::GetCollisionCategory_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_collisionCategory;
			}

			void PhysicsComponents::SetBodyType_S(int entityStaticID, b2BodyType bodyType)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_bodyType = bodyType;
			}

			void PhysicsComponents::SetCollisionMask_S(int entityStaticID, EntityCollisionMasks collisionMask)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_collisionMask = collisionMask;
			}

			void PhysicsComponents::SetCollisionCategory_S(int entityStaticID, EntityCollisionCategories collisionCategory)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_collisionCategory = collisionCategory;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes