// TCPListenAndOutput.cpp : Defines the entry point for the console application.
//
#include <winnt.h>
#include "stdafx.h"
#include "SMPortInputQueue.h"
#include "SMSocketPort.h"
#include "SMThread.h"
#include "SMEvent.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#define ONE_SECOND 1000

SMString ParseFirstMessage( std::string& buffer )
{
	// Remove any leading whitespace
	string::size_type startPos = buffer.find ("<SMApplicationMessage");

	// Note that this is the only valid comparison for startPos.
	// It is unsigned, so you cannot use startPos > 0 to determine
	// if a substring is found.
	if ( string::npos == startPos ) 
		return SMString("");
		
	buffer.assign( buffer, startPos, buffer.size() - startPos );

	// Naturally, the same applies to endPos.
	string::size_type endPos = buffer.find("</SMApplicationMessage>");
	if ( string::npos == endPos ) 
		return SMString("");
	
	endPos += 23;  //length of "</SMApplicationCommand>"

	// Anything left after the first message is saved.
	std::string leftInBuffer;
	leftInBuffer.assign( buffer, endPos, buffer.size() - endPos );

	// Cut off anthing after the first message.
	buffer.assign( buffer, 0, endPos );

	// Must be at least bigger than the size of the tags.
	SM_ASSERT( buffer.size() > 50 );

	// Create our fully formed message.
	SMString msg( buffer.c_str() );

	// Put the remainder back in the buffer for the next call to parse.
	buffer = leftInBuffer;
	return msg;
}

void StopAndDelete(SMPortInputQueue*& inQ, SMSocketPort*& smPort)
{
	if ( inQ ) 
	{
		inQ->Stop();
		inQ->Clear();
		delete inQ;
		inQ = 0;
	}

	if (smPort)
	{
		delete smPort;
		smPort = 0;
	}
}

class InpThreadClss
{
private:
	static SMEvent	*m_evnt;
public:
	InpThreadClss()
	{
	}
	static void SetEvent(SMEvent *evnt)
	{
		m_evnt = evnt;
	}
	static UINT __stdcall InputThread(SMThread &thread)
	{
		int i;
		std::cin >> i;
		if( m_evnt)
		{
			m_evnt->Set();
		}
		return 0;
	}
};

// rqrd. initialization
SMEvent * InpThreadClss::m_evnt = 0;


int _tmain(int argc, _TCHAR* argv[])
{
	
	SMSocketPort *port = new SMSocketPort("localhost", (unsigned short)3979);
//	SMSocketPort *port = new SMSocketPort("localhost", (unsigned short)3980);
	SMPortInputQueue *inp_q = new SMPortInputQueue( *port );

	// try every second for two minutes

	if (inp_q->Start() != S_OK)
	{
		StopAndDelete( inp_q, port );
	}
	else
	{
		std::cout << "successful start of queue" << std::endl;
		ofstream outFile;
		outFile.open(	"output.txt", 
							ios_base::out  
						|	ios_base::trunc 
						|	ios_base::binary);
	    if(!outFile.is_open())
	    {
	        cout << "Error Opening output.txt\n";
	        return -1;
	    }

		SMEvent			evnt(SMEvent::eManualReset,false,"endwaithandle",0);
		InpThreadClss	inpThrdClss;
		InpThreadClss::SetEvent(&evnt);
//		SMThread * exitSignalThread = new SMThread(SMString("exitSignalThread"),&InpThreadClss::InputThread,&inpThrdClss);
		SMThread * exitSignalThread = new SMThread(SMString("exitSignalThread"),&InpThreadClss::InputThread,0);
		SMEvent & queueChange = inp_q->GetChangedEvent();


		HANDLE *wait_handles = new HANDLE[2];
		wait_handles[0] = queueChange.GetHandle();
		wait_handles[1] = evnt.GetHandle();
		

		bool ThreadIsStillRunning = false;
		
		exitSignalThread->Start();
		

		if(exitSignalThread->IsActive())
		{
			ThreadIsStillRunning = true;
		}

		SMString completeMsg;
		std::string buffer;

		while(ThreadIsStillRunning)
		{
			WaitForMultipleObjects(2,wait_handles,FALSE,INFINITE);
			//WaitForSingleObject(queueChange.GetHandle(), ONE_SECOND);

			if(! exitSignalThread->IsActive())
			{
				ThreadIsStillRunning = false;
			}

			while(inp_q->IsInputPending())
			{

				SMString *inp = inp_q->Pop();
				buffer.append(inp->Data());

				completeMsg = ParseFirstMessage( buffer );
				inp_q->Free(inp);
				if( ! completeMsg.IsEmpty())
				{
					outFile << completeMsg << std::endl;
					outFile.flush();
					outFile << "---------ENDMSG--------" << std::endl;
					outFile.flush();
					outFile << std::endl;
					outFile.flush();
					std::cout << completeMsg << std::endl;
				}
			}
		}

		std::cout << "bye!" << std::endl;

		outFile.close();

		// normal processing
		StopAndDelete( inp_q, port );
	}
	return 0;
}

