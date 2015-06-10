#pragma once

#include "States/GamePlayState/Entities/SystemsComponents.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			SystemsComponents::SystemsComponents(EntityMemory& entityMemory) : ComponentsContainer<DynamicSystemsComponent, StaticSystemsComponent>(entityMemory) {}
			SystemsComponents::~SystemsComponents() {}

			// DYNAMIC GETTERS AND SETTERS

			// STATIC GETTERS

			// UTILITY FUNCTIONS			

			// STATIC SETTERS

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetAISystem_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_AISystem;
			}

			void SystemsComponents::SetAISystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc AISystem)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_AISystem = AISystem;
			}

			GamePlay::EntitySystemFunc SystemsComponents::GetStatusSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_statusSystem;
			}

			void SystemsComponents::SetStatusSystem_S(int entityStaticID, GamePlay::EntitySystemFunc statusSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_statusSystem = statusSystem;
			}

			GamePlay::EntitySystemFunc SystemsComponents::GetHealthSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_healthSystem;
			}

			void SystemsComponents::SetHealthSystem_S(int entityStaticID, GamePlay::EntitySystemFunc healthSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_healthSystem = healthSystem;
			}

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetAISystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_AISystem;
			}

			void SystemsComponents::SetAISystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc AISystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_AISystem = AISystem;
			}

			GamePlay::EntitySystemFunc SystemsComponents::GetActionSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_actionSystem;
			}

			void SystemsComponents::SetActionSystem_S(int entityStaticID, GamePlay::EntitySystemFunc actionSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_actionSystem = actionSystem;
			}

			GamePlay::EntitySystemFunc SystemsComponents::GetMovementSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_movementSystem;
			}

			void SystemsComponents::SetMovementSystem_S(int entityStaticID, GamePlay::EntitySystemFunc movementSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_movementSystem = movementSystem;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes