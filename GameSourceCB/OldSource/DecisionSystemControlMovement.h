#pragma once
#include "stdafx.h"
#include "DecisionSystem.h"

#define DIAGONAL_MOVEMENT 0.7071f


// This class perfroms the decision of where to move the controlled
// entity based on which keys are being pressed
class DecisionSystemControlMovement : public DecisionSystem
{
public:
	DecisionSystemControlMovement(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;

		// get keyboard
		key_board_state_ = SDL_GetKeyboardState(&num_keys_);

		// hard code the directions into an array of all possible
		directions_ = new b2Vec2[16];
		directions_[0].x = 0;
		directions_[0].y = 0;
		directions_[1].x = 1;
		directions_[1].y = 0;
		directions_[2].x = -1;
		directions_[2].y = 0;
		directions_[3].x = 0;
		directions_[3].y = 0;
		directions_[4].x = 0;
		directions_[4].y = -1;
		directions_[5].x = +DIAGONAL_MOVEMENT;
		directions_[5].y = -DIAGONAL_MOVEMENT;
		directions_[6].x = -DIAGONAL_MOVEMENT;
		directions_[6].y = -DIAGONAL_MOVEMENT;
		directions_[7].x = 0;
		directions_[7].y = -1;
		directions_[8].x = 0;
		directions_[8].y = 1;
		directions_[9].x = +DIAGONAL_MOVEMENT;
		directions_[9].y = +DIAGONAL_MOVEMENT;
		directions_[10].x = -DIAGONAL_MOVEMENT;
		directions_[10].y = +DIAGONAL_MOVEMENT;
		directions_[11].x = 0;
		directions_[11].y = 1;
		directions_[12].x = 0;
		directions_[12].y = 0;
		directions_[13].x = 1;
		directions_[13].y = 0;
		directions_[14].x = -1;
		directions_[14].y = 0;
		directions_[15].x = 0;
		directions_[15].y = 0;
	}
	~DecisionSystemControlMovement() {
		delete[] directions_;
	}
	virtual bool updateSystem(uint64_t entity) {

		// if space is pressed the desired velocity should be based on entity, otherwise zero
		// find the index
		int index = 1 * key_board_state_[SDL_SCANCODE_D] + 2 * key_board_state_[SDL_SCANCODE_A] + 4 * key_board_state_[SDL_SCANCODE_S] +
			8 * key_board_state_[SDL_SCANCODE_W];

		if (!entity_group_->active[entity].active && !entity_group_->death[entity].death) {
			entity_group_->movementSpeed[entity].current = entity_group_->movementSpeed[entity].currentMax;
		}
		else {
			entity_group_->movementSpeed[entity].current = 0;
		}

		entity_group_->movementOrientation[entity].orientation = directions_[index];

		return true;
	}

private:
	int num_keys_;
	const uint8_t* key_board_state_;
	b2Vec2* directions_;

};

