using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex
{
    [System.Serializable]
    public class Transform
    {
        public Vector3 position;
        //public Vector3 eulerAngles;// { get { return rotation.e} }
        internal Quaternion rotation;
        public Transform transform { get { return this; } set { } }


        public Transform() {
            position = Vector3.Zero();
            //eulerAngles = Vector3.Zero();
            rotation = new Quaternion();
        }
        public Transform(Vector3 p, Vector3 r) { position = p; /*eulerAngles = r;*/ }
    }

    [System.Serializable]
    public class Vector3
    {
        // Properties:
        public float x, y, z;
        public Vector3 Normalized { get { return Normalize(this); } }
        // Functions:
        public Vector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
        public Vector3() { }
        public Vector3(float _val) { x = y = z = _val; }
        ~Vector3() { }

        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            Vector3 v = new Vector3();
            v.x = v1.x + v2.x;
            v.y = v1.y + v2.y;
            v.z = v1.z + v2.z;
            return v;
        }

        public static Vector3 operator /(Vector3 v1, float f)
        {
            return new Vector3(v1.x / f, v1.y / f, v1.z / f);
        }

        public static Vector3 Normalize(Vector3 _v)
        {
            float mod = (float)System.Math.Sqrt(System.Math.Pow(_v.x, 2) + System.Math.Pow(_v.y, 2) + System.Math.Pow(_v.z, 2));
            _v.x /= mod;
            _v.y /= mod;
            _v.z /= mod;
            return _v;
        }

        public static Vector3 Cross(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
        }

        public static float Dot(Vector3 v1, Vector3 v2)
        {
            return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
        }

        public static Vector3 Zero() { return new Vector3(0); }
        public static Vector3 One() { return new Vector3(1); }

        public static float Magnitude(Vector3 v)
        {
            return (float)Math.Sqrt(Math.Pow(v.x, 2) + Math.Pow(v.y, 2) + Math.Pow(v.z, 2));
        }
    }

    [System.Serializable]
    public class AxisAngle
    {
        // Properties:
        public float x, y, z, angle;

        // Functions:
        public AxisAngle() { x = y = z = angle = 0; }
        public AxisAngle(Vector3 _axis, float _angle)
        {
            x = _axis.x; y = _axis.y; z = _axis.z; angle = _angle;
        }
        public AxisAngle(float _x, float _y, float _z, float _angle)
        {
            x = _x; y = _y; z = _z; angle = _angle;
        }
        ~AxisAngle() { }
    }

    [System.Serializable]
    internal class Quaternion
    {
        // Properties:
        private float w, x, y, z;
        public Quaternion Normalized { get { return Normalize(this); } }

        // Functions:
        public Quaternion() { w = 1; x = 0; y = 0; z = 0; }
        public Quaternion(float _w, float _x, float _y, float _z) { w = _w; x = _x; y = _y; z = _z; }
        ~Quaternion() { }

        public static Quaternion Normalize(Quaternion _q)
        {
            float magnitude = (float)System.Math.Sqrt(System.Math.Pow(_q.x, 2) + System.Math.Pow(_q.y, 2) + System.Math.Pow(_q.z, 2));
            _q.w /= magnitude;
            _q.x /= magnitude;
            _q.y /= magnitude;
            _q.z /= magnitude;
            return _q;
        }

        public static Quaternion operator +(Quaternion _q1, Quaternion _q2)
        {
            Quaternion _res = new Quaternion();
            _res.w = _q1.w + _q2.w;
            _res.x = _q1.x + _q2.x;
            _res.y = _q1.y + _q2.y;
            _res.z = _q1.z + _q2.z;
            _res = Normalize(_res);
            return _res;
        }

        public static Quaternion operator *(Quaternion _q1, Quaternion _q2)
        {
            Quaternion _res = new Quaternion();
            _res.w = _q1.w * _q2.w - _q1.x * _q2.x - _q1.y * _q2.y - _q1.z * _q2.z;
            _res.x = _q1.w * _q2.x + _q1.x * _q2.w + _q1.y * _q2.z - _q1.z * _q2.y;
            _res.y = _q1.w * _q2.y + _q1.y * _q2.w - _q1.x * _q2.z + _q1.z * _q2.x;
            _res.z = _q1.w * _q2.z + _q1.z * _q2.w + _q1.x * _q2.y - _q1.y * _q2.x;
            return Normalize(_res);
        }

        public static Vector3 operator *(Quaternion quat, Vector3 vec)
        {
            float num = quat.x * 2f;
            float num2 = quat.y * 2f;
            float num3 = quat.z * 2f;
            float num4 = quat.x * num;
            float num5 = quat.y * num2;
            float num6 = quat.z * num3;
            float num7 = quat.x * num2;
            float num8 = quat.x * num3;
            float num9 = quat.y * num3;
            float num10 = quat.w * num;
            float num11 = quat.w * num2;
            float num12 = quat.w * num3;
            Vector3 result = new Vector3();
            result.x = (1f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
            result.y = (num7 + num12) * vec.x + (1f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
            result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1f - (num4 + num5)) * vec.z;
            return result;
        }

        public static Quaternion Inverse(Quaternion _q)
        {
            _q = Normalize(_q);
            _q.x *= -1;
            _q.y *= -1;
            _q.z *= -1;

            return _q;
        }

        public static Quaternion AxisAngleToQuaternion(Vector3 _axis, float _angle)
        {
            _axis = _axis.Normalized;
            Quaternion _q = new Quaternion
            {
                x = (float)(_axis.x * System.Math.Sin(_angle / 2)),
                y = (float)(_axis.y * System.Math.Sin(_angle / 2)),
                z = (float)(_axis.z * System.Math.Sin(_angle / 2)),
                w = (float)(System.Math.Cos(_angle / 2))
            };
            return _q;
        }

        public static Quaternion AxisAngleToQuaternion(AxisAngle _axisAngle)
        {
            return AxisAngleToQuaternion(new Vector3(_axisAngle.x, _axisAngle.y, _axisAngle.z), _axisAngle.angle);
        }

        public static AxisAngle QuaternionToAxisAngle(Quaternion _q)
        {
            AxisAngle _axAng = new AxisAngle
            {
                angle = (float)(2 * System.Math.Acos(_q.w)),
                x = (float)(_q.x / System.Math.Sqrt(1 - _q.w * _q.w)),
                y = (float)(_q.y / System.Math.Sqrt(1 - _q.w * _q.w)),
                z = (float)(_q.z / System.Math.Sqrt(1 - _q.w * _q.w))
            };
            return _axAng;
        }

    }
}
