using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Diagnostics;

namespace SMManagerMock
{
    public class ServiceMock
    {
        private TcpListener     _listener;
        private bool            _keepListen;
        public List<IOPort>     Clients = new List<IOPort>();
        private List<String>    m_rcvdMessages = new List<string>();
        private Object          m_rcvdMessagesLock = new object();

        private AutoResetEvent  m_connectedSignal = new AutoResetEvent(false);
        private AutoResetEvent  m_msgReceivedSignal = new AutoResetEvent(false);

        public AutoResetEvent ConnectedSignal
        {
            get
            {
                return m_connectedSignal;
            }
        }
        public AutoResetEvent ReceivedSignal
        {
            get
            {
                return m_msgReceivedSignal;
            }
        }

        public ServiceMock(int PortNumber)
        {
#pragma warning disable 0618  // this function is deprecated compiler suggests using TcpListener(IPAddress localaddr, int port) instead
            _listener = new TcpListener(PortNumber);
#pragma warning restore 0618
        }

        internal string AddRcvdMessage
        {
            set
            {
                lock (m_rcvdMessagesLock)
                {
                    m_rcvdMessages.Add(value);
                }
            }
        }

        public List<String> ReceivedMessages
        {
            get
            {
                List<String> retVal = new List<string>();
                lock (m_rcvdMessagesLock)
                {
                    foreach (String str in m_rcvdMessages)
                    {
                        retVal.Add(str);
                    }
                    m_rcvdMessages.Clear();
                }
                return retVal;
            }
        }
        public void StartListener()
        {

            _listener.Start();
            _keepListen = true;

            Thread thread = new Thread(new ThreadStart(DoListen));
            thread.Name = "TCPListenServer";
            thread.Start();
        }

        private void DoListen()
        {
            while (_keepListen)
            {
                Thread.Sleep(1);
                if (_listener.Pending())
                {
                    TcpClient _client = _listener.AcceptTcpClient();
                    Trace.WriteLine("Client connected...");
					_client.SendBufferSize = 4095;
					System.Console.WriteLine(_client.Client.AddressFamily);
					System.Console.WriteLine(_client.Client.ProtocolType);
					System.Console.WriteLine(_client.Client.SocketType);

                    IOPort port = new IOPort(_client,m_msgReceivedSignal,this);
                    Clients.Add(port);
                    m_connectedSignal.Set();
                }

                //Check if all clients are alive
                for (int i = 0; i < Clients.Count; i++)
                {
                    IOPort port = Clients[i];

                    if (!port.IsConnected)
                    {
                        Trace.WriteLine("Dead client detected... Will be removed. ");
                        Clients.Remove(port);
                    }
                }
            }

            _listener.Stop();
        }

        public bool SendToAll(byte[] buffer)
        {
			bool sendSuccessful = false;
            for (int i = 0; i < Clients.Count; i++)
            {
                IOPort port = Clients[i];

                if (port.IsConnected)
                {
                    try
                    {
                        port.Send(buffer);
//						Thread.Sleep(30);
						sendSuccessful = true;
                    }
                    catch
					{
						sendSuccessful = false;
					}
                }
                else
                {
                    Trace.WriteLine("Dead client detected... Will be removed. ");
                    Clients.Remove(port);
                }
            }
			return sendSuccessful;
        }

        public void Stop()
        {
            _keepListen = false;

            foreach (IOPort port in Clients)
            {
                port.Stop();
            }
			Thread.Sleep(20);
        }
    }
}
