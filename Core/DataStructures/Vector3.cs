using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex
{
    public class Vector3D
    {
        public float x, y, z;
        public Vector3D(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public Vector3D()
        {
            x = 0;
            y = 0;
            z = 0;
        }
    }
}
