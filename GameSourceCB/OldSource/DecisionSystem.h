#pragma once
#include "stdafx.h"
#include "EntityGroup.h"

class DecisionSystem
{
public:
	~DecisionSystem() {}
	virtual bool updateSystem(uint64_t entity) = 0;

protected:
	EntityGroupPtr entity_group_;
};

