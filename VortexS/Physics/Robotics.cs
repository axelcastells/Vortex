using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SVortex;

namespace SVortex.Physics
{
    public enum Mode { FK, IK }

    [System.Serializable]
    public class RobotController
    {
        #region Variables
        public RobotJoint BaseJoint;

        public List<RobotJoint> Joints = null;
        // The current angles
        public List<float> Solution = null;

        public Transform Effector;
        public Transform Destination;
        public float DistanceFromDestination;
        private Vector3 target;

        public float DeltaGradient = 0.1f; // Used to simulate gradient (degrees)
        public float LearningRate = 0.1f; // How much we move depending on the gradient

        public float StopThreshold = 0.1f; // If closer than this, it stops
        public float SlowdownThreshold = 0.25f; // If closer than this, it linearly slows down
        #endregion
        #region Constructors
        public RobotController() { }

        #endregion
        public delegate void ExecutionLoop();
        public ExecutionLoop executionLoop;

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

        private void RunFK()
        {
            ForwardKinematics(Solution);
        }

        public void LinkData(ref List<RobotJoint> joint, ref List<float> solution)
        {
            BaseJoint = joint[0];
            Solution = solution;
            Joints = joint;
        }

        public string DebugLinkedData()
        {
            return ("Joints Size: " + Joints.Capacity + "Solution Size: " + Solution.Capacity);
        }

        public PositionRotation ForwardKinematics(List<float> Solution)
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
        public Transform transform;
        public Vector3 startOffset;
        public Vector3 axis;
        public float minAngle, maxAngle;

        public Vector3 zeroEuler;


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
