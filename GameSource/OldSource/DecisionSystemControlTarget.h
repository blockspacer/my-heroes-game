#pragma once
#include "stdafx.h"
#include "DecisionSystem.h"

class DecisionSystemControlTarget : public DecisionSystem
{
public:
	DecisionSystemControlTarget(EntityGroupPtr entityGroup, int screenWidth, int screenHeight) {
		entity_group_ = entityGroup;
		mouse_offset_x_ = screenWidth / 2;
		mouse_offset_y_ = screenHeight / 2;
	}
	~DecisionSystemControlTarget() {}
	virtual bool updateSystem(uint64_t entity) {

		if (!entity_group_->death[entity].death) {

			// get mouse coordinates
			SDL_GetMouseState(&mouse_x_, &mouse_y_);

			// find relative position
			b2Vec2 relativePosition;
			relativePosition.x = mouse_x_ - mouse_offset_x_;
			relativePosition.y = -(mouse_y_ - mouse_offset_y_);

			// normalize the relative position
			float distance = b2Distance(b2Vec2(0, 0), relativePosition);
			relativePosition.x = relativePosition.x / distance;
			relativePosition.y = relativePosition.y / distance;

			// update entities orientation with the relative position
			entity_group_->visionOrientation[entity].orientation = relativePosition;
		}
		return false;
	}

private:
	int mouse_x_;
	int mouse_y_;
	int mouse_offset_x_;
	int mouse_offset_y_;
};

