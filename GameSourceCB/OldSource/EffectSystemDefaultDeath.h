#pragma once
#include "stdafx.h"
#include "EffectSystem.h"
#include "EntityManager.h"

class EffectSystemDefaultDeath : public EffectSystem
{
public:
	EffectSystemDefaultDeath(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}
	~EffectSystemDefaultDeath() {}

	virtual void updateSystem(uint64_t entity) {
		if (entity_group_->death[entity].death) {
			if (entity_group_->death[entity].countDown > 0) {
				entity_group_->death[entity].countDown--;
			}
			else {
				// delete vision component
				entity_group_->world->DestroyJoint(entity_group_->visionSensor[entity].connectionJoint);
				entity_group_->world->DestroyBody(entity_group_->visionSensor[entity].visionBody);
				delete entity_group_->visionSensor[entity].smallSightShape;
				delete entity_group_->visionSensor[entity].largeSightShape;

				// delete physics component
				entity_group_->world->DestroyBody(entity_group_->physics[entity].body);
				for (auto it = entity_group_->physics[entity].shapes.begin(); it != entity_group_->physics[entity].shapes.end(); it++) {
					delete *it;
				}

				// delete render components
				SDL_DestroyTexture(entity_group_->render[entity].texture); // have to deal with all the textures

				// reset mask and free
				entity_group_->maskList[entity].mask.reset();
				EntityManager::releaseEntity(entity_group_, entity);
			}
		}
	}
};

