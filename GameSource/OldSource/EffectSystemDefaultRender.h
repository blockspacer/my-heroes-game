#pragma once
#include "stdafx.h"
#include "EffectSystem.h"
#include "Box2DPixelInfo.h"

class EffectSystemDefaultRender : public EffectSystem
{
public:
	EffectSystemDefaultRender(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}
	~EffectSystemDefaultRender() {}

	virtual void updateSystem(uint64_t entity) {
		// currently just update the rect location
		// eventually determine animation

		float healthPercentage = entity_group_->health[entity].current * 1.0 / entity_group_->health[entity].base;
		entity_group_->render[entity].lifeBar.w = static_cast<int>(entity_group_->render[entity].lifeBarBack.w * (healthPercentage));

		int changeX = entity_group_->render[entity].rectWorld.w / 2;
		int changeY = entity_group_->render[entity].rectWorld.h / 2;

		b2Vec2 entityCenter = entity_group_->physics[entity].body->GetWorldCenter();

		int newX = static_cast<int>(entityCenter.x * PIXEL_TO_B2D_RATIO - changeX);
		int newY = static_cast<int>(entityCenter.y * PIXEL_TO_B2D_RATIO + changeY);
		entity_group_->render[entity].rectWorld.x = newX;
		entity_group_->render[entity].rectWorld.y = newY;
		entity_group_->render[entity].lifeBarBack.x = newX;
		entity_group_->render[entity].lifeBarBack.y = newY;
		entity_group_->render[entity].lifeBar.x = newX;
		entity_group_->render[entity].lifeBar.y = newY;
	}
};

