using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// for conversions
using FarseerPhysics;

namespace Heroes
{
    class PointDis
    {
        public PointDis(int x, int y)
        {
            X = x;
            Y = y;
        }

        public PointSim GetSimPoint()
        {
            return new PointSim(ConvertUnits.ToSimUnits((float)X), ConvertUnits.ToSimUnits((float)Y));
        }

        public int X;
        public int Y;
    }
}
