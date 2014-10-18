#pragma once
#include "CameraPixelInfo.h"

class DrawableTileMap
{
public:
	virtual void draw(SDL_Renderer* renderer, CameraPixelInfo* cameraPixelInfo) = 0;
	virtual ~DrawableTileMap() {}
protected:
};

