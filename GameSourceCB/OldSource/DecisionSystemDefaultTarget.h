#pragma once
#include "stdafx.h"
#include "DecisionSystem.h"

class DecisionSystemDefaultTarget : public DecisionSystem
{
public:
	DecisionSystemDefaultTarget(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}

	~DecisionSystemDefaultTarget() {}

	virtual bool updateSystem(uint64_t entity) {
		// responsible for updating the entity sensors, the target information, target, distance, vision orientation
		// first check if this entity is death before updating target
		if (!entity_group_->death[entity].death) {

			// find target
			int target = entity_group_->visionTarget[entity].target;

			// FIRST if there is no target try to scan for one,
			// SECOND if there is a target test that it is still alive and within range
			if (target == -1) {
				// look for targets
				// get contacts
				b2ContactEdge* sensorContacts = entity_group_->visionSensor[entity].visionBody->GetContactList();
				// while there are contacts check for touching
				bool targetFound = false;
				while (sensorContacts != NULL) {
					if (sensorContacts->contact->IsTouching()) {
						// get both entities involved in collision
						uint64_t unknownEntity1 = (uint64_t)sensorContacts->contact->GetFixtureA()->GetBody()->GetUserData();
						uint64_t unknownEntity2 = (uint64_t)sensorContacts->contact->GetFixtureB()->GetBody()->GetUserData();

						if (unknownEntity1 == entity && !entity_group_->death[unknownEntity2].death) {
							entity_group_->visionTarget[unknownEntity1].target = unknownEntity2;
							target = unknownEntity2;
							targetFound = true;
						}
						else if (unknownEntity2 == entity && !entity_group_->death[unknownEntity1].death) {
							entity_group_->visionTarget[unknownEntity2].target = unknownEntity1;
							target = unknownEntity1;
							targetFound = true;
						}

						// change sensor shapes if non dead target was found and then break
						if (targetFound) {
							entity_group_->visionSensor[entity].visionBody->DestroyFixture(entity_group_->visionSensor[entity].visionBody->GetFixtureList());
							entity_group_->visionSensor[entity].visionBody->CreateFixture(&entity_group_->visionSensor[entity].smallSightFixDef);
							target = entity_group_->visionTarget[entity].target; // update target if found
							break;
						}
					}
					sensorContacts = sensorContacts->next;
				}
			}


			bool targetLost = false;
			if (target != -1) {

				// if target is not dead
				if (!entity_group_->death[target].death) {

					b2Vec2 entityLocation = entity_group_->physics[entity].body->GetWorldCenter();
					b2Vec2 targetLocation = entity_group_->physics[target].body->GetWorldCenter();
					float distanceToTarget = b2Distance(entityLocation, targetLocation);

					// now see if the distance is longer than tracking distance
					if (distanceToTarget < entity_group_->visionTarget[entity].trackingRange) {

						// distance is good now update vision orientation and decide whether to perfrom
						// action
						// find relative position
						b2Vec2 relativePosition;
						relativePosition.x = targetLocation.x - entityLocation.x;
						relativePosition.y = targetLocation.y - entityLocation.y;

						// normalize the relative position
						relativePosition.x = relativePosition.x / distanceToTarget;
						relativePosition.y = relativePosition.y / distanceToTarget;

						// update entities orientation with the relative position
						entity_group_->visionOrientation[entity].orientation = relativePosition;
						entity_group_->visionTarget[entity].targetDistance = distanceToTarget;

						// just do heavy attacks for now
						if (distanceToTarget < entity_group_->basicAttack[entity].heavyRange) {
							// return true unless the entity is active and not attacking
							if (!(entity_group_->active[entity].active && !entity_group_->attack[entity].attacking)) {
								entity_group_->attack[entity].attackType = Components::ATTACK_TYPE::HEAVY;
								return true;
							}
						}
					}
					else {
						targetLost = true;
					}

				}
				else {
					// if target is dead ditch the target
					targetLost = true;
				}
			}

			// if target was lost set to no target state vision
			if (targetLost) {
				entity_group_->visionTarget[entity].target = -1;
				entity_group_->visionTarget[entity].targetDistance = -1;
				entity_group_->visionOrientation[entity].orientation.x = 0;
				entity_group_->visionOrientation[entity].orientation.y = 0;
				entity_group_->visionSensor[entity].visionBody->DestroyFixture(entity_group_->visionSensor[entity].visionBody->GetFixtureList());
				entity_group_->visionSensor[entity].visionBody->CreateFixture(&entity_group_->visionSensor[entity].largeSightFixDef);
			}

			// return true for now
			return entity_group_->attack[entity].attacking;
		}
	}
};