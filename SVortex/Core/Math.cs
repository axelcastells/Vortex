using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SVortex
{
    public static class VMath
    {
        public static float Clamp(float value, float min, float max)
        {
            return (value < min) ? min : (value > max) ? max : value;
        }
    }
}
