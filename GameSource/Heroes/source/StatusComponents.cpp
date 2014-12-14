#pragma once

#include  <SDL_timer.h>
#include "Engine/Log.h"
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

			int StatusComponents::GetBusyStatus_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_busy;
			}

			int StatusComponents::GetIdleStatus_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_idle;
			}

			void StatusComponents::SetIdleStatus_D(int entityDynamicID, IdleStatusType idleStatus)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_idle = idleStatus;
			}

			int StatusComponents::GetActiveStatus_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_status;
			}

			void StatusComponents::SetActiveStatus_D(int entityDynamicID, ActiveStatusType status)
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



			std::string StatusComponents::GetName_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_name;
			}

			void StatusComponents::SetName_S(int entityStaticID, std::string name)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_name = name;
			}

			int StatusComponents::GetBusyStatusStartTime_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_busyStatusStartTime;
			}

			int StatusComponents::GetBusyStatusTotalTime_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_busyStatusTotalTime;
			}

			void StatusComponents::UpdateEntityStatusComponent(int dynamicEntityID)
			{
				CheckDynamicEntityID(dynamicEntityID);
				if (m_dynamicComponents[dynamicEntityID].m_busy != BusyStatusType::NONE)
				{
					int currentTime = SDL_GetTicks();
					if (m_dynamicComponents[dynamicEntityID].m_busyStatusStartTime + m_dynamicComponents[dynamicEntityID].m_busyStatusTotalTime < currentTime)
					{
						m_dynamicComponents[dynamicEntityID].m_busy = BusyStatusType::NONE;
					}
				}
			}

			bool StatusComponents::SetBusyStatus(int entityDynamicID, BusyStatusType busyStatus, int busyStatusTotalTime)
			{
				g_assert(busyStatusTotalTime > 0);
				CheckDynamicEntityID(entityDynamicID);
				if (m_dynamicComponents[entityDynamicID].m_busy != BusyStatusType::NONE)
				{
					return false;
				}
				else
				{
					m_dynamicComponents[entityDynamicID].m_busy = busyStatus;
					m_dynamicComponents[entityDynamicID].m_busyStatusTotalTime = busyStatusTotalTime;
					m_dynamicComponents[entityDynamicID].m_busyStatusStartTime = SDL_GetTicks();
				}

				return true;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes