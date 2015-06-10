#pragma once
#include "stdafx.h"

// interface for getting the information about the camera
class CameraPixelInfo
{
public:

	// returns the pixel region of viewing (screen size)
	virtual SDL_Rect* getCameraRect() = 0;

	// returns a pointer to a rect that contains the values of the rect
	// values should be copied if additional calls are going to be
	// made
	virtual void getRelativeCameraRect(SDL_Rect* rectSrc, SDL_Rect* rectDst) = 0;

	virtual ~CameraPixelInfo() {}
};

