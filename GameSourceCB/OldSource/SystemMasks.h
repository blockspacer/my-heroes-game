#pragma once
#include "stdafx.h"
#include "Components.h"

// This file contains the functions to call to to set bitsets to respective masks

// HEALTH MASK
static bool SetHealthMask(Components::ComponentMask* mask) {
	if (mask == NULL) {
		return false;
	}

	// set the mask
	*mask = Components::C_HEALTH | Components::C_HEALTH_DAMAGE | Components::C_RESISTANCE |
		    Components::C_REGENERATE | Components::C_RECOIL | Components::C_DEATH |
		    Components::C_ACTIVE;

	// successful assignment
	return true;
}

// DEATH MASK
static bool SetDeathMask(Components::ComponentMask* mask) {
	if (mask == NULL) {
		return false;
	}

	// set the mask
	*mask = Components::C_DEATH | Components::C_PHYSICS | Components::C_RENDER |
		    Components::C_VISION_SENSORS;

	// successful assignment
	return true;
}

// AI ACTION MASK
static bool SetAIActionMask(Components::ComponentMask* mask) {
	if (mask == NULL) {
		return false;
	}

	// set the mask
	*mask = Components::C_ACTIVE | Components::C_DEATH | Components::C_PHYSICS |
		Components::C_VISION_ORIENTATION | Components::C_VISION_SENSORS |
		Components::C_VISION_TARGET | Components::C_ATTACK | Components::C_BASICATTACK;

	// successful assignment
	return true;
}

// ACTION MASK
static bool SetActionhMask(Components::ComponentMask* mask) {
	if (mask == NULL) {
		return false;
	}

	// set the mask
	*mask = Components::C_ACTIVE | Components::C_DEATH | Components::C_PHYSICS |
		    Components::C_VISION_ORIENTATION | Components::C_VISION_SENSORS |
		    Components::C_VISION_TARGET | Components::C_ATTACK | Components::C_BASICATTACK;

	// successful assignment
	return true;
}

static bool SetHealthMask(Components::ComponentMask* mask) {
	if (mask == NULL) {
		return false;
	}

	// set the mask
	*mask = Components::C_HEALTH | Components::C_HEALTH_DAMAGE | Components::C_RESISTANCE |
		Components::C_REGENERATE | Components::C_RECOIL | Components::C_DEATH |
		Components::C_ACTIVE;

	// successful assignment
	return true;
}