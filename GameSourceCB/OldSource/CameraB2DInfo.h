#pragma once
#include "stdafx.h"

// interface for getting the camera information about the b2
// world 
class CameraB2World
{
public:

	// returns the AABB that the camera is currently viewing
	virtual b2AABB getCameraSmallB2AABB() = 0;

	// returns the greater area around the camera for entity processing
	virtual b2AABB getCameraLargeB2AABB() = 0;

	// returns the b2 coordinates of the camera
	virtual b2Vec2 getCameraB2Vec2() = 0;
	virtual ~CameraB2World() {}
};

