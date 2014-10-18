#pragma once
#include "stdafx.h"
#include <list>

// file for all the component structs and unique enums for each component
namespace Components {

	static const size_t NUMBER_OF_COMPONENTS = 50;

	using std::string;
	using std::bitset;

	typedef std::bitset<NUMBER_OF_COMPONENTS> ComponentMask;

	static const ComponentMask C_NONE(                 string("00000000000000000000000000000000000000000000000000"));
	static const ComponentMask C_HEALTH(               string("01000000000000000000000000000000000000000000000000"));
	static const ComponentMask C_HEALTH_DAMAGE(        string("00100000000000000000000000000000000000000000000000"));
	static const ComponentMask C_RESISTANCE(           string("00010000000000000000000000000000000000000000000000"));
	static const ComponentMask C_REGENERATE(           string("00001000000000000000000000000000000000000000000000"));
	static const ComponentMask C_RECOIL(               string("00000100000000000000000000000000000000000000000000"));
	static const ComponentMask C_DEATH(                string("00000010000000000000000000000000000000000000000000"));
	static const ComponentMask C_ACTIVE(               string("00000001000000000000000000000000000000000000000000"));

	static const ComponentMask C_PHYSICS(              string("00000000100000000000000000000000000000000000000000"));
	static const ComponentMask C_MOVEMENT_ORIENTATION( string("00000000010000000000000000000000000000000000000000"));
	static const ComponentMask C_MOVEMENT_SPEED(       string("00000000001000000000000000000000000000000000000000"));

	static const ComponentMask C_VISION_TARGET(        string("00000000000100000000000000000000000000000000000000"));
	static const ComponentMask C_VISION_SENSORS(       string("00000000000010000000000000000000000000000000000000"));
	static const ComponentMask C_VISION_ORIENTATION(   string("00000000000001000000000000000000000000000000000000"));
	
	static const ComponentMask C_ATTACK(               string("00000000000000100000000000000000000000000000000000"));
	static const ComponentMask C_BASICATTACK(          string("00000000000000010000000000000000000000000000000000"));

	static const ComponentMask C_RENDER(               string("00000000000000001000000000000000000000000000000000"));

	// Health
	typedef struct {
		int base;
		int current;
	} ComponentHealth;

	typedef struct {
		int chunkDamage;
		uint64_t chunckDamageSource;
		int incrementalDamage;
		int incrementalRate;
		uint64_t incrementalDamageSource;
	} ComponentHealthDamage;

	typedef struct {
		int normal_base;
		int normal_current;
		int fire_base;
		int fire_current;
		int poison_base;
		int poison_current;
	} ComponentResistance;

	typedef struct {
		int base;
		int countDown;
		int rate;
	} ComponentRegenerate;

	typedef struct {
		int base;
		int countDown;
	} ComponentRecoil;

	typedef struct {
		bool death;
		int countDown;
	} ComponentDead;

	typedef struct {
		bool active;
	} ComponentActive;

	typedef struct {
		b2Body* body;
		std::list<b2Shape*> shapes;
	} ComponentPhysics;

	typedef struct {
		b2Vec2 orientation;
	} ComponentMovementOrientation;

	typedef struct {
		float baseMax;
		float currentMax;
		float current;
	} ComponentMovementSpeed;

	typedef struct {
		int target;
		float targetDistance;
		float trackingRange;
	} ComponentVisionTarget;

	typedef struct {
		b2Joint* connectionJoint;
		b2Body* visionBody;
		b2Shape* smallSightShape;
		b2FixtureDef smallSightFixDef;
		b2Shape* largeSightShape;
		b2FixtureDef largeSightFixDef;
	} ComponentVisionSensors;

	typedef struct {
		b2Vec2 orientation;
	} ComponentVisionOrientation;

	enum ATTACK_TYPE_DAMAGE {
		NORMAL = 0,
		FIRE = 1,
		POISON = 2
	};

	enum ATTACK_TYPE {
		LIGHT = 0,
		HEAVY = 1,
		SPECIAL = 2
	};

	typedef struct {
		bool attacking;
		ATTACK_TYPE attackType;
		int kills;
	} ComponentAttack;

	typedef struct {
		ATTACK_TYPE_DAMAGE lightType;
		float lightRange;
		uint8_t lightDamage;
		uint8_t lightSpeedDamagePoint;
		uint8_t lightSpeedCurrent;
		uint8_t lightSpeedBase;

		ATTACK_TYPE_DAMAGE heavyType;
		float heavyRange;
		uint8_t heavyDamage;
		uint8_t heavySpeedDamagePoint;
		uint8_t heavySpeedCurrent;
		uint8_t heavySpeedBase;
	} ComponentBasicAttack;

	typedef struct {
		// life bar stuff
		SDL_Rect lifeBarBack;
		SDL_Color colorLifeBarBack;
		SDL_Rect lifeBar;
		SDL_Color colorLifeBar;

		// sprite stuff
		SDL_Rect rectWorld;
		SDL_Rect rectTexture; // images that contain multiple frames
		SDL_Texture* texture;
	} ComponentRender;
}

