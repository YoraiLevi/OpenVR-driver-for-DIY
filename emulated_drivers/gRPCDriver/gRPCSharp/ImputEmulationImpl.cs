using System;
using System.Threading.Tasks;
using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
namespace GRPCServices.Driver
{
    public class InputEmulationImpl : InputEmulation.InputEmulationBase
    {
        public class AttachEventArgs : EventArgs
        {
            public AttachMessage message;
        }
        public class DetachEventArgs : EventArgs
        {
            public DetachMessage message;
        }
        public class TransformEventArgs : EventArgs
        {
            public TransformMessage message;
        }
        public event EventHandler<AttachEventArgs> Attached;
        public event EventHandler<DetachEventArgs> Detached;
        public event EventHandler<TransformEventArgs> Transformed;

        public override Task<Empty> Attach(AttachMessage request, ServerCallContext context)
        {
#if DEBUG
            Console.WriteLine(request.ToString());
#endif
            Attached?.Invoke(this, new AttachEventArgs { message = request });
            return Task.FromResult(new Empty());
        }
        public override Task<Empty> Detach(DetachMessage request, ServerCallContext context)
        {
#if DEBUG
            Console.WriteLine(request.ToString());
#endif
            Detached?.Invoke(this, new DetachEventArgs { message = request });
            return Task.FromResult(new Empty());
        }
        public override Task<Empty> Transform(TransformMessage request, ServerCallContext context)
        {
#if DEBUG
            Console.WriteLine(request.ToString());
#endif
            Transformed?.Invoke(this, new TransformEventArgs { message = request });
            return Task.FromResult(new Empty());
        }
    }
}
