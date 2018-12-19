using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex.Physics
{
    public enum Mode { FK, IK_CCD }

    [System.Serializable]
    public class IKCCDController : KinematicsController
    {
        private Transform target;
        private float distanceFromDestination;

        private float deltaGradient = 0.1f;
        private float learningRate = 0.1f;

        private float stopThreshold;
        private float slowdownThreshold;
    }

    public class FKController : KinematicsController
    {
        #region Constructors
        public FKController() { }
        #endregion

        internal delegate void ExecutionLoop();
        internal ExecutionLoop executionLoop;

        internal delegate void DataInitializer();
        internal DataInitializer dataInitialize;

        public void Init(Mode mode)
        {
            dataInitialize();
        }

        private void InitFK()
        {

        }

        public override void Run()
        {
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                Vector3 constraintAxis = ConstraintAxis(Joints[i].axis, Joints[i].axisConstraint);
                float constraintAngle = ConstraintAngle(Joints[i], Solution[i]);

                //Joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(constraintAxis, constraintAngle);
                Joints[i].transform.rotation = MyQuaternion.AxisAngleToQuaternion(Joints[i].axis, Solution[i]);
            }
        }

        private void InitIKCCD()
        {
            Solution = new float[Joints.Count].ToList<float>();
        }

        internal void RunIKCCD()
        {

        }

        public void LinkData(ref List<RobotJoint> _joints, ref List<float> _solution)
        {
            Solution = _solution;
            Joints = _joints;
        }

        public string DebugLinkedData()
        {
            return ("Joints Size: " + Joints.Count + "Solution Size: " + Solution.Count);
        }



        public static float ClampAngle(float angle, float minAngle, float maxAngle, float delta = 0)
        {
            return VMath.Clamp(angle + delta, minAngle, maxAngle);
        }

        public Vector3 ConstraintAxis(Vector3 originAxis, Vector3 targetAxis)
        {
            Vector3 targetMag = targetAxis / Vector3.Magnitude(targetAxis);
            Vector3 finalMag = targetAxis / (float)Math.Pow(Vector3.Magnitude(targetAxis), 2);
            Vector3 cross = Vector3.Cross(originAxis, targetMag);
            Vector3 proj = Vector3.Cross(cross, finalMag);

            return proj.Normalized;
        }

        public float ConstraintAngle(RobotJoint j, float newAngle)
        {
            return ClampAngle(newAngle, j.minAngle, j.maxAngle);
        }
    }

    public abstract class KinematicsController
    {
        /// <summary>
        /// Joint index 0 will always be the base joint.
        /// Joint index Count - 1 will always be the effector.
        /// </summary>
        protected List<RobotJoint> Joints = null;
        // The current angles
        protected List<float> Solution = null;

        public KinematicsController()
        {

        }

        public abstract void Init();
        public abstract void Run();
    }

    public class RobotJoint
    {
        internal Transform transform;
        //internal Vector3 startOffset;
        internal Vector3 axis;
        public Vector3 axisConstraint;
        public Vector3 zeroEuler;
        public readonly float minAngle, maxAngle;

        public RobotJoint() { axis = new Vector3(0, 0, 0); transform = new Transform(); minAngle = 0; maxAngle = 90; zeroEuler = Vector3.Zero(); }
        public RobotJoint(float _axisX, float _axisY, float _axisZ, float _constraintX, float _constraintY, float _constraintZ, float _minAngle, float _maxAngle)//, float _angle, float _zeroAxisX, float _zeroAxisY, float _zeroAxisZ)//(float _positionX, float _positionY, float _positionZ, AxisAngle _angleAxis, Vector3 _axis)
        {
            axisConstraint = new Vector3(_constraintX, _constraintY, _constraintZ);
            minAngle = _minAngle;
            maxAngle = _maxAngle;
            transform = new Transform();
            axis = new Vector3(_axisX, _axisY, _axisZ);
        }
        
        public void SetAxis(float _x, float _y, float _z)
        {
            axis = new Vector3(_x, _y, _z);
        }

        public Vector3 GetAxis()
        {
            return axis;
        }

        public AxisAngle GetAxisAngle()
        {
            return MyQuaternion.QuaternionToAxisAngle(transform.rotation);
        }
    }
}
