#pragma once
#include "stdafx.h"
#include "EffectSystem.h"

class EffectSystemDefaultAction : public EffectSystem
{
public:
	EffectSystemDefaultAction(EntityGroupPtr entityGroup) {
		entity_group_ = entityGroup;
	}
	~EffectSystemDefaultAction() {}

	virtual void updateSystem(uint64_t entity) {
		// default system only does light or heavy
		uint64_t target = entity_group_->visionTarget[entity].target;

		// if attacking continue attack
		if (entity_group_->attack[entity].attacking) {

			if (entity_group_->attack[entity].attacking == Components::ATTACK_TYPE::LIGHT) {
				// if it is damage point do the damage to the target
	
				if (entity_group_->basicAttack[entity].lightSpeedCurrent == entity_group_->basicAttack[entity].lightSpeedDamagePoint &&
					target != -1 && entity_group_->visionTarget[entity].targetDistance < entity_group_->basicAttack[entity].lightRange) {
					// do damage, determining resistances and such
					doDamage(entity, target, entity_group_->basicAttack[entity].lightDamage, entity_group_->basicAttack[entity].lightType);
				}

				// increment the attack
				if (entity_group_->basicAttack[entity].lightSpeedCurrent > 0) {
					entity_group_->basicAttack[entity].lightSpeedCurrent--;
				}
				else {
					entity_group_->attack[entity].attacking = false;
					entity_group_->active[entity].active = false;
					entity_group_->basicAttack[entity].lightSpeedCurrent = entity_group_->basicAttack[entity].lightSpeedBase;
				}
			}
			else if (entity_group_->attack[entity].attacking == Components::ATTACK_TYPE::HEAVY) {
				// if it is damage point do the damage to the target
				if (entity_group_->basicAttack[entity].heavySpeedCurrent == entity_group_->basicAttack[entity].heavySpeedDamagePoint &&
					target != -1 && entity_group_->visionTarget[entity].targetDistance < entity_group_->basicAttack[entity].heavyRange) {
					// do damage, determining resistances and such
					doDamage(entity, target, entity_group_->basicAttack[entity].heavyDamage, entity_group_->basicAttack[entity].heavyType);
				}

				// increment the attack
				if (entity_group_->basicAttack[entity].heavySpeedCurrent > 0) {
					entity_group_->basicAttack[entity].heavySpeedCurrent--;
				}
				else {
					entity_group_->attack[entity].attacking = false;
					entity_group_->active[entity].active = false;
					entity_group_->basicAttack[entity].heavySpeedCurrent = entity_group_->basicAttack[entity].heavySpeedBase;
				}
			}
			
		} else {
			// start attack
			entity_group_->active[entity].active = true;
			entity_group_->attack[entity].attacking = true;
		}
	}

	void doDamage(uint64_t entity, uint64_t target, int damage, Components::ATTACK_TYPE_DAMAGE damageType) {
		if (damageType == Components::ATTACK_TYPE_DAMAGE::NORMAL) {
			entity_group_->healthDamage[target].chunkDamage += b2Max(0, damage - entity_group_->resistance[target].normal_current);
			entity_group_->healthDamage[target].chunckDamageSource = entity;
		}
		else if (damageType == Components::ATTACK_TYPE_DAMAGE::FIRE) {
			entity_group_->healthDamage[target].chunkDamage += b2Max(0, damage - entity_group_->resistance[target].fire_current);
			entity_group_->healthDamage[target].chunckDamageSource = entity;
		}
		else if (damageType == Components::ATTACK_TYPE_DAMAGE::POISON) {
			entity_group_->healthDamage[target].incrementalDamage += b2Max(0, damage - entity_group_->resistance[target].poison_current);
			entity_group_->healthDamage[target].incrementalDamageSource = entity;
		}
	}
};

