using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Vortex;

namespace Vortex.Math
{
    public static class VMath
    {
        public static double Magnitude(Vector3D v)
        {
            return System.Math.Sqrt(System.Math.Pow(v.x, 2) + System.Math.Pow(v.y, 2) + System.Math.Pow(v.z, 2));
        }

        public static double DotProduct(Vector3D v1, Vector3D v2)
        {
            return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        }

        public static Vector3D CrossProduct(Vector3D a, Vector3D b)
        {
            return new Vector3D(a.x * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }

        public static Vector3D Normalize(Vector3D v)
        {
            return v / Magnitude(v);
        }
    }
}
