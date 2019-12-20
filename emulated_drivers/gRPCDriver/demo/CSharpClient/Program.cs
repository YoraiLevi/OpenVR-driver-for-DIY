using Grpc.Core;
using System;
using GRPCServices.Driver;
using static GRPCServices.Driver.AttachMessage.Types;
namespace CSharpClient
{
    class Program
    {
        public static void Main(string[] args)
        {
            Channel channel = new Channel("127.0.0.1:50051", ChannelCredentials.Insecure);

            var client = new InputEmulation.InputEmulationClient(channel);

            var replyA = client.Attach(new AttachMessage { Id = 1, Device = Device.Controller });
            Console.WriteLine("Attach: " + replyA.ToString());
            var replyT = client.Transform(new TransformMessage { Id = 1, Absolute = new Graphics.CartesianPose { Position = new Graphics.Cartesian { X = 1, Y = 1, Z = 1 }, Euler = new Graphics.Euler { X = 1, Y = 1, Z = 1 } }});
            Console.WriteLine("Transform: " + replyT.ToString());
            var replyD = client.Detach(new DetachMessage { Id = 1 });
            Console.WriteLine("Attach: " + replyD.ToString());
            replyT = client.Transform(new TransformMessage { Id = 1, Relative = new Graphics.CartesianPose { Position = new Graphics.Cartesian { X = 1, Y = 1, Z = 1 }, Euler = new Graphics.Euler { X = 1, Y = 1, Z = 1 } } });
            Console.WriteLine("Transform: " + replyT.ToString());
            channel.ShutdownAsync().Wait();
            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}

