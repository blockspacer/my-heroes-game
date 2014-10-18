#include <math.h>

#include "States/GamePlayState/b2Conversion.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{
			float Pixel2Meter(int pixel)
			{
				return (1.0f * pixel) / ConversionScale::PIXEL_TO_METER;
			}

			int Meter2Pixel(float sim)
			{
				return static_cast<int>(ceilf(sim * ConversionScale::PIXEL_TO_METER));
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes