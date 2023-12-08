using Lab4.Model;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Lab4.Implementation
{
    public class TaskMechanism
    {
        public static void Run(List<string> hostnames)
        {
            var tasks = new Task[hostnames.Count];

            for (var i = 0; i < hostnames.Count; i++)
            {
                var index = i; // otherwise all tasks will reference same index, since it takes the reference of the variable, not the value itself
                tasks[i] = Task.Factory.StartNew(() => Start(index, hostnames[index]));
            }

            Task.WaitAll(tasks);
        }

        private static void Start(int id, string hostname)
        {
            // set up connection
            var state = Utils.CreateState(id, hostname);

            // connect to the remote endpoint
            Connect(state).Wait();

            
            // request data from the server
            Send(state, Utils.GetRequestString(state.hostname, state.endPointPath)).Wait();

            // receive data from the server
            Receive(state).Wait();

            Console.WriteLine(state.response.ToString());
            Console.WriteLine("Downloaded {0} bytes from {1}.\n\n", Utils.GetResponseBody(state.response.ToString()).Length, state.hostname);

            // close connection
            state.socket.Shutdown(SocketShutdown.Both);
            state.socket.Close();
        }

        private static Task Connect(State state)
        {
            state.socket.BeginConnect(state.remoteEndPoint, ConnectCallback, state);
            return Task.FromResult(state.connectDone.WaitOne());
        }

        private static void ConnectCallback(IAsyncResult ar)
        {
            // get the state of the connection
            var state = (State)ar.AsyncState;

            // complete the connection  
            state.socket.EndConnect(ar);

            Console.WriteLine("{0}) Socket connected to {1} ({2})", state.clientID, state.hostname, state.socket.RemoteEndPoint);

            // signal that the connection has been made 
            state.connectDone.Set();
        }

        private static Task Send(State state, string data)
        {
            // convert the string data to byte data using ASCII encoding.  
            var byteData = Encoding.ASCII.GetBytes(data);

            // begin sending the data to the server  
            state.socket.BeginSend(byteData, 0, byteData.Length, 0, SendCallback, state);

            return Task.FromResult(state.sendDone.WaitOne());
        }

        private static void SendCallback(IAsyncResult ar)
        {
            // get the state of the connection
            var state = (State)ar.AsyncState;

            // complete sending the data to the server  
            var bytesSent = state.socket.EndSend(ar);
            Console.WriteLine("{0}) Sent {1} bytes to server.", state.clientID, bytesSent);

            // signal that all bytes have been sent  
            state.sendDone.Set();
        }

        private static Task Receive(State state)
        {
            // begin receiving the data from the server  
            state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, ReceiveCallback, state);

            return Task.FromResult(state.receiveDone.WaitOne());
        }

        private static void ReceiveCallback(IAsyncResult ar)
        {
            // retrieve the details from the connection information wrapper
            var state = (State)ar.AsyncState;
    
            try
            {
                // read data from the remote device.  
                var bytesRead = state.socket.EndReceive(ar);

                // get from the buffer, a number of characters <= the buffer size, and store it in the responseContent
                state.response.Append(Encoding.ASCII.GetString(state.receiveBuffer, 0, bytesRead));

                // if the response header has not been fully obtained, get the next chunk of data
                if (!Utils.FullResponseHeader(state.response.ToString()))
                {
                    state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, ReceiveCallback, state);
                }
                else
                {
                    // header has been fully obtained
                    // get the body
                    var responseBody = Utils.GetResponseBody(state.response.ToString());

                    // the custom header parser is being used to check if the data received so far has the length specified in the response headers
                    if (responseBody.Length < Utils.GetContentLength(state.response.ToString()))
                    {
                        // if it isn't, then more data is to be recieved
                        state.socket.BeginReceive(state.receiveBuffer, 0, State.BUFFER_SIZE, 0, ReceiveCallback, state);
                    }
                    else
                    {
                        // all the data has been received  
                        // signal that all bytes have been received  
                        state.receiveDone.Set();
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
