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

			void PhysicsComponents::SetBodyType_S(int entityStaticID, b2BodyType bodyType)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_bodyType = bodyType;
			}

			b2FixtureDef PhysicsComponents::GetBodyDef_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_bodyDef;
			}

			void PhysicsComponents::SetBodyDef_S(int entityStaticID, b2FixtureDef bodyDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_bodyDef = bodyDef;
			}

			b2FixtureDef PhysicsComponents::GetVisionDef_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_visionDef;
			}

			void PhysicsComponents::SetVisionDef_S(int entityStaticID, b2FixtureDef visionDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_visionDef = visionDef;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes