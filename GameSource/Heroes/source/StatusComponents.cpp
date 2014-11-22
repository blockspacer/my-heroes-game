#pragma once

#include "States/GamePlayState/Entities/StatusComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			StatusComponents::StatusComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicStatusComponent, StaticStatusComponent>(entityMemory) {}
			StatusComponents::~StatusComponents() {}

				// DYNAMIC GETTERS AND SETTERS

				// STATIC GETTERS

				// UTILITY FUNCTIONS			

				// STATIC SETTERS

			int StatusComponents::GetAction_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_action;
			}

			void StatusComponents::SetAction_D(int entityDynamicID, ActionType action)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_action = action;
			}

			int StatusComponents::GetMovement_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_movement;
			}

			void StatusComponents::SetMovement_D(int entityDynamicID, MovementType movement)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_movement = movement;
			}

			int StatusComponents::GetStatus_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_status;
			}

			void StatusComponents::SetStatus_D(int entityDynamicID, StatusType status)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_status = status;
			}

			int StatusComponents::GetDeathTimer_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_deathTimer;
			}

			void StatusComponents::SetDeathTimer_D(int entityDynamicID, int deathTimer)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_deathTimer = deathTimer;
			}

			int StatusComponents::GetStaticEntityID_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_staticEntityID;
			}

			void StatusComponents::SetStaticEntityID_D(int entityDynamicID, int staticEntityID)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_staticEntityID = staticEntityID;
			}

			int StatusComponents::GetDeathTimer_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_deathTimer;
			}

			void StatusComponents::SetDeathTimer_S(int entityStaticID, int deathTimer)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_deathTimer = deathTimer;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes