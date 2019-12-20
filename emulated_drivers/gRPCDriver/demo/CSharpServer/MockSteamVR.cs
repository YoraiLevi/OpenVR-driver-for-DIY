using System;
using System.Collections.Generic;
using System.Text;

namespace CSharpServer
{
    class MockSteamVR
    {
        public struct Pose
        {
            public struct Vector3
            {
                public double x, y, z;
                public static Vector3 operator +(Vector3 vector3A, Vector3 vector3B)
                {
                    return new Vector3 { x = vector3A.x + vector3B.x, y = vector3A.y + vector3B.y, z = vector3A.z + vector3B.z };
                }
                public override string ToString()
                {
                    string format = "<Vector3: {0} , {1} , {2}>";
                    return string.Format(format, x, y, z);
                }
            }
            public struct Quaternion
            {
                public double w, x, y, z;
                public static Quaternion operator *(Quaternion quaternionA, Quaternion quaternionB)
                {
                    throw new NotImplementedException("Quaternion * operator isn't implemented");
                }
                public override string ToString()
                {
                    string format = "<Quaternion: {0} , {1} , {2} , {3}>";
                    return string.Format(format, w, x,y,z);
                }
            }
            Vector3 positon;
            Quaternion rotation;
            public static Pose operator +(Pose poseA, Pose poseB)
            {
                return new Pose { positon = poseA.positon + poseB.positon, rotation = poseA.rotation * poseB.rotation };
            }
            public override string ToString()
            {
                string format = "<Pose: {0} , {1}>";
                return string.Format(format,positon,rotation);
            }
        }
        public abstract class TrackedObject
        {
            public static TrackedObject TrackedObjectFactory(TrackedObjectType trackedObjectType)
        {
            switch (trackedObjectType)
            {
                case TrackedObjectType.CONTROLLER:
                    return new MockSteamVR.Controller();
                case TrackedObjectType.HMD:
                    return new MockSteamVR.Headset();
                case TrackedObjectType.TRACKER:
                    return new MockSteamVR.Tracker();
                default:
                    return null;
            }
        }
            protected TrackedObject() { }
            public Pose pose { get; set; }
        }
        public enum TrackedObjectType { HMD, CONTROLLER, TRACKER };
        public class Headset : TrackedObject { }
        public class Controller : TrackedObject { }
        public class Tracker : TrackedObject { }

        private Dictionary<int, TrackedObject> trackedObjects { get; set; }

        public MockSteamVR()
        {
            trackedObjects = new Dictionary<int, TrackedObject>(); //10 for two players is likely to be enough
        }
        public void Attach(int id, TrackedObjectType trackedObjectType)
        {
            trackedObjects.Add(id, TrackedObject.TrackedObjectFactory(trackedObjectType));
#if DEBUG
            Console.WriteLine("Server is Attaching {0} of type {1}", id, Enum.GetName(typeof(TrackedObjectType), trackedObjectType));
#endif
        }
        public void Detach(int id)
        {
#if DEBUG
            Console.WriteLine("Server is Detaching {0}", id);
#endif
            trackedObjects.Remove(id);
        }
        public void SetPose(int id, Pose pose)
        {
            trackedObjects[id].pose = pose;
#if DEBUG
            Console.WriteLine("Server is Setting Pose of {0} to {1}", id, trackedObjects[id].pose);
#endif
        }
        public void TransformPose(int id, Pose pose)
        {
            var oldpose = trackedObjects[id].pose;
            trackedObjects[id].pose = pose + oldpose;
#if DEBUG
            Console.WriteLine("Server is Setting Pose of {0} to {1}", id, trackedObjects[id].pose);
#endif
        }
    }
}
