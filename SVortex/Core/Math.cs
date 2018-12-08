using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex
{
    public static class VMath
    {
        public const float Deg2Rad = 0.0174532924F;
        public const float Rad2Deg = 57.29578F;

        public static float Clamp(float value, float min, float max)
        {
            return (value < min) ? min : (value > max) ? max : value;
        }
    }
}
