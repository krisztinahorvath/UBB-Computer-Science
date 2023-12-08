using System.Net;
using System.Net.Security;
using System.Net.Sockets;
using System.Text;


namespace Lab4.Model
{
    public class State
    {
        public Socket socket;
        public const int BUFFER_SIZE = 1024;
        public byte[] receiveBuffer = new byte[BUFFER_SIZE];
        public StringBuilder response = new StringBuilder();
        public int clientID;
        public string hostname;
        public string endPointPath;
        public IPEndPoint remoteEndPoint;
        public ManualResetEvent connectDone = new ManualResetEvent(false);
        public ManualResetEvent sendDone = new ManualResetEvent(false);
        public ManualResetEvent receiveDone = new ManualResetEvent(false);
    }
}
