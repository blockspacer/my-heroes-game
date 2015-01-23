// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#include "Engine/Log.h"
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			void CheckDynamicEntityID(int entityDynamicID)
			{
				g_assert(entityDynamicID >= 0 && entityDynamicID < ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
			}

			void CheckStaticEntityID(int entityStaticID)
			{
				g_assert(entityStaticID >= 0 && entityStaticID < ComponentContainerConstants::STATIC_ENTITY_MEMORY_SIZE);
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes