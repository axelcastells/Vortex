using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SVortex;

namespace SVortex.Physics
{
    [System.Serializable]
    public class RobotController
    {
        public Transform BaseJoint;


        public RobotJoint[] Joints = null;
        // The current angles
        public float[] Solution = null;

        public Transform Effector;
        public Transform Destination;
        public float DistanceFromDestination;
        private Vector3 target;

        public float DeltaGradient = 0.1f; // Used to simulate gradient (degrees)
        public float LearningRate = 0.1f; // How much we move depending on the gradient

        public float StopThreshold = 0.1f; // If closer than this, it stops
        public float SlowdownThreshold = 0.25f; // If closer than this, it linearly slows down

        private RobotController() { }
        public RobotController(RobotJoint[] jnts, float[] sln)
        {
            if(jnts.Length == sln.Length)
            {
                Joints = jnts;
                Solution = sln;
            }
        }

        public void ApproachTarget(Vector3 target)
        {

        }
    }

    public class RobotJoint
    {
        public Transform transform;

        public Vector3 axis;
        public float minAngle, maxAngle;

        public Vector3 startOffset;

        public Vector3 zeroEuler;


        public float ClampAngle(float angle, float delta = 0)
        {
            return Math.Clamp(angle + delta, minAngle, maxAngle);
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
