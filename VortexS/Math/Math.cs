using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VortexS.Math
{
    public class Vector3
    {
        // Properties:
        public float x, y, z;

        // Functions:
        public Vector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
        public Vector3() { }
        public Vector3(float _val) { x = y = z = _val; }
        ~Vector3() { }

        Vector3 Normalize(Vector3 _v)
        {
            float mod = (float)System.Math.Sqrt(System.Math.Pow(_v.x, 2) + System.Math.Pow(_v.y, 2) + System.Math.Pow(_v.z, 2));
            _v.x /= mod;
            _v.y /= mod;
            _v.z /= mod;
            return _v;
        }

        public Vector3 Normalized() { return Normalize(this); }
    }

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

    public class Quaternion
    {
        // Properties:
        public float w, x, y, z;

        // Functions:
        public Quaternion() { w = 1; x = 0; y = 0; z = 0; }
        public Quaternion(float _w, float _x, float _y, float _z) { w = _w; x = _x; y = _y; z = _z; }
        //public MyQuaternion(Quaternion _unityQ)
        //{
        //    _unityQ = _unityQ.normalized;
        //    w = _unityQ.w; x = _unityQ.x; y = _unityQ.y; z = _unityQ.z;
        //}
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

        public Quaternion Normalized()
        {
            return Normalize(this);
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

        public Quaternion Multiply(Quaternion _q1, Quaternion _q2)
        {
            Quaternion _res = new Quaternion();
            _res.w = _q1.w * _q2.w - _q1.x * _q2.x - _q1.y * _q2.y - _q1.z * _q2.z;
            _res.x = _q1.w * _q2.x + _q1.x * _q2.w + _q1.y * _q2.z - _q1.z * _q2.y;
            _res.y = _q1.w * _q2.y + _q1.y * _q2.w - _q1.x * _q2.z + _q1.z * _q2.x;
            _res.z = _q1.w * _q2.z + _q1.z * _q2.w + _q1.x * _q2.y - _q1.y * _q2.x;
            return Normalize(_res);
        }

        public Quaternion Inverse(Quaternion _q)
        {
            _q = Normalize(_q);
            _q.x *= -1;
            _q.y *= -1;
            _q.z *= -1;

            return _q;
        }

        public Quaternion AxisAngleToQuaternion(Vector3 _axis, float _angle)
        {
            _axis = _axis.Normalized();
            Quaternion _q = new Quaternion();
            _q.x = (float)(_axis.x * System.Math.Sin(_angle / 2));
            _q.y = (float)(_axis.y * System.Math.Sin(_angle / 2));
            _q.z = (float)(_axis.z * System.Math.Sin(_angle / 2));
            _q.w = (float)(System.Math.Cos(_angle / 2));
            return _q;
        }

        public Quaternion AxisAngleToQuaternion(AxisAngle _axisAngle)
        {
            return AxisAngleToQuaternion(new Vector3(_axisAngle.x, _axisAngle.y, _axisAngle.z), _axisAngle.angle);
        }

        public AxisAngle QuaternionToAxisAngle(Quaternion _q)
        {
            AxisAngle _axAng = new AxisAngle();
            _axAng.angle = (float)(2 * System.Math.Acos(_q.w));
            _axAng.x = (float)(_q.x / System.Math.Sqrt(1 - _q.w * _q.w));
            _axAng.y = (float)(_q.y / System.Math.Sqrt(1 - _q.w * _q.w));
            _axAng.z = (float)(_q.z / System.Math.Sqrt(1 - _q.w * _q.w));
            return _axAng;
        }

    }
}
