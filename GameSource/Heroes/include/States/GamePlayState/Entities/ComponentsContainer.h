// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			// used for class member in ComponentsContainer template class
			class EntityMemory;

			/*
			 * This is the definition for how many dynamic and static components can be
			 * simultaneously held.
			 */
			enum ComponentContainerConstants
			{
				DYNAMIC_ENTITY_MEMORY_SIZE = 1000,
				STATIC_ENTITY_MEMORY_SIZE = 50
			};

			/*
			 * These are common/useful functions for checking the indexing for
			 * either the dynamic of static components.
			 */
			void CheckDynamicEntityID(int entityDynamicID);
			void CheckStaticEntityID(int entityStaticID);

			/*
			 * This class is a template for the Entity components. It combines the dynamic and 
			 * static componenets in a single class. The purpose of the class is to be a single
			 * generic access point to a specific Entity component type. This template allows
			 * the freedom to create functions to access the dynamic and static arrays. Methods can even
			 * be and are used to facilitate certain types of updates. These are used in the StatusComponents
			 * class as an example. The method access protocol also enable these classes to be more easily exported
			 * to Lua and gives better access control to the script writers.
			 * T_D should be the dynamic struct of an entity component
			 * T_S should be the static struct of an entity component
			 */
			template <typename T_D, typename T_S>
			class ComponentsContainer
			{
			public:

				ComponentsContainer::ComponentsContainer(EntityMemory& entityMemory) : m_entityMemory(entityMemory) {}
				virtual ~ComponentsContainer() {}

			protected:

				// These are the dynamic and static arrays, they are supposed to allow efficent usage
				// of memory spatially
				T_D m_dynamicComponents[ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE];
				T_S m_staticComponents[ComponentContainerConstants::STATIC_ENTITY_MEMORY_SIZE];

				// This is not required but is used often among the various components
				EntityMemory& m_entityMemory;
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
