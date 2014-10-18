#pragma once

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			enum ConversionScale
			{
				PIXEL_TO_METER = 64
			};

			float Pixel2Meter(int pixel);

			int Meter2Pixel(float sim);

			// struct for storing the center of the camera in pixel coordinates
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