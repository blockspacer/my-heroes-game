#include <iostream>
#include <fstream>

#include <SDL.h>

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
				SDL_assert(m_initialized);

				CleanUp();
			}

			/*
			* This method intializes the tile map based on an
			* input file which will specify tile textures and then a grid
			* which is made up from those tile textures.
			*/
			void TileMap::Load(const char* tileMapFile, SDL_Window* window, SDL_Renderer* renderer)
			{
				SDL_assert(tileMapFile != nullptr);
				SDL_assert(window != nullptr);

				if (m_initialized)
				{
					CleanUp();
				}

				std::ifstream in("TestMap.map", std::ifstream::in);

				SDL_assert(in.is_open());

				// read tile width
				SDL_assert(in >> m_worldTileWidth);
				SDL_assert(m_worldTileWidth > TileMapConstants::MIN_WORLD_TILE_SIZE);

				// read tile height
				SDL_assert(in >> m_worldTileHeight);
				SDL_assert(m_worldTileHeight > TileMapConstants::MIN_WORLD_TILE_SIZE);

				int numberOfTileTextures = 0;
				SDL_assert(in >> numberOfTileTextures);
				SDL_assert(numberOfTileTextures > 0);

				char tileFile[64];
				int tilew1 = 0;
				int tileh1 = 0;
				int tilew2 = 0;
				int tileh2 = 0;


				std::cout << "Reading Textures" << std::endl;
				in.getline(tileFile, 5);
				for (int i = 0; i < numberOfTileTextures; i++)
				{
					in.getline(tileFile, TileMapConstants::MAX_TILE_TEXTURE_FILE_SIZE);
					SDL_assert(in.fail() == false);

					// Create the surface cache
					SDL_Surface* testSurface = m_sdlUtilityTool.LoadBMP(tileFile);
					SDL_Texture* testTexture = m_sdlUtilityTool.CreateTextureFromSurface(renderer, testSurface);
					SDL_assert(testTexture != nullptr);
					m_textureCache.push_back(testTexture);
					m_sdlUtilityTool.DestroySurface(testSurface);

					// check that all tile dimensions agree
					if (i > 0)
					{
						SDL_QueryTexture(m_textureCache[i], NULL, NULL, &tilew1, &tileh1);
						SDL_QueryTexture(m_textureCache[i], NULL, NULL, &tilew2, &tileh2);
						SDL_assert(tilew1 == tileh1 && tilew2 == tileh2);
						SDL_assert(tilew1 == tilew2);

						// assign tile dimension
						if (i == 0)
						{
							m_tileDimension = tilew1;
						}
					}
				}

				std::cout << "Divisions" << std::endl;
				int tileMapValue = -1;
				for (int i = 0; i < m_worldTileWidth * m_worldHeight; i++)
				{
					m_textureMap.push_back(Position());
					SDL_assert(in >> m_textureMap[i].m_surface);
					SDL_assert(m_textureMap[i].m_surface >= 0);
					m_textureMap[i].m_x = (i % m_worldTileWidth) * m_tileDimension;
					m_textureMap[i].m_y = (i / m_worldTileWidth) * m_tileDimension;
				}

				// -----------------------------------------------
				// TEMPORARY BEGIN
				// -----------------------------------------------
				// 16 X 16 tile world
				/*m_worldWidth = 128;
				m_worldHeight = 128;

				// make sure the world is bigger than 6 X 6 tiles
				SDL_assert(m_worldWidth >= 48 && m_worldHeight >= 48);
				// -----------------------------------------------
				// TEMPORARY BEGIN
				// -----------------------------------------------

				// Create the surface cache
				SDL_Surface* testSurface = m_sdlUtilityTool.LoadBMP("D:/GameDevelopment/GameSource/Resources/Textures/TestTile.bmp");
				SDL_Texture* testTexture = m_sdlUtilityTool.CreateTextureFromSurface(renderer, testSurface);
				SDL_assert(testTexture != nullptr);
				m_textureCache.push_back(testTexture);
				m_sdlUtilityTool.DestroySurface(testSurface);

				SDL_assert(testSurface->w == testSurface->h && testSurface->w != 0);
				m_tileDimension = testSurface->w;*/

				SDL_DisplayMode displayMode;
				SDL_GetWindowDisplayMode(window, &displayMode);

				//m_worldTileWidth = (m_worldWidth * PIXEL_TO_METER) / m_tileDimension;
				//m_worldTileHeight = (m_worldHeight * PIXEL_TO_METER) / m_tileDimension;

				m_screenTileWidth = (displayMode.w / m_tileDimension) + 3;
				m_screenTileHeight = (displayMode.h / m_tileDimension) + 3;

				m_screenPixelWidth = displayMode.w;
				m_screenPixelHeight = displayMode.h;

				// prepopulate the sdl rects
				/*for (int i = 0; i < m_worldTileWidth * m_worldTileHeight; i++)
				{
					m_textureMap.push_back(Position());
					m_textureMap[i].m_surface = 0;
					m_textureMap[i].m_x = (i % m_worldTileWidth) * m_tileDimension;
					m_textureMap[i].m_y = (i / m_worldTileWidth) * m_tileDimension;
				}*/

				m_initialized = true;
			}

			void TileMap::CleanUp()
			{
				SDL_assert(m_initialized);

				for (int i = 0; i < static_cast<int>(m_textureCache.size()); i++)
				{
					m_sdlUtilityTool.DestroyTexture(m_textureCache[i]);
					m_textureCache[i] = nullptr;
				}

				m_initialized = false;
			}

			void TileMap::Render(b2Vec2& simulationPoint, SDL_Renderer* renderer)
			{
				SDL_assert(m_initialized);
				SDL_assert(m_tileDimension != 0);
				SDL_assert(renderer != nullptr);

				// first calculate the corner of the screen in world pixel coordinates
				// from the center of the camera in simulation coordinates
				PixelVector2 pixelPoint = PixelVector2(Meter2Pixel(simulationPoint.x) - (m_screenPixelWidth / 2), Meter2Pixel(simulationPoint.y) - (m_screenPixelHeight / 2));
				std::cout << simulationPoint.x << ", " << simulationPoint.y << std::endl;
				std::cout << pixelPoint.m_x << ", " << pixelPoint.m_y << std::endl;

				// Next figure out the tile for that pixel point
				int tileX = std::min(std::max(pixelPoint.m_x / m_tileDimension - 1, 0), m_worldTileWidth - m_screenTileWidth);
				int tileY = std::min(std::max(pixelPoint.m_y / m_tileDimension - 1, 0), m_worldTileHeight - m_screenTileHeight);

				SDL_Rect relative;
				relative.w = m_tileDimension;
				relative.h = m_tileDimension;
				// i => height, j => width
				for (int i = tileY; i < m_screenTileHeight + tileY; i++)
				{
					for (int j = tileX; j < m_screenTileWidth + tileX; j++)
					{
						relative.x = m_textureMap[j + (i * m_worldTileWidth)].m_x - pixelPoint.m_x;
						relative.y = m_textureMap[j + (i * m_worldTileWidth)].m_y - pixelPoint.m_y;
						SDL_RenderCopy(renderer, m_textureCache[m_textureMap[j + (i * m_worldTileWidth)].m_surface], NULL, &relative);
						//SDL_BlitSurface(m_textureCache[m_textureMap[j + (i * m_worldTileWidth)].m_surface], NULL, windowSurface, &relative);
					}
				}
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes
