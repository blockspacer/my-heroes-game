#pragma once
#include "stdafx.h"
#include "Components.h"

// The max amount of entities (just a number)
static const uint64_t MAX_ENTITIES = 300;

// struct for a mask node
struct MaskNode_str;
typedef MaskNode_str MaskNode;

enum ENTITY_COLLISION_CATEGORIES {
	ENVIRONMENT_BODY = 0x0001,
	ALLY_SENSOR = 0x0002,
	ENEMY_BODY = 0x0004,
	ENEMY_SENSOR = 0x0008,
	ALLY_BODY = 0x0010,
	ENVIRONMENT_SENSOR = 0x0020
};

static const uint16_t ALLY_BODY_COL = ALLY_BODY | ENEMY_BODY | ENEMY_SENSOR | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR;
static const uint16_t ALLY_SENSOR_COL = ENEMY_BODY;
static const uint16_t ENEMY_BODY_COL = ALLY_BODY | ALLY_SENSOR | ENEMY_BODY | ENVIRONMENT_BODY | ENVIRONMENT_SENSOR;
static const uint16_t ENEMY_SENSOR_COL = ALLY_BODY;
static const uint16_t ENVIRONMENT_BODY_COL = ALLY_BODY | ENEMY_BODY | ENVIRONMENT_BODY;
static const uint16_t ENVIRONMENT_SENSOR_COL = ALLY_BODY | ENEMY_BODY;

struct MaskNode_str {
	std::bitset<Components::NUMBER_OF_COMPONENTS> mask;
	uint64_t index;
	MaskNode* next;
	MaskNode* prev;
	bool free;
};

// This is the core data of the game!
// It holds the b2World and all the entities which
// are defined by thier data and mask
typedef struct {

	// The physics simulation world
	b2World* world;

	// should only need free nodes
	MaskNode* freeNodes;
	MaskNode* usedNodes;

	// The ENTITY DATA (NEEDS TO BE OPTIMIZED)
	MaskNode maskList[MAX_ENTITIES];

	// general
	Components::ComponentActive              active[MAX_ENTITIES];
	
	// health
	Components::ComponentHealth              health[MAX_ENTITIES];
	Components::ComponentHealthDamage        healthDamage[MAX_ENTITIES];
	Components::ComponentResistance          resistance[MAX_ENTITIES];	
	Components::ComponentRegenerate          regenerate[MAX_ENTITIES];
	Components::ComponentRecoil              recoil[MAX_ENTITIES];
	Components::ComponentDead                death[MAX_ENTITIES];

	Components::ComponentPhysics             physics[MAX_ENTITIES];
	Components::ComponentMovementOrientation movementOrientation[MAX_ENTITIES];
	Components::ComponentMovementSpeed       movementSpeed[MAX_ENTITIES];

	Components::ComponentVisionTarget        visionTarget[MAX_ENTITIES];
	Components::ComponentVisionSensors       visionSensor[MAX_ENTITIES];
	Components::ComponentVisionOrientation   visionOrientation[MAX_ENTITIES];

	Components::ComponentAttack              attack[MAX_ENTITIES];
	Components::ComponentBasicAttack         basicAttack[MAX_ENTITIES];

	Components::ComponentRender              render[MAX_ENTITIES];

} EntityGroup;

typedef uint64_t EntityID;
typedef EntityGroup* EntityGroupPtr;

