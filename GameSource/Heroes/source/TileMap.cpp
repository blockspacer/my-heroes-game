#include <iostream>
#include <fstream>

#include <Engine/SDLUtilityTool.h>

#include "Engine/Log.h"

#include "States/GamePlayState/b2Conversion.h"
#include "States/GamePlayState/TileMap.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			// Needs sdl utility tool
			TileMap::TileMap(Engine::SDLUtilityTool& sdlUtilityTool) : m_sdlUtilityTool(sdlUtilityTool) {}

			TileMap::~TileMap()
			{
				g_assert(m_initialized);

				CleanUp();
			}

			/*
			* This method intializes the tile map based on an
			* input file which will specify tile textures and then a grid
			* which is made up from those tile textures.
			*/
			void TileMap::Load(const char* tileMapFile, SDL_Window* window, SDL_Renderer* renderer)
			{
				g_assert(tileMapFile != nullptr);
				g_assert(window != nullptr);

				// if a tile map has already been intialized clean it up
				if (m_initialized)
				{
					CleanUp();
				}

				// open file
				std::ifstream in(tileMapFile, std::ifstream::in);
				g_assert(in.is_open());

				// read tile width
				g_assert(in >> m_worldTileWidth);
				g_assert(m_worldTileWidth >= TileMapConstants::MIN_WORLD_TILE_SIZE);

				// read tile height
				g_assert(in >> m_worldTileHeight);
				g_assert(m_worldTileHeight >= TileMapConstants::MIN_WORLD_TILE_SIZE);

				int numberOfTileTextures = 0;
				g_assert(in >> numberOfTileTextures);
				g_assert(numberOfTileTextures > 0);

				// array for tile file names
				char tileFile[64];

				// variables to check tile dimensions match
				int tilew1 = 0;
				int tileh1 = 0;
				int tilew2 = 0;
				int tileh2 = 0;

				in.getline(tileFile, 1); // read empty line

				// go through the number of different texture and load them into the tile map
				for (int i = 0; i < numberOfTileTextures; i++)
				{
					in.getline(tileFile, TileMapConstants::MAX_TILE_TEXTURE_FILE_SIZE);
					g_assert(in.fail() == false);

					// Create the surface cache
					SDL_Texture* testTexture = m_sdlUtilityTool.LoadImageTexture(tileFile, renderer);
					g_assert(testTexture != nullptr);
					m_textureCache.push_back(testTexture);

					// check that all tile dimensions agree for each i and i + 1
					if (i > 0)
					{
						SDL_QueryTexture(m_textureCache[i - 1], NULL, NULL, &tilew1, &tileh1);
						SDL_QueryTexture(m_textureCache[i], NULL, NULL, &tilew2, &tileh2);
						g_assert(tilew1 == tileh1 && tilew2 == tileh2);
						g_assert(tilew1 == tilew2);
						
					}

					// assign tile dimension
					if (i == 0)
					{
						SDL_QueryTexture(m_textureCache[i], NULL, NULL, &tilew1, &tileh1);
						m_tileDimension = tilew1;
					}

					g_Log_Write_L2(LOG_FILE_LOAD_EVENT, tileMapFile);
				}

				// assign the positions of each tile
				int tileMapValue = -1;
				for (int i = 0; i < m_worldTileWidth * m_worldTileHeight; i++)
				{
					m_textureMap.push_back(TileInfoType());
					g_assert(in >> m_textureMap[i].m_surface);
					g_assert(m_textureMap[i].m_surface >= 0);
					m_textureMap[i].m_x = (i % m_worldTileWidth) * m_tileDimension;
					m_textureMap[i].m_y = (i / m_worldTileWidth) * m_tileDimension;
				}

				// get the screen dimensions for showing the tilemap
				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(window, &displayMode);

				m_screenTileWidth = (displayMode.w / m_tileDimension) + 3;
				m_screenTileHeight = (displayMode.h / m_tileDimension) + 3;

				m_screenPixelWidth = displayMode.w;
				m_screenPixelHeight = displayMode.h;

				m_initialized = true;
			}

			void TileMap::CleanUp()
			{
				g_assert(m_initialized);

				for (int i = 0; i < static_cast<int>(m_textureCache.size()); i++)
				{
					g_assert(m_textureCache[i] != nullptr);
					m_sdlUtilityTool.DestroyTexture(m_textureCache[i]);
					m_textureCache[i] = nullptr;
				}

				g_Log_Write_L2(LOG_FILE_UNLOAD_EVENT, "Cleaned up Map File in TileMap");
				m_initialized = false;
			}

			void TileMap::Render(b2Vec2& simulationPoint, SDL_Renderer* renderer)
			{
				g_assert(m_initialized);
				g_assert(m_tileDimension != 0);
				g_assert(renderer != nullptr);

				// first calculate the corner of the screen in world pixel coordinates
				// from the center of the camera in simulation coordinates
				PixelVector2 pixelPoint = PixelVector2(Meter2Pixel(simulationPoint.x) - (m_screenPixelWidth / 2), Meter2Pixel(simulationPoint.y) - (m_screenPixelHeight / 2));

				// Next figure out the tile for that pixel point
				int tileX = std::min(std::max(pixelPoint.m_x / m_tileDimension - 1, 0), m_worldTileWidth - m_screenTileWidth);
				int tileY = std::min(std::max(pixelPoint.m_y / m_tileDimension - 1, 0), m_worldTileHeight - m_screenTileHeight);

				SDL_Rect relative;
				relative.w = m_tileDimension;
				relative.h = m_tileDimension;
				// i => height, j => width
				// Loops through the tiles in the vision region and draw thier respective tile textures
				for (int i = tileY; i < m_screenTileHeight + tileY; i++)
				{
					for (int j = tileX; j < m_screenTileWidth + tileX; j++)
					{
						relative.x = m_textureMap[j + (i * m_worldTileWidth)].m_x - pixelPoint.m_x;
						relative.y = m_textureMap[j + (i * m_worldTileWidth)].m_y - pixelPoint.m_y;
						SDL_RenderCopy(renderer, m_textureCache[m_textureMap[j + (i * m_worldTileWidth)].m_surface], NULL, &relative);
					}
				}
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
