#include <SDL_assert.h>
#include "States/GamePlayState/Entities/ComponentsContainer.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			void CheckDynamicEntityID(int entityDynamicID)
			{
				SDL_assert(entityDynamicID >= 0 && entityDynamicID < ComponentContainerConstants::DYNAMIC_ENTITY_MEMORY_SIZE);
			}

			void CheckStaticEntityID(int entityStaticID)
			{
				SDL_assert(entityStaticID >= 0 && entityStaticID < ComponentContainerConstants::STATIC_ENTITY_MEMORY_SIZE);
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes