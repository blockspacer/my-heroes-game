#pragma once

#include "States/GamePlayState/Systems/EntitySystem.h"
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			struct DynamicSystemsComponent final
			{
				//luabind::object m_targetSystem;
				//luabind::object m_directionSystem;
				GamePlay::EntityDecisionSystemFunc m_targetSystem;
				GamePlay::EntityDecisionSystemFunc m_directionSystem;
			};

			struct StaticSystemsComponent final
			{
				//luabind::object m_targetSystem;
				//luabind::object m_directionSystem;

				GamePlay::EntitySystemFunc m_statusSystem;
				GamePlay::EntitySystemFunc m_healthSystem;
				GamePlay::EntityDecisionSystemFunc m_targetSystem;
				GamePlay::EntitySystemFunc m_actionSystem;
				GamePlay::EntityDecisionSystemFunc m_directionSystem;
				GamePlay::EntitySystemFunc m_movementSystem;
				GamePlay::EntityRenderFunc m_renderUpdateSystem;
			};

			class SystemsComponents : public ComponentsContainer<DynamicSystemsComponent, StaticSystemsComponent>
			{
			public:
				SystemsComponents(EntityMemory& entityMemory);
				virtual ~SystemsComponents();

				// DYNAMIC GETTERS AND SETTERS

				GamePlay::EntityDecisionSystemFunc GetDirectionSystem_D(int entityDynamicID);

				void SetDirectionSystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc directionSystem);

				GamePlay::EntityDecisionSystemFunc GetTargetSystem_D(int entityDynamicID);

				void SetTargetSystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc targetSystem);

				// STATIC GETTERS

				GamePlay::EntitySystemFunc GetStatusSystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetHealthSystem_S(int entityStaticID);

				GamePlay::EntityDecisionSystemFunc GetTargetSystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetActionSystem_S(int entityStaticID);
				
				GamePlay::EntityDecisionSystemFunc GetDirectionSystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetMovementSystem_S(int entityStaticID);

				GamePlay::EntityRenderFunc GetRenderUpdateSystem_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetStatusSystem_S(int entityStaticID, GamePlay::EntitySystemFunc statusSystem);

				void SetHealthSystem_S(int entityStaticID, GamePlay::EntitySystemFunc healthSystem);

				void SetTargetSystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc targetSystem);

				void SetActionSystem_S(int entityStaticID, GamePlay::EntitySystemFunc actionSystem);

				void SetDirectionSystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc directionSystem);

				void SetMovementSystem_S(int entityStaticID, GamePlay::EntitySystemFunc movementSystem);

				void SetRenderUpdateSystem_S(int entityStaticID, GamePlay::EntityRenderFunc renderSystem);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes