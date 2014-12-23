#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			class EntityMemory;
			struct TargetMapEntry;

			struct TargetMapEntry final
			{
				TargetMapEntry* m_before{ nullptr };
				TargetMapEntry* m_after{ nullptr };
				int m_dynamicID{ -1 };
				int m_value{ 0 };
				int m_fixtures{ 0 };
			};

			enum EntityTargetMapConstants
			{
				SIZE = 47,
				HASH_VALUE = 25
			};

			int DistanceValue(int source, int target, EntityMemory& entityMemory);

			class EntityTargetMap final
			{
			public:

				/*
				 * A comes before B return -1
				 * A = B return 0
				 * A comes after B return 1
				 */
				typedef int (*TargetValueFunction)(int source, int target, EntityMemory& entityMemory);

				EntityTargetMap(TargetValueFunction targetValueFunction);

				int GetTarget(EntityMemory& entityMemory);
				void SwitchTargets(EntityMemory& entityMemory);
				void SwitchToTarget(int target, EntityMemory& entityMemory);

				void AddTargetFront(int target, EntityMemory& entityMemory);
				void AddTargetBack(int target, EntityMemory& entityMemory);
				void RemoveTarget(int target);
				
				int GetNumberOfTargets();

				void ClearTargets();
				void SetSourceEntity(int source);

			private:

				void RemoveEntryFromInternalList(TargetMapEntry* entry);
				bool CheckTarget(int target, EntityMemory& entityMemory);

				int HashValue(int target);

				TargetValueFunction m_targetValueFunction{ DistanceValue };

				TargetMapEntry m_targets[EntityTargetMapConstants::SIZE];

				TargetMapEntry* m_targetFront{ nullptr };
				TargetMapEntry* m_targetBack{ nullptr };

				int m_numberOfTargets{ 0 };

				int m_source{ -1 };
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes