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

        private Transform Effector;
        private Transform Destination;
        private float DistanceFromDestination;
        private Vector3 target;

        private float DeltaGradient = 0.1f; // Used to simulate gradient (degrees)
        private float LearningRate = 0.1f; // How much we move depending on the gradient

        private float StopThreshold = 0.1f; // If closer than this, it stops
        private float SlowdownThreshold = 0.25f; // If closer than this, it linearly slows down
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

            PositionRotation pr = ForwardKinematics(Solution);

        }

        private void RunIK()
        {

        }

        public void LinkData(ref List<RobotJoint> _joints, ref List<float> _solution)
        {
            BaseJoint = _joints[0];
            Solution = _solution;
            Joints = _joints;
        }

        public string DebugLinkedData()
        {
            return ("Joints Size: " + Joints.Count + "Solution Size: " + Solution.Count);
        }

        internal PositionRotation ForwardKinematics(List<float> Solution)
        {
            Vector3 prevPoint = Joints[0].transform.position;

            // Takes object initial rotation into account
            Quaternion rotation = Joints[0].transform.rotation;

            
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
        public float minAngle, maxAngle;

        internal Vector3 zeroEuler;

        public RobotJoint(float _startOffsetX, float _startOffsetY, float _startOffsetZ, float _zeroEulerX, float _zeroEulerY, float _zeroEulerZ,
                            AxisConstraint _axis)
        {
            zeroEuler = new Vector3(_zeroEulerX, _zeroEulerY, _zeroEulerZ);
            startOffset = new Vector3(_startOffsetX, _startOffsetY, _startOffsetZ);

            switch (_axis)
            {
                case AxisConstraint.X:
                    axis = new Vector3(1, 0, 0);
                    break;
                case AxisConstraint.Y:
                    axis = new Vector3(0, 1, 0);
                    break;
                case AxisConstraint.Z:
                    axis = new Vector3(0, 0, 1);
                    break;
                default:
                    break;
            }
            

        }
        
        public float ClampAngle(float angle, float delta = 0)
        {
            return VMath.Clamp(angle + delta, minAngle, maxAngle);
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



        // Moves the angle to reach 
        public float MoveArm(float angle)
        {
            return SetAngle(angle);
        }
    }
}
