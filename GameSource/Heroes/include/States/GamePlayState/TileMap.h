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
			typedef int SurfaceIDType;

			enum TileMapConstants
			{
				MAX_TILE_TEXTURE_FILE_SIZE = 64,
				MIN_WORLD_TILE_SIZE = 6
			};

			struct Position {
				int m_surface;
				int m_x;
				int m_y;
				// probable a texture field
			};

			class TileMap final
			{

			public:
				/* Representation:
				 * A tile map is a grid of 512 pixel squares that represent
				 * the ground in the game. The pixels start at (0,0) being the
				 * upper left corner going to the current max size of the width
				 * and height of the grid.
				 */

				TileMap(Engine::SDLUtilityTool& sdlUtilityTool);
				~TileMap();

				/*
				 * This method intializes the tile map based on an
				 * input file which will specify tile textures and then a grid
				 * which is made up from those tile textures.
				 */
				void Load(const char* tileMapFile, SDL_Window* window, SDL_Renderer* renderer);

				/*
				 * Draws the TileMap based on a pixel location, the pixel location should
				 * represent the center and the tiles should be drawn using the screen dimensions
				 * and that pixel coordinate.
				 */
				void Render(b2Vec2& simulationPoint, SDL_Renderer* renderer);

			private:

				void CleanUp();

				Engine::SDLUtilityTool& m_sdlUtilityTool;

				bool m_initialized{ false };

				int m_worldWidth{ 0 };
				int m_worldHeight{ 0 };

				int m_worldTileHeight{ 0 };
				int m_worldTileWidth{ 0 };

				int m_screenTileHeight{ 0 };
				int m_screenTileWidth{ 0 };

				int m_screenPixelWidth{ 0 };
				int m_screenPixelHeight{ 0 };

				int m_tileDimension{ 0 };

				std::vector<SDL_Texture*> m_textureCache;
				std::vector<Position> m_textureMap;
			};

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
