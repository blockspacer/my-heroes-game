#pragma once
#include "Components.h"
#include "EntityManager.h"
#include "TileMap.h"
#include "Camera.h"
#include "SDLEventSender.h"
#include "SDLEventData.h"

// the two types of systems
#include "EffectSystem.h"
#include "DecisionSystem.h"

// temporary systems held here
// decision systems
#include "DecisionSystemControlTarget.h"
#include "DecisionSystemControlMovement.h"
// need target

#include "DecisionSystemDefaultTarget.h"
#include "DecisionSystemDefaultMovement.h"

// effect systems
#include "EffectSystemDefaultHealth.h"
#include "EffectSystemDefaultDeath.h"
#include "EffectSystemDefaultAction.h"
#include "EffectSystemDefaultMovement.h"
#include "EffectSystemDefaultRender.h"

#include <list>
#include <unordered_set>
#include <unordered_map>

typedef struct {
	DecisionSystem* decisionSystem;
	EffectSystem* effectSystem;
} SystemPair;

typedef std::unordered_map<uint64_t, DecisionSystem*> DecisionSystemMap;
typedef std::unordered_map<uint64_t, EffectSystem*> EffectSystemMap;
typedef std::unordered_map<uint64_t, SystemPair*> PairSystemMap;

typedef std::unordered_set<uint64_t> SetOfEntities;

class LevelManager : public SDLEventSender, public b2QueryCallback
{
public:
	LevelManager(CameraPtr cameraPtr);
	~LevelManager();

	// this will eventually take a file or something
	void loadLevel(SDL_Renderer* renderer);
	void clearLevel();
	void updateLevel();

	bool LevelManager::ReportFixture(b2Fixture* fixture);
private:
	// fuctions for processing 
	void processEffectSystem(Components::ComponentMask mask, EffectSystemMap* effectSystemMap);
	void processPairSystem(Components::ComponentMask mask, PairSystemMap* pairSystemMap);

	// temp function for making enemy hell bats
	void makeHellBat(float x, float y, SDL_Renderer* renderer);

	// health systems are only effect systems
	Components::ComponentMask health_mask_;
	EffectSystemMap systems_health_;

	// death systems are only effect systems
	Components::ComponentMask death_mask_;
	EffectSystemMap systems_death_;

	// target and action systems are a pair system (same mask because
	// if the entity performs an action is needs to be targeted or sensed)
	Components::ComponentMask target_action_mask_;
	PairSystemMap systems_target_action_;

	// movement logic and movement systems are a pair system (same mask because
	// if the entity can move it needs to decide how to move)
	Components::ComponentMask movement_mask_;
	PairSystemMap systems_movement_;

	// effect system for updating the render information about enities
	Components::ComponentMask render_mask_;
	EffectSystemMap systems_render_;

	EntityGroupPtr entity_group_;
	uint64_t main_entity_;

	TileMap* tile_map_;
	CameraPtr camera_ptr_;
	SetOfEntities camera_targets_;
	std::list<Components::ComponentRender*> render_targets_;

	// single systems examples
	// decision
	DecisionSystemDefaultTarget* default_target_;
	DecisionSystemDefaultMovement* default_movementD_;

	DecisionSystemControlTarget* control_target_;
	DecisionSystemControlMovement* control_movementD_;

	// effect
	EffectSystemDefaultHealth* default_health_;
	EffectSystemDefaultDeath* default_death_;
	EffectSystemDefaultAction* default_action_;
	EffectSystemDefaultMovement* default_movementE_;
	EffectSystemDefaultRender* default_render_;
};

