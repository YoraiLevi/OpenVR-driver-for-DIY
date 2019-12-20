using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Text;
using Grpc.Core;
using System.Diagnostics;
namespace GRPCServices.Ping
{
    public class PingServerImpl : PingService.PingServiceBase
    {
        public override Task<PingResponse> Ping(PingRequest request, ServerCallContext context)
        {
            return Task.FromResult(new PingResponse { Data = request.Data });
        }
    }
    public class PingClientImpl : PingService.PingServiceClient
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
            var reply = base.Ping(new PingRequest { Data = data });
            long nanoseconds = sw.ElapsedTicks / (Stopwatch.Frequency / (1000L * 1000L * 1000L));
            return nanoseconds;
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
