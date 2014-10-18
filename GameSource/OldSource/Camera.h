#pragma once
#include "stdafx.h"
#include "CameraPixelInfo.h"
#include "CameraB2DInfo.h"

class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

// This camera is interface for b2 world coordinates to pixel coordinate for 
// the screen, implements various interfaces for drawing game entities and
// getting info about the camera for drawing anything that is not an entity
class Camera : public CameraPixelInfo, public CameraB2World
{
public:
	Camera() {
		pixel_region_.w = 0;
		pixel_region_.h = 0;
		pixel_region_.x = 0;
		pixel_region_.y = 0;
	}

	~Camera() {}

	// intializes the camera with a window and sets it to point at the
	// origin (0,0) in both the pixel world and the b2 world
	void init(SDL_Window* window) {
		SDL_DisplayMode displayMode;
		SDL_GetWindowDisplayMode(window, &displayMode);

		// intializes the camera to point at 0,0
		pixel_region_.w = displayMode.w;
		pixel_region_.h = displayMode.h;
		pixel_region_.x = - displayMode.w / 2;
		pixel_region_.y = displayMode.h / 2;

		// bounds are reversed from sdl rects (confusing), 5's are to make the transition nice 
		B2DRegion_small_.lowerBound = b2Vec2(-displayMode.w / static_cast<float>(2.0 * 64) - 5, -displayMode.h / static_cast<float>(2.0 * 64) - 5);
		B2DRegion_small_.upperBound = b2Vec2(displayMode.w / static_cast<float>(2.0 * 64) + 5, displayMode.h / static_cast<float>(2.0 * 64) + 5);

		B2DRegion_large_.lowerBound = b2Vec2(-displayMode.w * 3 / static_cast<float>(2.0 * 64), -displayMode.h * 3 / static_cast<float>(2.0 * 64));
		B2DRegion_large_.upperBound = b2Vec2(displayMode.w * 3 / static_cast<float>(2.0 * 64), displayMode.h * 3 / static_cast<float>(2.0 * 64));
	}

	void update(b2Vec2 cameraLocation) {
		
		// updates the b2 data by incrementing change
		b2Vec2 oldCenter = B2DRegion_small_.GetCenter();

		float changeX = cameraLocation.x - oldCenter.x;
		float changeY = cameraLocation.y - oldCenter.y;

		// update B2 region
		B2DRegion_small_.lowerBound.x += changeX;
		B2DRegion_small_.lowerBound.y += changeY;

		B2DRegion_small_.upperBound.x += changeX;
		B2DRegion_small_.upperBound.y += changeY;

		B2DRegion_large_.lowerBound.x += changeX;
		B2DRegion_large_.lowerBound.y += changeY;

		B2DRegion_large_.upperBound.x += changeX;
		B2DRegion_large_.upperBound.y += changeY;

		pixel_region_.x += static_cast<int>(changeX * 64);
		pixel_region_.y += static_cast<int>(changeY * 64);

	}

	// cameraPixelInfo override
	virtual SDL_Rect* getCameraRect() { return &pixel_region_; }
	virtual void getRelativeCameraRect(SDL_Rect* rectSrc, SDL_Rect* rectDst) {
		// determine a rect in association with the screen
		// only interesting in the position of the rect with the camera rect
		rectDst->w = rectSrc->w;
		rectDst->h = rectSrc->h;
		rectDst->x = rectSrc->x - pixel_region_.x;
		rectDst->y = pixel_region_.y - rectSrc->y;
	}

	// cameraB2DInfo
	virtual b2AABB getCameraSmallB2AABB() { return B2DRegion_small_; }
	virtual b2AABB getCameraLargeB2AABB() { return B2DRegion_large_; }
	virtual b2Vec2 getCameraB2Vec2() { return B2DRegion_small_.GetCenter(); }

private:
	SDL_Rect pixel_region_;
	b2AABB B2DRegion_small_;
	b2AABB B2DRegion_large_;
};



