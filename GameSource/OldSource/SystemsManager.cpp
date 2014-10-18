#include "stdafx.h"
#include "SystemsManager.h"
#include "SystemMasks.h"

SystemsManager::SystemsManager()
{
	// call functions to create each of the masks for the respective System
	SetHealthMask(&health_mask_);
	SetDeathMask(&death_mask_);
	//.... TODO
}


SystemsManager::~SystemsManager()
{
}
