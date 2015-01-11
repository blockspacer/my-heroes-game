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

			b2FixtureDef PhysicsComponents::GetBodyDefA_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_bodyDefA;
			}

			b2FixtureDef PhysicsComponents::GetBodyDefB_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_bodyDefB;
			}

			void PhysicsComponents::SetBodyDefA_S(int entityStaticID, b2FixtureDef bodyDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_bodyDefA = bodyDef;
			}

			void PhysicsComponents::SetBodyDefB_S(int entityStaticID, b2FixtureDef bodyDef)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_bodyDefB = bodyDef;
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

			int PhysicsComponents::GetWidth_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_width;
			}

			int PhysicsComponents::GetLength_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_length;
			}

			void PhysicsComponents::SetWidth_S(int entityStaticID, int width)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_width = width;
			}

			void PhysicsComponents::SetLength_S(int entityStaticID, int length)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_length = length;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes