#pragma once
#include "stdafx.h"
#include "DrawableTileMap.h"
#include "Box2DPixelInfo.h"
#include <string>

//#define TILE_SIZE 512
//#define MAP_WIDTH 10

typedef struct {
	int x;
	int y;
	// probable a texture field
} Position;

typedef Position** TileGrid;

// This class represents the underlying image map of a level
class TileMap : public DrawableTileMap
{
public:
	// Constructor does nothing.
	TileMap() {
		tile_grid_ = NULL;
		tile_grid_width_ = 0;
		tile_grid_height_ = 0;
		texture_ = NULL;
		texture_dim_ = 0;
	}

	~TileMap() {
		if (texture_ != NULL) {
			SDL_DestroyTexture(texture_);

			// delete the sdl rects
			for (int i = 0; i < tile_grid_width_; i++) {
				delete[] tile_grid_[i];
			}
			delete[] tile_grid_;
		}
	}

	// Initiates the TileMap based on a texture file to load from and the width and 
	// height of the world
	// NOTE: currently 512x512 images are the only working and world dimensions
	// have to be multples of 8 since the pixel to meter ratio is PIXEL_TO_B2D_RATIO
	void init(SDL_Renderer* renderer, const char* textureFile, float worldWidth, float worldHeight) {
		assert(renderer != NULL);

		// load the texture 
		// TODO change to some file that has data
		texture_ = IMG_LoadTexture(renderer, textureFile);
		assert(texture_ != NULL);

		int textureWidth;
		int textureHeight;
		SDL_QueryTexture(texture_, NULL, NULL, &textureWidth, &textureHeight);

		assert(textureWidth == textureHeight); // textures are squares
		assert(textureWidth % PIXEL_TO_B2D_RATIO == 0); // texture represents multiple of meters in b2 world
		texture_dim_ = textureWidth;
		
		// create the grid of textures
		tile_grid_width_ = static_cast<int>(std::ceilf(worldWidth * PIXEL_TO_B2D_RATIO / (texture_dim_)));
		tile_grid_height_ = static_cast<int>(std::ceilf(worldHeight * PIXEL_TO_B2D_RATIO / (texture_dim_)));

		// create the map as sdl rects of 512 pixel chunks with 
		// one texture to act as each chunck
		int maxY = static_cast<int>(worldHeight * PIXEL_TO_B2D_RATIO);

		tile_grid_ = new Position*[tile_grid_width_];
		for (int i = 0; i < tile_grid_width_; i++) {
			tile_grid_[i] = new Position[tile_grid_height_];
			for (int j = 0; j < tile_grid_height_; j++) {
				tile_grid_[i][j].x = i * texture_dim_;
				tile_grid_[i][j].y = maxY - (j * texture_dim_);
			}
		}
	}

	// assumes the camera coordinates are in within safe boundaries
	virtual void draw(SDL_Renderer* renderer, CameraPixelInfo* cameraPixelInfo) {
		assert(renderer != NULL);
		assert(cameraPixelInfo != NULL);

		SDL_Rect* cameraRegion = cameraPixelInfo->getCameraRect();

		int indexX = (cameraRegion->x / texture_dim_);
		int indexY = tile_grid_height_ - 1 - (cameraRegion->y / texture_dim_); // reverse y since increase is down

		// determine the number of tiles that need to be shown up to a max of the max tile width index
		int tilesX = (cameraRegion->w / texture_dim_) + 2;
		int tilesY = (cameraRegion->h / texture_dim_) + 2;

		// match the size
		SDL_Rect rect;
		rect.w = texture_dim_;
		rect.h = texture_dim_;

		SDL_Rect relative; // fields dont matter

		for (int i = 0; i < tilesX; i++) {
			for (int j = 0; j < tilesY; j++) {
				int x = i + indexX;
				int y = j + indexY;

				// test for whether the tile should be drawn
				if (x >= 0 && x < tile_grid_width_ && y >= 0 && y < tile_grid_height_) {
					// grab position and put in a rect for camera relative method
					rect.x = tile_grid_[x][y].x;
					rect.y = tile_grid_[x][y].y;
					cameraPixelInfo->getRelativeCameraRect(&rect, &relative);
					SDL_RenderCopy(renderer, texture_, NULL, &relative);
				}
			}
		}
	}

private:
	// grid based on double pointers so the width
	// and height are also nessacaery
	TileGrid tile_grid_;
	int tile_grid_width_;
	int tile_grid_height_;

	// todo figure out to hold mutiple containers
	SDL_Texture* texture_;
	int texture_dim_;

};

