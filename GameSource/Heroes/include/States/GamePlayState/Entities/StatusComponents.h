#pragma once

#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{	
			typedef int StaticEntityIDType;

			enum ActionType
			{
				NO_ACTION,
				CLOSE_COMBAT
			};

			enum MovementType
			{
				NO_MOVEMENT,
				MOVING
			};

			enum StatusType
			{
				ALIVE,
				DEAD
			};

			struct DynamicStatusComponent final
			{
				ActionType m_action{ ActionType::NO_ACTION }; // whether entity is actively doing something (busy)
				MovementType m_movement{ MovementType::NO_MOVEMENT };
				StatusType m_status{ StatusType::DEAD }; // whether entity is dead
				int m_deathTimer{ -1 }; // amount until this entity should be cleaned up
				StaticEntityIDType m_staticEntityID{ -1 };
			};

			struct StaticStatusComponent final
			{
				int m_deathTimer{ -1 }; // max death count down
			};

			class StatusComponents : public ComponentsContainer<DynamicStatusComponent, StaticStatusComponent>
			{
			public:

				StatusComponents(EntityMemory& entityMemory);
				virtual ~StatusComponents();

				// DYNAMIC GETTERS AND SETTERS

				int GetAction_D(int entityDynamicID);

				void SetAction_D(int entityDynamicID, ActionType action);

				int GetMovement_D(int entityDynamicID);

				void SetMovement_D(int entityDynamicID, MovementType movement);

				int GetStatus_D(int entityDynamicID);

				void SetStatus_D(int entityDynamicID, StatusType status);

				int GetDeathTimer_D(int entityDynamicID);

				void SetDeathTimer_D(int entityDynamicID, int deathTimer);

				int GetStaticEntityID_D(int entityDynamicID);

				void SetStaticEntityID_D(int entityDynamicID, int staticEntityID);

				// STATIC GETTERS

				int GetDeathTimer_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetDeathTimer_S(int entityStaticID, int deathTimer);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes