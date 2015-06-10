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
				//luabind::object m_AISystem;
				//luabind::object m_directionSystem;
				GamePlay::EntityDecisionSystemFunc m_AISystem;
			};

			struct StaticSystemsComponent final
			{
				//luabind::object m_AISystem;
				//luabind::object m_directionSystem;

				GamePlay::EntitySystemFunc m_statusSystem;
				GamePlay::EntitySystemFunc m_healthSystem;
				GamePlay::EntityDecisionSystemFunc m_AISystem;
				GamePlay::EntitySystemFunc m_actionSystem;
				GamePlay::EntitySystemFunc m_movementSystem;
			};

			class SystemsComponents : public ComponentsContainer<DynamicSystemsComponent, StaticSystemsComponent>
			{
			public:
				SystemsComponents(EntityMemory& entityMemory);
				virtual ~SystemsComponents();

				// DYNAMIC GETTERS AND SETTERS

				GamePlay::EntityDecisionSystemFunc GetAISystem_D(int entityDynamicID);

				void SetAISystem_D(int entityDynamicID, GamePlay::EntityDecisionSystemFunc AISystem);

				// STATIC GETTERS

				GamePlay::EntitySystemFunc GetStatusSystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetHealthSystem_S(int entityStaticID);

				GamePlay::EntityDecisionSystemFunc GetAISystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetActionSystem_S(int entityStaticID);

				GamePlay::EntitySystemFunc GetMovementSystem_S(int entityStaticID);

				// UTILITY FUNCTIONS			

			private:

				friend class EntityLoader;

				// STATIC SETTERS

				void SetStatusSystem_S(int entityStaticID, GamePlay::EntitySystemFunc statusSystem);

				void SetHealthSystem_S(int entityStaticID, GamePlay::EntitySystemFunc healthSystem);

				void SetAISystem_S(int entityStaticID, GamePlay::EntityDecisionSystemFunc AISystem);

				void SetActionSystem_S(int entityStaticID, GamePlay::EntitySystemFunc actionSystem);

				void SetMovementSystem_S(int entityStaticID, GamePlay::EntitySystemFunc movementSystem);
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes