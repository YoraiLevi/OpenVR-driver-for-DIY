using System;
using Grpc.Core;
using GRPCServices.Driver;

namespace CSharpServer
{
    static class EnumExtention
    {
        public static MockSteamVR.TrackedObjectType ToTrackedObjectType(this AttachMessage.Types.Device device)
        {
            switch (device)
            {
                case AttachMessage.Types.Device.Controller:
                    return MockSteamVR.TrackedObjectType.CONTROLLER;
                case AttachMessage.Types.Device.Hmd:
                    return MockSteamVR.TrackedObjectType.HMD;
                case AttachMessage.Types.Device.Tracker:
                    return MockSteamVR.TrackedObjectType.TRACKER;
                default:
                    throw new NotSupportedException();
            }
        }
    }
    class Program
    {
        const int Port = 50051;
        public static void Main(string[] args)
        {
            MockSteamVR steamVR = new MockSteamVR();
            EventHandler<InputEmulationImpl.AttachEventArgs> attach = (s, e) => { steamVR.Attach(e.message.Id, e.message.Device.ToTrackedObjectType()); };
            EventHandler<InputEmulationImpl.DetachEventArgs> detach = (s, e) => { steamVR.Detach(e.message.Id); };
            EventHandler<InputEmulationImpl.TransformEventArgs> transform = (s, e) => { Console.WriteLine("I can't care to write this function at the moment");/*steamVR.SetPose(e.message.Id,);*/ };
            try
            {
                var inputEmulation = new InputEmulationImpl();
                inputEmulation.Attached += attach;
                inputEmulation.Detached += detach;
                inputEmulation.Transformed += transform;
                Server server = new Server
                {
                    Services = { GRPCServices.Driver.InputEmulation.BindService(inputEmulation) },
                    Ports = { new ServerPort("localhost", Port, ServerCredentials.Insecure) }
                };

                server.Start();
                Console.WriteLine("Accounts server listening on port " + Port);
                Console.WriteLine("Press any key to stop the server...");
                Console.ReadKey();
                server.ShutdownAsync().Wait();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception encountered: {ex}");
            }
        }
    }
}