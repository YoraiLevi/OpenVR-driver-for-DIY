using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Text;
using Grpc.Core;
using System.Diagnostics;
using grpc = global::Grpc.Core;
namespace GRPCServices
{
    public static partial class Ping
    {
        public class PingImpl : PingBase
        {
            public override Task<PingResponse> Ping(PingRequest request, ServerCallContext context)
            {
                return Task.FromResult(new PingResponse { Data = request.Data });
            }
        }
        public partial class PingClient
        {
            /// <summary>
            /// Pings the remote server
            /// </summary>
            /// <param name="data"></param>
            /// <returns></returns>
            public long Ping(string data)
            {
                Stopwatch sw = new Stopwatch();
                sw.Start();
                var request = new PingRequest { Data = data };
                var reply = this.Ping(request);
                sw.Stop();
                //long nanoseconds = sw.ElapsedTicks / (Stopwatch.Frequency / (1000L * 1000L * 1000L));
                long ms = sw.ElapsedMilliseconds;
                Console.WriteLine("Sent {0} bytes in {1} ms", request.CalculateSize(), sw.ElapsedMilliseconds);
                return ms;
            }
            /*        Stopwatch sw = new Stopwatch();
                    sw.Start();

            // Do something you want to time

            sw.Stop();

            long microseconds = sw.ElapsedTicks / (Stopwatch.Frequency / (1000L * 1000L));
            long nanoseconds = sw.ElapsedTicks / (Stopwatch.Frequency / (1000L * 1000L * 1000L));
                    Console.WriteLine("Operation completed in: " + microseconds + " (us)");
            Console.WriteLine("Operation completed in: " + nanoseconds + " (ns)");
            */
        }
    }
}
