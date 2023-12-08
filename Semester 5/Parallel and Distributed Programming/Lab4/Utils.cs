using System;
using System.Net.Sockets;
using System.Net;
using System.Text;
using Lab4.Model;

namespace Lab4
{
    public class Utils
    {
        public static State CreateState(int id, string host)
        {
            var hostEntry = Dns.GetHostEntry(host.Split('/')[0]);
            var ipAddress = hostEntry.AddressList[0];

            // create a new state with the connection information
            var state = new State
            {
                clientID = id,  
                hostname = host.Split('/')[0], 
                socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp), // TCP/IP socket
                endPointPath = host.Contains("/") ? host.Substring(host.IndexOf("/")) : "/",  
                remoteEndPoint = new IPEndPoint(ipAddress, 80)  // new IPEndPoint with the resolved IP address and port 80
            };

            return state;
        }


        public static string GetResponseBody(string response)
        {
            var responseParts = response.Split(new[] { "\r\n\r\n" }, StringSplitOptions.RemoveEmptyEntries);
            return responseParts.Length > 1 ? responseParts[1] : "";
        }

        public static bool FullResponseHeader(string responseContent)
        {
            return responseContent.Contains("\r\n\r\n");
        }

        public static int GetContentLength(string responseContent)
        {
            var responseLines = responseContent.Split('\r', '\n');
            foreach (var responseLine in responseLines)
            {
                var headerDetails = responseLine.Split(':');
                if (headerDetails[0].CompareTo("Content-Length") == 0)
                {
                    return int.Parse(headerDetails[1]);
                }
            }

            return 0;
        }

        public static string GetRequestString(string hostname, string endpoint)
        {
            return "GET " + endpoint + " HTTP/1.1\r\n" +
                    "Host: " + hostname + "\r\n" +
                    "Content-Length: 0\r\n\r\n";
        }
    }
}
