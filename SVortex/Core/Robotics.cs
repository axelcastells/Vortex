using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex.Physics
{
    public enum Mode { FK, IK }
    public enum AxisConstraint { X, Y, Z }

    [System.Serializable]
    public class RobotController
    {
        #region Variables
        private RobotJoint BaseJoint;

        private List<RobotJoint> Joints = null;
        // The current angles
        private List<float> Solution = null;

        #endregion
        #region Constructors
        public RobotController()
        {

        }

        #endregion
        internal delegate void ExecutionLoop();
        internal ExecutionLoop executionLoop;

        public void SetMode(Mode mode)
        {
            switch (mode)
            {
                case Mode.FK:
                    {
                        executionLoop = RunFK;
                    }
                    break;
                case Mode.IK:
                    {

                    }
                    break;
                default:
                    break;
            }
        }

        public void Run()
        {
            executionLoop();
        }

        private void RunFK()
        {
            ForwardKinematics();
        }

        private void RunIK()
        {

        }

        public void LinkData(ref RobotJoint _baseJoint, ref List<RobotJoint> _joints, ref List<float> _solution)
        {
            BaseJoint = _baseJoint;
            Solution = _solution;
            Joints = _joints;
        }

        public string DebugLinkedData()
        {
            return ("Joints Size: " + Joints.Count + "Solution Size: " + Solution.Count);
        }

        internal void ForwardKinematics()
        {
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                Joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(Joints[i].axis, Solution[i]);
                //Joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(new Vector3(1, 1, 20), 90);
            }
        }

        internal PositionRotation ForwardKinematicsSimulation(List<float> Solution)
        {
            Vector3 prevPoint = BaseJoint.transform.position;

            // Takes object initial rotation into account
            Quaternion rotation = BaseJoint.transform.rotation;

            
            //TODO
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                rotation = Quaternion.AxisAngleToQuaternion(Joints[i].axis, Solution[i]) * rotation;

                Vector3 newVectorRotate = rotation * (Joints[i + 1].startOffset);
                Vector3 nextPoint = prevPoint + newVectorRotate;

                prevPoint = nextPoint;
            }



            // The end of the effector
            return new PositionRotation(prevPoint, rotation);
        }
    }

    public class RobotJoint
    {
        internal Transform transform;
        internal Vector3 startOffset;
        internal Vector3 axis;
        private float minAngle, maxAngle;

        public RobotJoint(float _axisX, float _axisY, float _axisZ)//, float _angle, float _zeroAxisX, float _zeroAxisY, float _zeroAxisZ)//(float _positionX, float _positionY, float _positionZ, AxisAngle _angleAxis, Vector3 _axis)
        {
            minAngle = 0;
            maxAngle = 360;
            transform = new Transform();
            //transform.rotation = Quaternion.AxisAngleToQuaternion(new Vector3(_zeroAxisX, _zeroAxisY, _zeroAxisZ), _angle);
            //startOffset = new Vector3(_positionX, _positionY, _positionZ);
            //transform.position = startOffset;
            //transform.rotation = Quaternion.AxisAngleToQuaternion(_angleAxis);
            axis = new Vector3(_axisX, _axisY, _axisZ);
        }
        
        public float ClampAngle(float angle, float delta = 0)
        {
            return angle;// VMath.Clamp(angle + delta, minAngle, maxAngle);
        }

        // Get the current angle
        public float GetAngle()
        {
            float angle = 0;
            if (axis.x == 1) angle = transform.eulerAngles.x;
            else
            if (axis.y == 1) angle = transform.eulerAngles.y;
            else
            if (axis.z == 1) angle = transform.eulerAngles.z;

            return ClampAngle(angle);
        }
        public float SetAngle(float angle)
        {
            angle = ClampAngle(angle);
            if (axis.x == 1) transform.eulerAngles = new Vector3(angle, 0, 0);
            else
            if (axis.y == 1) transform.eulerAngles = new Vector3(0, angle, 0);
            else
            if (axis.z == 1) transform.eulerAngles = new Vector3(0, 0, angle);

            return angle;
        }

        public Vector3 GetAxis()
        {
            return axis;
        }

        // Moves the angle to reach 
        public float MoveArm(float angle)
        {
            return SetAngle(angle);
        }

        public AxisAngle GetAxisAngle()
        {
            return Quaternion.QuaternionToAxisAngle(transform.rotation);
        }
    }
}
