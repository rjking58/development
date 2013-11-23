using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Diagnostics;


namespace SMManagerMock
{
    public class IOPort
    {
        private TcpClient       _client;
        private bool            _keepAlive = true;
        private ServiceMock     _mock = null;
		private AutoResetEvent _receivedSignal = null;
        private const string    END_MESSAGE_MARKER = "</SMApplicationMessage>";
        //This buffer is used to keep part of message until another part of it will come from the buffer
        private byte[] holdoverBuffer = null;

        public IOPort(  TcpClient Client,
						AutoResetEvent receivedSignal,
                        ServiceMock mock)
        {
            _client = Client;
            _mock = mock;
			_receivedSignal = receivedSignal;

            Thread _thread = new Thread(new ThreadStart(DoCommunication));
            _thread.Start();
        }

        public void Stop()
        {
            _keepAlive = false;
        }

        public bool IsConnected
        {
            get { return _client.Connected; }
        }

        public void Send(byte[] buffer)
        {
            NetworkStream ns = null;
            try
            {
                lock (this)
                {
                    ns = _client.GetStream();
                    if (ns != null)
                        ns.Write(buffer, 0, buffer.Length);
                    else
                        throw new ApplicationException("NetworkStream does not exist for Send(1)");
                }
            }
            catch (Exception ex)
            {
                string s = ex.StackTrace;
            }
        }


        private void MessageSplitter(byte[] conditioned_buffer)
        {
            //-------------------------------------
            //Lets cut incoming messages right from the socket
            
            string sReceived = Encoding.UTF8.GetString(conditioned_buffer);

            int index = sReceived.IndexOf("</SMApplicationMessage>");
            if (index < 0)
            {
                Trace.WriteLine("holding data over (missing end)");
                holdoverBuffer = conditioned_buffer;

                return;
            }
            else
            {
                if (conditioned_buffer.Length == index + END_MESSAGE_MARKER.Length)
                {
                    Trace.WriteLine("storing current");
                    char[] conditioned_char_buffer = new char[conditioned_buffer.Length];
                    conditioned_buffer.CopyTo(conditioned_char_buffer,0);
					//System.Console.WriteLine("rcvd1:" + Encoding.UTF8.GetString(conditioned_buffer));
                    _mock.AddRcvdMessage = new String(conditioned_char_buffer);
					_receivedSignal.Set();
                }
                else
                {
                    byte[] temp = new byte[index + END_MESSAGE_MARKER.Length];
                    Array.Copy(conditioned_buffer, 0, temp, 0, temp.Length);
                    Trace.WriteLine(Encoding.UTF8.GetString(temp));
                    char[] temp_char = new char[temp.Length];
                    temp.CopyTo(temp_char,0);
					//System.Console.WriteLine("rcvd2:" + Encoding.UTF8.GetString(temp));
                    _mock.AddRcvdMessage = new String(temp_char);
					_receivedSignal.Set();


                    temp = new byte[conditioned_buffer.Length - (index + END_MESSAGE_MARKER.Length)];
                    Array.Copy(conditioned_buffer, index + END_MESSAGE_MARKER.Length, temp, 0, temp.Length);

                    MessageSplitter(temp);
                }
            }
        }

        private void DoCommunication()
        {
            while(_client.Connected && _keepAlive)
            {
                if (_client.Available > 0)
                {
                    Trace.WriteLine("IOPORT:receiving data..");
					int rawReceiptBufferSize = 0;
					byte[] rawReceiptBuffer = null;
					lock (this)
					{
	                    NetworkStream stream = _client.GetStream();

	                    rawReceiptBuffer = new byte[_client.ReceiveBufferSize];

						rawReceiptBufferSize = stream.Read(rawReceiptBuffer, 0, _client.ReceiveBufferSize);
					}
					

                    //If there is something in tempBuffer it has to added to the incoming buffer
                    byte[] rawPlusHoldoverBuffer;

                    if (holdoverBuffer != null)
                    {
                        rawPlusHoldoverBuffer = new byte[rawReceiptBufferSize + holdoverBuffer.Length];

                        Array.Copy(holdoverBuffer, 0, rawPlusHoldoverBuffer, 0, holdoverBuffer.Length);
                        Array.Copy(rawReceiptBuffer, 0, rawPlusHoldoverBuffer, holdoverBuffer.Length, rawReceiptBufferSize);

                        holdoverBuffer = null;
                    }
                    else
                    {
                        rawPlusHoldoverBuffer = new byte[rawReceiptBufferSize];

                        Array.Copy(rawReceiptBuffer, rawPlusHoldoverBuffer, rawReceiptBufferSize);
                    }

                    //There could be leading zeros in the received bytes lets cut them
                    int index = 0;
                    while (index < rawPlusHoldoverBuffer.Length && rawPlusHoldoverBuffer[index] == 0) index++;

                    //If we still have something after cutting zeros lets split messages
                    if (index != rawPlusHoldoverBuffer.Length)
                    {

                        byte[] conditioned_buffer = new byte[rawPlusHoldoverBuffer.Length - index];
                        Array.Copy(rawPlusHoldoverBuffer, index, conditioned_buffer, 0, conditioned_buffer.Length);
                        char [] conditioned_char_buffer = new char[conditioned_buffer.Length];
                        conditioned_buffer.CopyTo(conditioned_char_buffer,0);
                        String str = new String(conditioned_char_buffer);
                        Trace.WriteLine("IOPORT: ConditionedBuffer[" + str  + "]");

                        MessageSplitter(conditioned_buffer);
                    }
                }

                if (_client.Available == 0) Thread.Sleep(20);
            }

            _client.Close();
        }
    }
}
