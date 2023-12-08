using Lab4.Model;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Lab4.Implementation
{
    public class DirectCallback
    {
        public static void Run(List<string> hosts)
        {
            for (var i = 0; i < hosts.Count; i++)
            {
                Start(i, hosts[i]);
                Thread.Sleep(2000);
            }
        }

        private static void Start(int id, string host)
        {
            // set up connection
            var state = Utils.CreateState(id, host);

            // connect to the remote endpoint
            state.socket.BeginConnect(state.remoteEndPoint, OnConnect, state);
        }

        private static void OnConnect(IAsyncResult ar)
        {
            // get the state of the connection
            var state = (State)ar.AsyncState;

            // complete the connection
            state.socket.EndConnect(ar);

            Console.WriteLine("{0}) Socket connected to {1} ({2})", state.clientID, state.hostname, state.socket.RemoteEndPoint);

            // convert the string data to byte data
            var byteData = Encoding.ASCII.GetBytes(Utils.GetRequestString(state.hostname, state.endPointPath));

            // begin sending data to the server
            state.socket.BeginSend(byteData, 0, byteData.Length, 0, OnSend, state);
        }

        private static void OnSend(IAsyncResult ar)
        {
            var state = (State)ar.AsyncState;

            // end sending data to server
            var bytesSent = state.socket.EndSend(ar);

            Console.WriteLine("{0}) Sent {1} bytes to server.", state.clientID, bytesSent);

            // begin receiving response from the server
            state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, OnReceive, state);
        }

        private static void OnReceive(IAsyncResult ar)
        {
            // get the state of the connection
            var state = (State)ar.AsyncState;

            try
            {
                // read data from the server
                var bytesRead = state.socket.EndReceive(ar);

                // convert the bytes recieved from the server to ascii
                state.response.Append(Encoding.ASCII.GetString(state.receiveBuffer, 0, bytesRead));

                // response header not fully obtained, need to recieve more of it
                if (!Utils.FullResponseHeader(state.response.ToString()))
                {
                    state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, OnReceive, state);
                }
                else
                {
                    // header fully obtained, get the body
                    var responseBody = Utils.GetResponseBody(state.response.ToString());

                    // content-length from header
                    var contentLength = Utils.GetContentLength(state.response.ToString());
                    if (responseBody.Length < contentLength)
                    {
                        // the response body wasn't recieved fully, need to recieve more of it
                        state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, OnReceive, state);
                    }
                    else
                    {
                        // all data has been received
                        Console.WriteLine(state.response.ToString());
                        Console.WriteLine("Downloaded {0} bytes from {1}.\n\n", contentLength, state.hostname);

                        // close connection
                        state.socket.Shutdown(SocketShutdown.Both);
                        state.socket.Close();
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}
