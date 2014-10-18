#pragma once
#include "stdafx.h"
#include "EffectSystem.h"

// This class preforms the default movement effect which is to
// move at the current speed in the direction of the movement
// orientation
class EffectSystemDefaultMovement : public EffectSystem
{
public:
	EffectSystemDefaultMovement(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}
	~EffectSystemDefaultMovement() {}

	virtual void updateSystem(uint64_t entity) {
		// moves the entity in the direction of orientation at the
		// current speed

		float desiredVelocity = entity_group_->movementSpeed[entity].current;
		float desiredVelocityX = desiredVelocity * entity_group_->movementOrientation[entity].orientation.x;
		float desiredVelocityY = desiredVelocity * entity_group_->movementOrientation[entity].orientation.y;

		// do the math based on massed and preferred velocity of the body
		b2Vec2 vel = entity_group_->physics[entity].body->GetLinearVelocity();
		float velChangeX = desiredVelocityX - vel.x;
		float impulseX = entity_group_->physics[entity].body->GetMass() * velChangeX; //disregard time factor
		float velChangeY = desiredVelocityY - vel.y;
		float impulseY = entity_group_->physics[entity].body->GetMass() * velChangeY; //disregard time factor

		/*if (entity != 5) {
			cout << "moving" << endl;
			cout << "current speed " << desiredVelocity << endl;
			cout << "movement ORX: " << entity_group_->movementOrientation[entity].orientation.x << endl;
			cout << impulseX << ", " << impulseY << endl;
		}*/


		// apply the impulse to the body
		entity_group_->physics[entity].body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), entity_group_->physics[entity].body->GetWorldCenter(), true);
	}

};

