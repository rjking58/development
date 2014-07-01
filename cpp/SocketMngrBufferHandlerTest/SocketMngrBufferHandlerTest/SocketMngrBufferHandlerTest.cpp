// SocketMngrBufferHandlerTest.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <assert.h>
#include <queue>

#include </dev/Mobile/Orbiter/Source Code/SMUtilities/SMString.h>

typedef std::string SMUTFBuffer;

SMUTFBuffer m_buffer;

std::queue<SMString> m_inQ;


SMString GetXmlMessage()
{
	// Pull strings from the input queue into our message buffer.
    if( ! m_inQ.empty ())
    {
        do
    	{
        	SMString psTemp = m_inQ.front ();
            m_inQ.pop ();
    		// The incoming string was null terminated by the port input queue.
    		// We use a vector of characters to prevent any further narrow->wide conversions on buffers with a partial UTF sequence.
    		m_buffer.append( psTemp.Data() );
    	}
        while( ! m_inQ.empty ());
    }

	// Parse message buffer into messages.
	SMString msg("");
	string::size_type nStartPos = m_buffer.find ("<?xml version=\"1.0\"");
	if ( string::npos == nStartPos )
		return msg; //wait for more data
	
	// Slide the start of the message to the beginning of the buffer.
	if (nStartPos > 0)
		m_buffer.assign( m_buffer, nStartPos, m_buffer.size() - nStartPos );

	string::size_type nEndPos = 0;
	string::size_type nEndPos1 = m_buffer.find("</SMApplicationMessage>");
	string::size_type nEndPos2 = m_buffer.find("</SMApplicationCommand>");
	string::size_type nEndPos3 = m_buffer.find("</SMApplicationRequest>");

    if ( (string::npos == nEndPos1) && (nEndPos1 == nEndPos2) && (nEndPos2 == nEndPos3) )
		return msg; //wait for more data
	else
	{
		nEndPos = nEndPos1 < nEndPos2 ? nEndPos1 : nEndPos2;
		nEndPos = nEndPos < nEndPos3 ? nEndPos : nEndPos3;
	}
	
	nEndPos += 23;  //length of "</SMApplicationCommand>"

	//std::string csExtra;
	//csExtra.assign( m_buffer, nEndPos, m_buffer.size() - nEndPos );

	string smsg;
	smsg.assign( m_buffer, 0, nEndPos );

	// Must be at least bigger than the size of the tags.
	assert(smsg.size() > 50 );

	// msg = m_buffer.c_str();
	// m_buffer = csExtra;
	m_buffer.assign( m_buffer, nEndPos, m_buffer.size() - nEndPos );

	return SMString(smsg);
}

void TestTwoMsgs(SMString first_part,
                 SMString second_part)
{

    SMString rslt = GetXmlMessage();
    assert(rslt.Compare (first_part) == 0);
    rslt = GetXmlMessage();
    assert(rslt.Compare (second_part) == 0);
}

void TestThreeMsgs(SMString first_part,
                   SMString second_part,
                   SMString third_part)
{

    SMString rslt = GetXmlMessage();
    assert(rslt.Compare (first_part) == 0);
    rslt = GetXmlMessage();
    assert(rslt.Compare (second_part) == 0);
    rslt = GetXmlMessage();
    assert(rslt.Compare (third_part) == 0);
}

int _tmain(int argc, _TCHAR* argv[])
{

    SMString rslt;
    SMString single_Msg = "<?xml version=\"1.0\" encoding=\"utf-8\" ?> <SMApplicationMessage TypeId=\"WiFiEvent\" ClientID=\"\" CommandToken=\"\" Timestamp=\"2009-06-25T16:36:24.296-07:00\"> <wifievent> <wifievent>15</wifievent> <wifieventstr>CONNECTION_END</wifieventstr> <alias></alias> <ssid></ssid> <cnt>1</cnt> </wifievent> </SMApplicationMessage>";
    SMString single_Req = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <SMApplicationRequest xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" TypeId=\"GetSystemConfiguration\" ClientID=\"RKING-E5400|1|5524\" Username=\"rking\" Timestamp=\"2009-06-25T16:36:27.9159238-07:00\" CommandToken=\"671798733\"> <key /><cnt>1</cnt> </SMApplicationRequest>";
    SMString single_Cmd = "<?xml version=\"1.0\" encoding=\"utf-8\" ?> <SMApplicationCommand TypeId=\"xxxEvent\" ClientID=\"\" CommandToken=\"\" Timestamp=\"2009-06-25T16:36:24.296-07:00\"> <wifievent> <wifievent>15</wifievent> <wifieventstr>CONNECTION_END</wifieventstr> <alias></alias> <ssid></ssid><cnt>1</cnt> </wifievent> </SMApplicationCommand>";

    // with embedded null..
    SMString single_Req_NULL = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <SMApplicationRequest \x00 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" TypeId=\"GetSystemConfiguration\" ClientID=\"RKING-E5400|1|5524\" Username=\"rking\" Timestamp=\"2009-06-25T16:36:27.9159238-07:00\" CommandToken=\"671798733\"> <key /><cnt>1</cnt> </SMApplicationRequest>";

    m_inQ.push (single_Msg);
    m_inQ.push ("    ");
    m_inQ.push (single_Msg);

    m_inQ.push (single_Msg);
    m_inQ.push ("     ");
    m_inQ.push (single_Req);

    m_inQ.push (single_Msg);
    m_inQ.push ("     ");
    m_inQ.push (single_Cmd);

    m_inQ.push (single_Req);
    m_inQ.push ("     ");
    m_inQ.push (single_Req);

    m_inQ.push (single_Req_NULL);
    m_inQ.push (" \x00  ");
    m_inQ.push (single_Msg);

    m_inQ.push (single_Req);
    m_inQ.push (" \x01   ");
    m_inQ.push (single_Cmd);

    m_inQ.push (single_Cmd);
    m_inQ.push ("     ");
    m_inQ.push (single_Cmd);

    m_inQ.push (single_Cmd);
    m_inQ.push ("     ");
    m_inQ.push (single_Msg);

    m_inQ.push (single_Cmd);
    m_inQ.push ("     ");
    m_inQ.push (single_Req);

    m_inQ.push (single_Msg);
    m_inQ.push ("     ");
    m_inQ.push (single_Msg);
    m_inQ.push ("     ");
    m_inQ.push (single_Msg);

    TestTwoMsgs (single_Msg,single_Msg);
    TestTwoMsgs (single_Msg,single_Req);
    TestTwoMsgs (single_Msg,single_Cmd);
    TestTwoMsgs (single_Req,single_Req);
    TestTwoMsgs (single_Req,single_Msg);
    TestTwoMsgs (single_Req,single_Cmd);
    TestTwoMsgs (single_Cmd,single_Cmd);
    TestTwoMsgs (single_Cmd,single_Msg);
    TestTwoMsgs (single_Cmd,single_Req);
    TestThreeMsgs( single_Msg,
                   single_Msg,
                   single_Msg);

	return 0;
}



