#pragma once
#include "stdafx.h"
#include "DecisionSystem.h"

// This is the class for the default movement logic
// which is to set the movement speed to 0 if the entity
// is active and to currentMax is the entity is non active
// and finally set the movement orientation to the vision orientation
class DecisionSystemDefaultMovement : public DecisionSystem
{
public:
	DecisionSystemDefaultMovement(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}

	~DecisionSystemDefaultMovement() {}

	virtual bool updateSystem(uint64_t entity) {
		// update orientation and movement speed

		// if entity is not dead
		// if it is dead or active it should not be moving
		if (!entity_group_->active[entity].active && !entity_group_->death[entity].death) {
			entity_group_->movementSpeed[entity].current = entity_group_->movementSpeed[entity].currentMax;
		} else {
			entity_group_->movementSpeed[entity].current = 0;
		}

		entity_group_->movementOrientation[entity].orientation = entity_group_->visionOrientation[entity].orientation;

		return true;
	}
};

