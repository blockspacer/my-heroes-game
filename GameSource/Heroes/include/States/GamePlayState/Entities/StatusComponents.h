#pragma once

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{	
			typedef int StaticEntityIDType;

			enum BusyStatusType
			{
				NONE,
				DEAD,
				STUNNED,
				BASIC_ATTACK,
				SPECIAL_ATTACK

			};

			enum IdleStatusType
			{
				STANDING,
				MOVING
			};

			enum ActiveStatusType
			{
				ACTOR,
				EFFECT,
				NA,
				TOMBSTONE
			};

			struct DynamicStatusComponent final
			{


				BusyStatusType m_busy{ BusyStatusType::NONE }; // whether entity is actively doing something (busy)
				int m_busyStatusStartTime{ 0 };
				int m_busyStatusTotalTime{ 0 };

				IdleStatusType m_idle{ IdleStatusType::STANDING };
				ActiveStatusType m_status{ ActiveStatusType::NA }; // whether entity is dead
				
				StaticEntityIDType m_staticEntityID{ -1 };
			};

			struct StaticStatusComponent final
			{
				std::string m_name{ "" };
				ActiveStatusType m_status{ ActiveStatusType::NA }; // whether entity is dead
			};

			class StatusComponents : public ComponentsContainer<DynamicStatusComponent, StaticStatusComponent>
			{
			public:

				StatusComponents(EntityMemory& entityMemory);
				virtual ~StatusComponents();

				// DYNAMIC GETTERS AND SETTERS

				int GetBusyStatus_D(int entityDynamicID);

				int GetBusyStatusStartTime_D(int entityDynamicID);

				int GetBusyStatusTotalTime_D(int entityDynamicID);

				int GetIdleStatus_D(int entityDynamicID);

				void SetIdleStatus_D(int entityDynamicID, IdleStatusType idleStatus);

				int GetActiveStatus_D(int entityDynamicID);

				void SetActiveStatus_D(int entityDynamicID, ActiveStatusType status);

				int GetActiveStatus_S(int entityStaticID);

				int GetStaticEntityID_D(int entityDynamicID);

				void SetStaticEntityID_D(int entityDynamicID, int staticEntityID);

				// STATIC GETTERS

				

				std::string GetName_S(int entityStaticID);

				// UTILITY FUNCTIONS

				void UpdateEntityStatusComponent_D(int dynamicEntityID);

				bool SetBusyStatus_D(int entityDynamicID, BusyStatusType busyStatus, int busyStatusTotalTime);

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetActiveStatus_S(int entityStaticID, ActiveStatusType activeStatus);

				void SetName_S(int entityStaticID, std::string name);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes