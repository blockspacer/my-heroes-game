#pragma once
#include "stdafx.h"
#include "EffectSystem.h"

class EffectSystemDefaultHealth : public EffectSystem
{
public:
	EffectSystemDefaultHealth(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}

	~EffectSystemDefaultHealth() {}

	virtual void updateSystem(uint64_t entity) {
		// TODO clean up

		if (!entity_group_->death[entity].death) {

			// if damage is taken reset the recoil and regenerate countdown
			/*if (entity_group_->healthDamage[entity].damage[Components::ATTACK_TYPE_DAMAGE::NORMAL] |
				entity_group_->healthDamage[entity].damage[Components::ATTACK_TYPE_DAMAGE::FIRE]) {
				entity_group_->regenerate[entity].countDown = entity_group_->regenerate[entity].base;
				entity_group_->recoil[entity].countDown = entity_group_->recoil[entity].base;
				entity_group_->active[entity].active = true;
			}
			else {
				// no damage update recoil count down
				if (entity_group_->recoil[entity].countDown > 0) {
					entity_group_->recoil[entity].countDown--;
				}
				else {
					entity_group_->active[entity].active = false;
				}

				// no damage update regenerate count down
				if (entity_group_->regenerate[entity].countDown > 0) {
					entity_group_->regenerate[entity].countDown--;
				}
				else {
					if (entity_group_->health[entity].current < entity_group_->health[entity].base) {
						entity_group_->health[entity].current += entity_group_->regenerate[entity].rate;
					}
				}
			}*/

			// deal with chunck damage
			int chunckDamage = entity_group_->healthDamage[entity].chunkDamage;
			if (chunckDamage > 0) {
				entity_group_->health[entity].current = b2Max(entity_group_->health[entity].current - chunckDamage, 0);
				entity_group_->healthDamage[entity].chunkDamage = 0;
				if (!entity_group_->death[entity].death && entity_group_->health[entity].current == 0) {
					// kill this entity and allocate kill
					entity_group_->death[entity].death = true;
					entity_group_->attack[entity_group_->healthDamage[entity].chunckDamageSource].kills++;
				}
			}

			int incrementalDamage = entity_group_->healthDamage[entity].incrementalDamage;
			if (incrementalDamage > 0) {
				entity_group_->health[entity].current = b2Max(entity_group_->health[entity].current - entity_group_->healthDamage[entity].incrementalRate, 0);
				entity_group_->healthDamage[entity].incrementalDamage - entity_group_->healthDamage[entity].incrementalRate;
				if (!entity_group_->death[entity].death && entity_group_->health[entity].current == 0) {
					entity_group_->death[entity].death = true;
					entity_group_->attack[entity_group_->healthDamage[entity].incrementalDamageSource].kills++;
				}
			}
		}
	}
};

