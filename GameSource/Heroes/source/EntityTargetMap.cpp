#include "Engine/Log.h"
#include "States/GamePlayState/Entities/EntityTargetMap.h"
#include "States/GamePlayState/Entities/EntityMemory.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			int DistanceValue(int source, int target, EntityMemory& entityMemory)
			{

				b2Vec2 distanceVec = entityMemory.m_physicsComponents.GetEntityBody_D(source)->GetPosition() - entityMemory.m_physicsComponents.GetEntityBody_D(target)->GetPosition();

				return static_cast<int>(distanceVec.Length());
			}


			EntityTargetMap::EntityTargetMap(TargetValueFunction targetValueFunction) : m_targetValueFunction(targetValueFunction)
			{}

			int EntityTargetMap::GetTarget(EntityMemory& entityMemory)
			{
				// check entities are in active status and return the target
				int target = -1;

				while (m_targetFront != nullptr)
				{
					if (CheckTarget(m_targetFront->m_dynamicID, entityMemory))
					{
						target = m_targetFront->m_dynamicID;
						break;
					}
					else
					{
						RemoveTarget(m_targetFront->m_dynamicID);
					}
				}

				return target;
				
			}

			void EntityTargetMap::SwitchTargets(EntityMemory& entityMemory)
			{
				if (m_targetBack != nullptr)
				{
					SwitchToTarget(m_targetBack->m_dynamicID, entityMemory);
				}
			}

			void EntityTargetMap::SwitchToTarget(int target, EntityMemory& entityMemory)
			{
				if (CheckTarget(target, entityMemory))
				{
					int hashValue = HashValue(target);
					TargetMapEntry* entry = &m_targets[hashValue];

					// if this target is known
					if (entry->m_dynamicID == target)
					{

						// proceed to swap targets

						// remove target from list
						RemoveEntryFromInternalList(entry);

						// place target at front
						entry->m_before = nullptr;
						entry->m_after = m_targetFront;

						// update front
						if (m_targetFront != nullptr)
						{
							m_targetFront->m_before = entry;
						}
						m_targetFront = entry;

						// update back
						if (m_targetBack == nullptr)
						{
							m_targetBack = entry;
						}
					}
				}
				else
				{
					RemoveTarget(target);
				}
			}

			void EntityTargetMap::AddTargetFront(int target, EntityMemory& entityMemory)
			{
				if (CheckTarget(target, entityMemory))
				{
					int hashValue = HashValue(target);

					TargetMapEntry* newEntry = &m_targets[hashValue];

					// if spot is empty
					if (newEntry->m_dynamicID == -1)
					{
						m_numberOfTargets++;
						newEntry->m_value = m_targetValueFunction(m_source, target, entityMemory);
						newEntry->m_dynamicID = target;
						// now place in list

						TargetMapEntry* insertionPoint = m_targetFront;


						// empty list
						if (insertionPoint == nullptr)
						{
							newEntry->m_before = nullptr;
							newEntry->m_after = nullptr;
							m_targetFront = newEntry;
							m_targetBack = newEntry;
						}
						// otherwise
						else
						{
							bool front = true;
							bool end = false;

							// update value
							g_assert(insertionPoint->m_dynamicID != -1 && insertionPoint->m_dynamicID != m_source);
							insertionPoint->m_value = m_targetValueFunction(m_source, insertionPoint->m_dynamicID, entityMemory);

							while (insertionPoint->m_value < newEntry->m_value)
							{
								front = false;

								// if this is the end
								if (insertionPoint->m_after == nullptr)
								{
									end = true;
									break;
								}

								// increment and update
								insertionPoint = insertionPoint->m_after;
								g_assert(insertionPoint->m_dynamicID != -1 && insertionPoint->m_dynamicID != m_source);
								insertionPoint->m_value = m_targetValueFunction(m_source, insertionPoint->m_dynamicID, entityMemory);
							}

							// put before insertion point


							if (front)
							{
								insertionPoint->m_before = newEntry;
								newEntry->m_after = insertionPoint;
								newEntry->m_before = nullptr;
								m_targetFront = newEntry;
							}
							// place at end
							else if (end)
							{
								insertionPoint->m_after = newEntry;
								newEntry->m_before = insertionPoint;
								newEntry->m_after = nullptr;
								m_targetBack = newEntry;
							}
							// place before insertion point
							else
							{
								TargetMapEntry* preInsertionPoint = insertionPoint->m_before;

								// set new point
								newEntry->m_before = preInsertionPoint;
								newEntry->m_after = insertionPoint;

								preInsertionPoint->m_after = newEntry;
								insertionPoint->m_before = newEntry;
							}

							
						}

						newEntry->m_fixtures = 1;
					}
					else if (newEntry->m_dynamicID == target)
					{
						newEntry->m_fixtures++;
					}
				}
			}

			void EntityTargetMap::AddTargetBack(int target, EntityMemory& entityMemory)
			{

			}

			void EntityTargetMap::RemoveTarget(int target)
			{
				int hashedValue = HashValue(target);

				TargetMapEntry* entry = &m_targets[hashedValue];

				if (entry->m_dynamicID != -1)
				{
					if (entry->m_fixtures == 1)
					{
						m_numberOfTargets--;
						// target is first and last
						RemoveEntryFromInternalList(entry);

						// cleanup entry
						entry->m_dynamicID = -1;
						entry->m_before = nullptr;
						entry->m_after = nullptr;
					}
					else
					{
						entry->m_fixtures--;
					}	
				}
			}

			int EntityTargetMap::GetNumberOfTargets()
			{
				return m_numberOfTargets;
			}

			int EntityTargetMap::HashValue(int target)
			{
				return target % EntityTargetMapConstants::SIZE;
				//return (target * EntityTargetMapConstants::HASH_VALUE) % EntityTargetMapConstants::SIZE;
			}

			void EntityTargetMap::ClearTargets()
			{
				while (m_targetFront != nullptr)
				{
					m_targetFront->m_dynamicID = -1;
					m_targetFront = m_targetFront->m_after;
				}
			}

			void EntityTargetMap::SetSourceEntity(int source)
			{
				if (source != -1)
				{
					g_assert(m_source == -1);
				}
				
				m_source = source;
			}

			void EntityTargetMap::RemoveEntryFromInternalList(TargetMapEntry* entry)
			{

				if (entry->m_dynamicID != -1)
				{
					// target is first and last
					if (entry->m_before == nullptr && entry->m_after == nullptr)
					{
						m_targetFront = nullptr;
						m_targetBack = nullptr;
					}
					// just first
					else if (entry->m_before == nullptr)
					{
						m_targetFront = entry->m_after;
						entry->m_after->m_before = nullptr;
					}
					// just last
					else if (entry->m_after == nullptr)
					{
						// no back to set
						m_targetBack = entry->m_before;
						entry->m_before->m_after = nullptr;
					}
					// middle
					else
					{
						entry->m_before->m_after = entry->m_after;
						entry->m_after->m_before = entry->m_before;
					}
				}
			}

			bool EntityTargetMap::CheckTarget(int target, EntityMemory& entityMemory)
			{
				return entityMemory.m_statusComponents.GetActiveStatus_D(target) == ActiveStatusType::ACTOR ||
					   entityMemory.m_statusComponents.GetActiveStatus_D(target) == ActiveStatusType::EFFECT;
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes