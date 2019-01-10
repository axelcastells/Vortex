using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Vortex.Physics.Kinematics
{

    public delegate float ErrorFunction(Vector3 target, float[] solution);

    public class IKGradientController : KinematicsController
    {
        // The current angles
        protected List<float> Solution = null;

        private Vector3 target;
        private Transform destination;

        private float distanceFromDestination;
        
        public float DeltaGradient
        {
            get { return DeltaGradient; }
            set { DeltaGradient = value; }
        }
        public float LearningRate
        {
            get { return LearningRate; }
            set { LearningRate = value; }
        }
        public float StopThreshold
        {
            get { return StopThreshold; }
            set { StopThreshold = value; }
        }
        public float SlowdownThreshold
        {
            get { return SlowdownThreshold; }
            set { SlowdownThreshold = value; }
        }

        private ErrorFunction errorFunction;

        IKGradientController()
        {
            LearningRate = 0.1f;
            DeltaGradient = 0.1f;
            StopThreshold = 0.1f;
            SlowdownThreshold = 0.25f;
        }

        public void LinkData(ref List<RobotJoint> _joints, ref List<float> _solution, ref Transform _destination, ref Vector3 _target)
        {
            Joints = _joints;
            Solution = _solution;
            destination = _destination;
            target = _target;
        }

        public override void Init()
        {
            throw new NotImplementedException();
        }

        public override void Run()
        {
            // Do we have to approach the target?
            target = destination.position;
            //TODO


            if (errorFunction(target, Solution.ToArray()) > StopThreshold)
                ApproachTarget(target);
        }

        private void ApproachTarget(Vector3 target)
        {

            //TODO
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                float gradient = CalculateGradient(target, Solution.ToArray(), i, DeltaGradient);
                Solution[i] -= LearningRate * gradient;
            }

            for (int i = 0; i < Joints.Count - 1; i++)
            {
                //Joints[i].MoveArm(Solution[i]);
            }

        }

        private float CalculateGradient(Vector3 target, float[] Solution, int i, float delta)
        {
            //TODO 
            float aux = Solution[i];
            Solution[i] += delta;
            float d1 = DistanceFromTarget(target, Solution);

            Solution[i] = aux;

            float d2 = DistanceFromTarget(target, Solution);

            float gradient = (d1 - d2) / delta;

            return gradient;
        }

        private float DistanceFromTarget(Vector3 target, float[] Solution)
        {
            Vector3 point = ForwardKinematics(Solution);
            return Vector3.Distance(point, target);
        }

        private PositionRotation ForwardKinematics(float[] Solution)
        {
            Vector3 prevPoint = Joints[0].transform.position;

            // Takes object initial rotation into account
            Quaternion rotation = Joints[0].transform.rotation;


            //TODO
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                rotation = Quaternion.AxisAngleToQuaternion(Joints[i].GetAxis(), Solution[i]) * rotation;

                Vector3 newVectorRotate = rotation * (Joints[i + 1].startOffset);
                Vector3 nextPoint = prevPoint + newVectorRotate;

                prevPoint = nextPoint;
            }



            // The end of the effector
            return new PositionRotation(prevPoint, rotation);
        }
    }

    public class IKCCDController : KinematicsController
    {
        public delegate void EndEvent();
        public EndEvent OnEnded;

        private Transform target;
        public float DistanceThreshold
        {
            get { return DistanceThreshold; }
            set { DistanceThreshold = value; }
        }

        public void LinkData(ref Transform _target)
        {
            target = _target;
        }

        public override void Init()
        {
            throw new NotImplementedException();
        }

        public override void Run()
        {
            if (Vector3.Distance(GetEffector().transform.position, target.position) > DistanceThreshold)
            {
                for (int i = Joints.Count - 2; i > 0; i--)
                {
                    float dot = Vector3.Dot(target.transform.position - Joints[i].transform.position, GetEffector().transform.position - Joints[i].transform.position);
                    Vector3 cross = Vector3.Cross(target.transform.position - Joints[i].transform.position, GetEffector().transform.position - Joints[i].transform.position);
                    cross.Normalize();

                    Quaternion q = new Quaternion((float)Math.Cos(dot / 2), 
                                        (float)Math.Sin(dot / 2) * cross.x, 
                                        (float)Math.Sin(dot / 2) * cross.y, 
                                        (float)Math.Sin(dot / 2) * cross.z);

                    Quaternion endQuat = Joints[i].transform.rotation;
                    for(int j = i - 1; j > 0; j--)
                    {
                        endQuat *= Joints[j].transform.rotation;
                    }
                    endQuat *= q;

                    Joints[i].transform.rotation = endQuat;
                }
            }
            else
            {
                OnEnded();
            }

        }

        

    }

    public class FABRIKController : KinematicsController
    {
        public override void Init()
        {
            throw new NotImplementedException();
        }
        public override void Run()
        {
            throw new NotImplementedException();
        }
    }

    public class FKController : KinematicsController
    {
        // The current angles
        protected List<float> Solution = null;

        #region Constructors
        public FKController() { }
        #endregion

        internal delegate void ExecutionLoop();
        internal ExecutionLoop executionLoop;

        internal delegate void DataInitializer();

        public override void Init()
        {
            Solution = new float[Joints.Count].ToList<float>();
        }

        public override void Run()
        {
            for (int i = 0; i < Joints.Count - 1; i++)
            {
                Vector3 constraintAxis = ConstraintAxis(Joints[i].axis, Joints[i].axisConstraint);
                float constraintAngle = ConstraintAngle(Joints[i], Solution[i]);

                //Joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(constraintAxis, constraintAngle);
                Joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(Joints[i].axis, Solution[i]);
            }
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
    }

    public abstract class KinematicsController
    {
        /// <summary>
        /// Joint index 0 will always be the base joint.
        /// Joint index Count - 1 will always be the effector.
        /// </summary>
        protected List<RobotJoint> Joints = null;
        

        public KinematicsController()
        {

        }

        public abstract void Init();
        public abstract void Run();

        protected void LinkJoints(ref List<RobotJoint> _joints)
        {
            Joints = _joints;
        }

        protected RobotJoint GetEffector()
        {
            return Joints[Joints.Count - 1];
        }

        protected static float ClampAngle(float angle, float minAngle, float maxAngle, float delta = 0)
        {
            return VMath.Clamp(angle + delta, minAngle, maxAngle);
        }

        protected Vector3 ConstraintAxis(Vector3 originAxis, Vector3 targetAxis)
        {
            Vector3 targetMag = targetAxis / Vector3.Magnitude(targetAxis);
            Vector3 finalMag = targetAxis / (float)Math.Pow(Vector3.Magnitude(targetAxis), 2);
            Vector3 cross = Vector3.Cross(originAxis, targetMag);
            Vector3 proj = Vector3.Cross(cross, finalMag);

            return proj.Normalized;
        }

        protected float ConstraintAngle(RobotJoint j, float newAngle)
        {
            return ClampAngle(newAngle, j.minAngle, j.maxAngle);
        }
    }

    public class RobotJoint
    {
        internal Transform transform;
        internal Vector3 startOffset;
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
            return Quaternion.QuaternionToAxisAngle(transform.rotation);
        }
    }

    internal struct PositionRotation
    {
        Vector3 position;
        Quaternion rotation;

        public PositionRotation(Vector3 position, Quaternion rotation)
        {
            this.position = position;
            this.rotation = rotation;
        }

        // PositionRotation to Vector3
        public static implicit operator Vector3(PositionRotation pr)
        {
            return pr.position;
        }
        // PositionRotation to Quaternion
        public static implicit operator Quaternion(PositionRotation pr)
        {
            return pr.rotation;
        }
    }

}