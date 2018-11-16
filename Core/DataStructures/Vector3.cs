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

        public static Vector3D operator /(Vector3D left, Vector3D righ)
        {
            return new Vector3D(left.x / righ.x, left.y / righ.y, left.z / righ.z);
        }

    }
}
