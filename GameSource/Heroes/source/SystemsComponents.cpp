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

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetDirectionSystem_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_directionSystem;
			}

			void SystemsComponents::SetDirectionSystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc directionSystem)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_directionSystem = directionSystem;
			}

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetTargetSystem_D(int entityDynamicID)
			{
				CheckDynamicEntityID(entityDynamicID);
				return m_dynamicComponents[entityDynamicID].m_targetSystem;
			}

			void SystemsComponents::SetTargetSystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc targetSystem)
			{
				CheckDynamicEntityID(entityDynamicID);
				m_dynamicComponents[entityDynamicID].m_targetSystem = targetSystem;
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

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetTargetSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_targetSystem;
			}

			void SystemsComponents::SetTargetSystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc targetSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_targetSystem = targetSystem;
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

			GamePlay::EntityDecisionSystemFunc SystemsComponents::GetDirectionSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_directionSystem;
			}

			void SystemsComponents::SetDirectionSystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc directionSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_directionSystem = directionSystem;
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

			GamePlay::EntityRenderFunc SystemsComponents::GetRenderUpdateSystem_S(int entityStaticID)
			{
				CheckStaticEntityID(entityStaticID);
				return m_staticComponents[entityStaticID].m_renderUpdateSystem;
			}

			void SystemsComponents::SetRenderUpdateSystem_S(int entityStaticID, GamePlay::EntityRenderFunc renderSystem)
			{
				CheckStaticEntityID(entityStaticID);
				m_staticComponents[entityStaticID].m_renderUpdateSystem = renderSystem;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes