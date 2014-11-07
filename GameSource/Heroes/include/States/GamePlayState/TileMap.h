#pragma once

#include <vector>

#include <Box2D/Box2D.h>

#include "Engine/SDLUtilityTool.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			// type for dynamix surface ids
			typedef int SurfaceIDType;
			typedef int TilePositionType;

			enum TileMapConstants
			{
				MAX_TILE_TEXTURE_FILE_SIZE = 64, // max size for any tile texture file name
				MIN_WORLD_TILE_SIZE = 5 // minimum dimension a world can be in tiles
			};

			/*
			 * This struct represent a Tile which is a position in the world and 
			 * a tile texture.
			 */
			struct TileInfoType {
				SurfaceIDType m_surface;
				TilePositionType m_x;
				TilePositionType m_y;
			};

			/*
			 * The TileMap is the background for the game it has not interaction with
			 * any of the entities. Currently the TileMap is always in the shape of a rectangle
			 */
			class TileMap final
			{

			public:
				/* Representation:
				 * A tile map is a grid of 512 pixel squares that represent
				 * the ground in the game. The pixels start at (0,0) being the
				 * upper left corner going to the current max size of the width
				 * and height of the grid.
				 */

				/*
				 * Constructor requires a SDLUtilityTool.
				 */
				TileMap(Engine::SDLUtilityTool& sdlUtilityTool);
				~TileMap();

				/*
				 * This method intializes the tile map based on an
				 * input file which will specify tile textures and then a grid
				 * which is made up from those tile textures.
				 *
				 * TileMap file format
				 * -----------------------------------
				 * < world tile size x >
				 * < world tile size y >
				 * < number of different tile textures (n) >
				 * < tile texture file for surface ID 0 >
				 * < tile texture file for surface ID 1 >
				 * < tile texture file for surface ID ... >
				 * < an x by y grid of numbers 0 -> (n - 1), example n = 3
				 * 0 0 0 1 1 1 0
				 * 0 0 0 1 1 1 1
				 * 2 2 0 0 1 1 0
				 * 0 2 2 0 0 1 1
				 * 0 2 2 2 0 1 0
				 * 0 0 2 2 0 0 1
				 * 0 0 2 2 0 0 1 >
				 * -----------------------------------
				 *
				 */
				void Load(const char* tileMapFile, SDL_Window* window, SDL_Renderer* renderer);

				/*
				 * Draws the TileMap based on a pixel location, the pixel location should
				 * represent the center and the tiles should be drawn using the screen dimensions
				 * and that pixel coordinate.
				 */
				void Render(b2Vec2& simulationPoint, SDL_Renderer* renderer);

			private:

				/*
				 * This cleans up the TileMap's resources. Assumes that
				 * a vaild file has been loaded.
				 */
				void CleanUp();

				Engine::SDLUtilityTool& m_sdlUtilityTool;

				bool m_initialized{ false };

				// These are variables that help with quick TileMap rendering
				int m_worldWidth{ 0 };
				int m_worldHeight{ 0 };

				int m_worldTileHeight{ 0 };
				int m_worldTileWidth{ 0 };

				int m_screenTileHeight{ 0 };
				int m_screenTileWidth{ 0 };

				int m_screenPixelWidth{ 0 };
				int m_screenPixelHeight{ 0 };

				int m_tileDimension{ 0 };

				std::vector<SDL_Texture*> m_textureCache; // This hold the textures for a given TileMap
				std::vector<TileInfoType> m_textureMap; // This holds information about each tile
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
