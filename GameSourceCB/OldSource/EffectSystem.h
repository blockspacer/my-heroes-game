#pragma once
#include "stdafx.h"
#include "EntityGroup.h"

class EffectSystem
{
public:
	virtual ~EffectSystem() {}
	virtual void updateSystem(uint64_t entity) = 0;

protected:
	EntityGroupPtr entity_group_;
};

