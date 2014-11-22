#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			class EntityMemory;

			enum ComponentContainerConstants
			{
				DYNAMIC_ENTITY_MEMORY_SIZE = 1000,
				STATIC_ENTITY_MEMORY_SIZE = 1
			};

			void CheckDynamicEntityID(int entityDynamicID);
			void CheckStaticEntityID(int entityStaticID);

			template <typename T_D, typename T_S>
			class ComponentsContainer
			{
			public:
				ComponentsContainer::ComponentsContainer(EntityMemory& entityMemory) : m_entityMemory(entityMemory) {}
				virtual ~ComponentsContainer() {}

			protected:

				T_D m_dynamicComponents[ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				T_S m_staticComponents[ComponentContainerConstants::STATIC_ENTITY_MEMORY_SIZE];

				EntityMemory& m_entityMemory;
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
