using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// for conversions
using FarseerPhysics;

namespace Heroes
{
    class PointSim
    {
        public PointSim(float x, float y)
        {
            X = x;
            Y = y;
        }

        public PointSim(PointSim p)
        {
            X = p.X;
            Y = p.Y;
        }

        public PointSim(PointSim p, float diff_x, float diff_y)
        {
            X = p.X + diff_x;
            Y = p.Y + diff_y;
        }

        public PointDis GetDisplayPoint()
        {
            return new PointDis((int)ConvertUnits.ToDisplayUnits(X), (int)ConvertUnits.ToDisplayUnits(Y));
        }

        public Microsoft.Xna.Framework.Vector2 GetVector2()
        {
            return new Microsoft.Xna.Framework.Vector2(X, Y);
        }

        public float X;
        public float Y;
    }
}
