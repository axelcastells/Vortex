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

        private Vector3 target;
        public float distanceThreshold;

        public IKCCDController()
        {
            distanceThreshold = 0.1f;
        }

        public void SetTarget(float _x, float _y, float _z)
        {
            target = new Vector3(_x, _y, _z);
        }

        public override void Init()
        {
            throw new NotImplementedException();
        }

        double SimpleAngle(double theta)
        {
            theta = theta % (2.0 * Math.PI);
            if (theta < -Math.PI)
                theta += 2.0 * Math.PI;
            else if (theta > Math.PI)
                theta -= 2.0 * Math.PI;
            return theta;
        }

        public override void Run()
        {

            if (Vector3.Distance(GetEffector().transform.position, target) > distanceThreshold)
            {
                for (int i = Joints.Count - 2; i > 0; i--)
                {
                    Vector3 v1 = GetEffector().transform.position - Joints[i].transform.position;
                    Vector3 v2 = target - Joints[i].transform.position;


                    float cos, sin;
                    if(v1.Magnitude() * v2.Magnitude() <= 0.001f)
                    {
                        cos = 1;
                        sin = 0;

                    }
                    else{
                        cos = Vector3.Dot(v1, v2) / (v1.Magnitude() * v2.Magnitude());
                        sin = Vector3.Cross(v1, v2).Magnitude() / (v1.Magnitude() * v2.Magnitude());
                    }

                    Vector3 axis = Vector3.Cross(v1, v2) / (v1.Magnitude() * v2.Magnitude());

                    float angle = (float)Math.Acos(Math.Max(-1, Math.Min(1, cos)));

                    if(sin < 0)
                    {
                        angle = -angle;
                    }

                    angle = (float)SimpleAngle(angle) * VMath.Rad2Deg;

                    
                    Quaternion q = Quaternion.AxisAngleToQuaternion(axis, angle);

                    //Quaternion endQuat = Joints[i].transform.rotation;
                    //for (int j = i - 1; j > 0; j--)
                    //{
                    //    endQuat *= Joints[j].transform.rotation;
                    //}
                    //endQuat *= q;

                    Joints[i].transform.rotation = q;
                    Joints[i].ConstraintAngle(0, 1);
                }
            }
            else
            {
                OnEnded();
            }

            float x = Math.Abs(Joints[Joints.Count - 1].transform.position.x - target.x);
            float y = Math.Abs(Joints[Joints.Count - 1].transform.position.y - target.y);
            float z = Math.Abs(Joints[Joints.Count - 1].transform.position.z - target.z);

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

        public void LinkJoints(ref List<RobotJoint> _joints)
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

        public RobotJoint(float _posX, float _posY, float _posZ, float _rotW, float _rotX, float _rotY, float _rotZ)
        {
            transform = new Transform();
            transform.position = new Vector3(_posX, _posY, _posZ);
            transform.rotation = new Quaternion(_rotW, _rotX, _rotY, _rotZ);
        }
        
        public void SetAxis(float _x, float _y, float _z)
        {
            axis = new Vector3(_x, _y, _z);
        }

        public Vector3 GetAxis()
        {
            return axis;
        }


        /// <summary>
        /// Min and Max must be between 0 and 360
        /// </summary>
        /// <param name="_min"></param>
        /// <param name="_max"></param>
        public void ConstraintAngle(float _min, float _max)
        {
            AxisAngle res = Quaternion.QuaternionToAxisAngle(transform.rotation);
            res.angle = VMath.Clamp(res.angle, _min * VMath.Rad2Deg, _max * VMath.Rad2Deg);
            transform.rotation = Quaternion.AxisAngleToQuaternion(res);
        }

        public void ConstraintAxis()
        {

        }

        public void SetPosition(float _x, float _y, float _z)
        {
            transform.position.x = _x;
            transform.position.y = _y;
            transform.position.z = _z;
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

    public class IKCCDSolver
    {

        // Array to hold all the joints
        // index 0 - root
        // index END - End Effector
        public List<Transform> joints;
        // The target for the IK system
        public Vector3 targ;

        // The sine component for each joint

        private float[] _sin, _cos, _theta;


        // To check if the target is reached at any point
        public bool done = false;
        // To store the position of the target
        private Vector3 tpos;

        // Max number of tries before the system gives up (Maybe 10 is too high?)
        private int Mtries = 10;
        // The number of tries the system is at now
        private int tries = 0;

        // the range within which the target will be assumed to be reached
        private float epsilon = 0.1f;




        // Initializing the variables
        public void Start()
        {
            _theta = new float[joints.Count];
            _sin = new float[joints.Count];
            _cos = new float[joints.Count];
            tpos = targ;
        }

        // Running the solver - all the joints are iterated through once every frame
        public void Update()
        {
            // if the target hasn't been reached
            if (!done)
            {
                // if the Max number of tries hasn't been reached
                if (tries <= Mtries)
                {
                    // starting from the second last joint (the last being the end effector)
                    // going back up to the root
                    for (int i = joints.Count - 2; i >= 0; i--)
                    {
                        // The vector from the ith joint to the end effector
                        Vector3 r1 = joints[joints.Count - 1].transform.position - joints[i].transform.position;
                        // The vector from the ith joint to the target
                        Vector3 r2 = targ - joints[i].transform.position;

                        // to avoid dividing by tiny numbers
                        if (r1.Magnitude() * r2.Magnitude() <= 0.001f)
                        {
                            // cos component will be 1 and sin will be 0
                            _cos[i] = 1;
                            _sin[i] = 0;
                        }
                        else
                        {
                            // find the components using dot and cross product
                            _cos[i] = Vector3.Dot(r1, r2) / (r1.Magnitude() * r2.Magnitude());
                            _sin[i] = (Vector3.Cross(r1, r2)).Magnitude() / (r1.Magnitude() * r2.Magnitude());

                        }

                        // The axis of rotation is basically the 
                        // unit vector along the cross product 
                        Vector3 axis = (Vector3.Cross(r1, r2)) / (r1.Magnitude() * r2.Magnitude());

                        // find the angle between r1 and r2 (and clamp values of cos to avoid errors)
                        _theta[i] = (float)Math.Acos(Math.Max(-1, Math.Min(1, _cos[i])));
                        // invert angle if sin component is negative
                        if (_sin[i] < 0.0f)
                            _theta[i] = -_theta[i];
                        // obtain an angle value between -pi and pi, and then convert to degrees
                        _theta[i] = (float)SimpleAngle(_theta[i]) * VMath.Rad2Deg;
                        // rotate the ith joint along the axis by theta degrees in the world space.
                        joints[i].transform.rotation = Quaternion.AxisAngleToQuaternion(axis, _theta[i]);

                    }

                    // increment tries
                    tries++;
                }
            }

            // find the difference in the positions of the end effector and the target
            // (there's obviously a more beautiful and DRY way to do this)
            float x = Math.Abs(joints[joints.Count - 1].transform.position.x - targ.x);
            float y = Math.Abs(joints[joints.Count - 1].transform.position.y - targ.y);
            float z = Math.Abs(joints[joints.Count - 1].transform.position.z - targ.z);

            // if target is within reach (within epsilon) then the process is done
            if (x < epsilon && y < epsilon && z < epsilon)
            {
                done = true;
            }
            // if it isn't, then the process should be repeated
            else
            {
                done = false;
            }

            // the target has moved, reset tries to 0 and change tpos
            if (targ != tpos)
            {
                tries = 0;
                tpos = targ;
            }




        }

        // function to convert an angle to its simplest form (between -pi to pi radians)
        double SimpleAngle(double theta)
        {
            theta = theta % (2.0 * Math.PI);
            if (theta < -Math.PI)
                theta += 2.0 * Math.PI;
            else if (theta > Math.PI)
                theta -= 2.0 * Math.PI;
            return theta;
        }
    }

}