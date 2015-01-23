// Heroes Game
// Author: Samuel Hall
// Last Commented 1/18/2015

#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			/*
			 * This is the ratio of 1 meter in Box2d simulation to the number of pixels on the screen.
			 * Box2d coordinates will be refered to as the simulation coordinates.
			 */
			enum ConversionScale
			{
				PIXEL_TO_SIM = 64
			};

			/*
			 * These are useful conversion functions for changing between pixel and simulation coordinates
			 */
			float Pixel2Meter(int pixel);
			int Meter2Pixel(float sim);

			/*
			 * This is a useful struct for storing pixel coordinates. Creates common data type since
			 * Box2d has the b2vector class which holds a pair of doubles.
			 */
			struct PixelVector2
			{
				PixelVector2(int x, int y)
				{
					m_x = x;
					m_y = y;
				}

				int m_x;
				int m_y;
			};
				
		} // namespace GamePlay
	} // namespace States
} //namespace Heroes