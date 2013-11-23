using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Diagnostics;

namespace SMManagerMock
{
    class Program
    {
        static bool _continue = true;
        static AutoResetEvent connectorDone = new AutoResetEvent(false);

        static void Main(string[] args)
        {
			bool endProgram = false;
            ServiceMock mock = new ServiceMock(3980);
            mock.StartListener();


            AutoResetEvent[] connectedSignal = new AutoResetEvent[1];
            connectedSignal[0] = mock.ConnectedSignal;
            WaitHandle.WaitAll(connectedSignal);
            Trace.WriteLine("mock is connected!");
//            _continue = false;
//            AutoResetEvent [] connector_signals = new AutoResetEvent[1];
//            connector_signals[0] = connectorDone;
//            WaitHandle.WaitAll(connector_signals);

			// wait for an input signal, and read the command.
			
            AutoResetEvent[] receivedSignal = new AutoResetEvent[1];
            receivedSignal[0] = mock.ReceivedSignal;
            WaitHandle.WaitAll(receivedSignal);
			receivedSignal[0].Reset();
			List<string> receivedMessages = mock.ReceivedMessages;
			Thread.Sleep(20);
			while (!endProgram)
			{
				if (receivedMessages.Count > 0)
				{
					System.Text.ASCIIEncoding enc = new System.Text.ASCIIEncoding();
					string msg;

					byte[] msg_bytes = null;
					foreach (String str in receivedMessages)
					{
						System.Console.WriteLine("rawmsg:" + str);
						int msgs_received = 0;
						int MAX_TO_RECEIVE = 0;

						switch (str)
						{
							case "<SMApplicationMessage><stop></SMApplicationMessage>":
								endProgram = true;
								break;
							case "<SMApplicationMessage><test_hardwareswitch></SMApplicationMessage>":
								System.Console.WriteLine("<test_hardwareswitch>.. executing");
								msgs_received = 0;
								MAX_TO_RECEIVE = 1;
								while (msgs_received < MAX_TO_RECEIVE)
								{
									msg =	"<SMApplicationMessage><hardwareswitch>true</hardwareswitch><cnt>"
											+ msgs_received
											+ "</cnt></SMApplicationMessage>";
									msg_bytes = enc.GetBytes(msg);
									if (mock.SendToAll(msg_bytes))
									{
										msgs_received++;
									}
								}
								System.Console.WriteLine(msgs_received);
								break;
							case "<SMApplicationMessage><test_networkstatus></SMApplicationMessage>":
								System.Console.WriteLine("<test_networkstatus>");
								msgs_received = 0;
								MAX_TO_RECEIVE = 1;
								byte[] networkDvcStateMsg = TestXMLs.GetNetworkDeviceState();
								while (msgs_received < MAX_TO_RECEIVE)
								{
									if (mock.SendToAll(networkDvcStateMsg))
										msgs_received++;
								}
								System.Console.WriteLine(msgs_received);
								break;
							case "<SMApplicationMessage><test_connectTP></SMApplicationMessage>":
								msg =	"<SMApplicationMessage TypeId=\"ConnectTechnologyProfile\" ClientID=\"testprog\"><cnt>"
										+ msgs_received
										+ "</cnt></SMApplicationMessage>";
								System.Console.WriteLine("<test_connectTP>");
								msg_bytes = enc.GetBytes(msg);

								msgs_received = 0;
								MAX_TO_RECEIVE = 1;

								while (msgs_received < MAX_TO_RECEIVE)
								{
									if (mock.SendToAll(msg_bytes))
										msgs_received++;
								}
								System.Console.WriteLine(msgs_received);
								break;
							case "<SMApplicationMessage><test_disconnectTP></SMApplicationMessage>":
								msg =	"<SMApplicationMessage TypeId=\"DisconnectTechnologyProfile\" ClientID=\"testprog\"><cnt>"
										+ msgs_received
										+ "</cnt></SMApplicationMessage>";
								System.Console.WriteLine("<test_connectTP>");
								msg_bytes = enc.GetBytes(msg);

								msgs_received = 0;
								MAX_TO_RECEIVE = 1;

								while (msgs_received < MAX_TO_RECEIVE)
								{
									if (mock.SendToAll(msg_bytes))
										msgs_received++;
								}
								System.Console.WriteLine(msgs_received);
								break;
							default:
								break;
						}
					}
				}
				receivedMessages.Clear();
	            WaitHandle.WaitAll(receivedSignal);
				receivedMessages = mock.ReceivedMessages;
				Thread.Sleep(20);
			}

            mock.Stop();
#if false
			List<String> msgs = null;
			int rcvd_cnt = 0;
            foreach (String s in msgs)
            {
                Trace.WriteLine("received(" + s.Length + "):" + s);
				rcvd_cnt++;
            }
			Trace.WriteLine("received:" + rcvd_cnt);
#endif
        }
    }
}
