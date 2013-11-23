//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMXmlDom.cpp $
//  Package : SMUtilities
//
//  Copyright ?2007-2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Tfiner $
//  $Date: 9/15/08 12:16p $
//  $Modtime: 9/05/08 5:16p $
//  $Revision: 49 $
//
//  TODO: Add description here.
//
//----------------------------------------------------------------------------

#ifndef VersionControlHistory
// $History: SMXmlDom.cpp $
// 
// *****************  Version 49  *****************
// User: Tfiner       Date: 9/15/08    Time: 12:16p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 48  *****************
// User: Jwu          Date: 7/22/08    Time: 6:11p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// TT 1850
// 
// *****************  Version 47  *****************
// User: Jwu          Date: 7/22/08    Time: 5:38p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 1850
// 
// *****************  Version 46  *****************
// User: Jwu          Date: 7/18/08    Time: 6:04p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// TT 1850
// 
// *****************  Version 45  *****************
// User: Tfiner       Date: 7/18/08    Time: 4:21p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Put the old settext tests back in, but log the failures now instead of
// bailing out.
// 
// *****************  Version 44  *****************
// User: Jwu          Date: 7/17/08    Time: 11:28p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added comments for TT 1850 fix
// 
// *****************  Version 43  *****************
// User: Jwu          Date: 7/16/08    Time: 8:00p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// TT 1850
// 
// *****************  Version 42  *****************
// User: Tfiner       Date: 7/02/08    Time: 5:49p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Get rid of faulty test for null.
// 
// *****************  Version 41  *****************
// User: Tfiner       Date: 7/01/08    Time: 9:51p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Error check result.
// 
// *****************  Version 40  *****************
// User: Tfiner       Date: 6/09/08    Time: 2:20p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixes for bugs: 1237 and 1520.
// 1. Explicitly convert narrow to wide using UTF8 codepage.
// 2. Use wide char functions.
// 
// *****************  Version 39  *****************
// User: Tfiner       Date: 4/24/08    Time: 4:04p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Got rid of a First Chance exception with each XML message parse.
// 
// *****************  Version 38  *****************
// User: Zsukhanov    Date: 4/03/08    Time: 4:39a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Remove deprecated methods
// 
// *****************  Version 37  *****************
// User: Cchang       Date: 3/31/08    Time: 11:22a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// put back Arodriguez's version since GetString has problem...
// 
// *****************  Version 35  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 34  *****************
// User: Vtokarev     Date: 18.01.08   Time: 9:42
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 33  *****************
// User: Sanderson    Date: 1/17/08    Time: 11:50a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Commented out calls to XML node release that are no longer needed.
// 
// *****************  Version 32  *****************
// User: Sanderson    Date: 1/16/08    Time: 10:10p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// restored formatting of XML
// 
// *****************  Version 31  *****************
// User: Vtokarev     Date: 16.01.08   Time: 16:35
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 30  *****************
// User: Vtokarev     Date: 16.01.08   Time: 11:47
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 29  *****************
// User: Vtokarev     Date: 15.01.08   Time: 12:19
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 28  *****************
// User: Vtokarev     Date: 15.01.08   Time: 9:14
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 27  *****************
// User: Vtokarev     Date: 15.01.08   Time: 8:56
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 26  *****************
// User: Vtokarev     Date: 14.01.08   Time: 15:18
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 25  *****************
// User: Vtokarev     Date: 14.01.08   Time: 13:34
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 24  *****************
// User: Vtokarev     Date: 10.12.07   Time: 10:24
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 23  *****************
// User: Ozhuk        Date: 12/03/07   Time: 4:26p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 22  *****************
// User: Ozhuk        Date: 12/03/07   Time: 3:56p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 21  *****************
// User: Ozhuk        Date: 12/03/07   Time: 3:26p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// LocationTechnologyProfile added.
// 
// *****************  Version 20  *****************
// User: Sanderson    Date: 11/30/07   Time: 7:47p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixed more handle leaks
// 
// *****************  Version 19  *****************
// User: Sanderson    Date: 11/30/07   Time: 7:20p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// fixed handle leaks
// 
// *****************  Version 18  *****************
// User: Admin        Date: 11/27/07   Time: 3:18p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// AccessPoint class added.
// 
// *****************  Version 17  *****************
// User: Sanderson    Date: 11/16/07   Time: 3:03p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Embedded 'ReadableXML' XSL into code
// 
// *****************  Version 16  *****************
// User: Sanderson    Date: 11/15/07   Time: 7:03p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Restored XML formatting for debug
// 
// *****************  Version 15  *****************
// User: Admin        Date: 11/12/07   Time: 10:32a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// WriteTextString overload to use pNode was added.
// 
// *****************  Version 14  *****************
// User: Admin        Date: 11/09/07   Time: 10:34a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added AppendChild method, which can be used to add several nodes with
// the same name to the same parent node.
// 
// *****************  Version 13  *****************
// User: Admin        Date: 11/01/07   Time: 6:52a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 12  *****************
// User: Admin        Date: 10/30/07   Time: 11:33a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// New Serialization format.
// 
// *****************  Version 11  *****************
// User: Sanderson    Date: 10/02/07   Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Chagnes to fix HEAP errors
// 
// *****************  Version 10  *****************
// User: Sanderson    Date: 9/27/07    Time: 7:18p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added "ReadTextString" to get the text between nodes
// 
// *****************  Version 9  *****************
// User: Jwu          Date: 9/24/07    Time: 3:09p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Upgraded to MSXML 6.0
// 
// *****************  Version 8  *****************
// User: Sanderson    Date: 9/21/07    Time: 1:26a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added code to retrieve vector<SMString> members
// Fixed HEAP errors
// 
// *****************  Version 7  *****************
// User: Jwu          Date: 9/13/07    Time: 5:47p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Changed to use GetXml method in SMXmlDom class
// 
// *****************  Version 6  *****************
// User: Jwu          Date: 9/13/07    Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 5  *****************
// User: Jwu          Date: 9/12/07    Time: 2:09p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 4  *****************
// User: Jwu          Date: 9/12/07    Time: 1:05p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 3  *****************
// User: Jwu          Date: 9/12/07    Time: 1:33a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 2  *****************
// User: Jwu          Date: 9/11/07    Time: 11:47p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 9/07/07    Time: 2:41p
// Created in $/Mobile/Orbiter/Source Code/SMUtilities
// Added SMXmlDom Class.
#endif

#include "StdAfx.h"
#include "SMXmlDom.h"
#include "SMTraceUtility.h"
#include "SMException.h"
//#include <SMUtilities/SMMutex.h>
#include "SMSingleLock.h"
//#include <SMUtilities/SM.h>
#include "SMRuntimeException.h"


#include <sstream>
#include <iomanip>
using namespace std;

//----------------------------------------------------------------------------

SMXmlDom::SMXmlDom(bool bReadableFormat /* = false */)
    : document(NULL), xsl(NULL)
{
    SM_TRY

    // Initialize COM
    ::CoInitialize(NULL);

    // Create an instance of the XML document COM object
    HRESULT hr = this->document.CreateInstance(__uuidof(DOMDocument));
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::SMXmlDom(): Failed to create XML parser instance!");
    }
    else
    {
        // Create a default document
        hr = CreateNew();
        if (FAILED(hr))
        {
            SM_LOG(hr, 1, "SMXmlDom::SMXmlDom(): Failed to create a default document!");
        }
    }

	if (bReadableFormat)
	{
		// Create an instance of the XSL document COM object
		hr = this->xsl.CreateInstance(__uuidof(DOMDocument));
		if (FAILED(hr))
		{
			SM_LOG(hr, 1, "SMXmlDom::SMXmlDom(): Failed to create XML parser instance!");
		}
		else
		{
			// Create a default document
//			VARIANT_BOOL varBoolSuccess = FALSE;

			SMString bstrXml = "<?xml version=\"1.0\" ?>\
	<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">\
		<xsl:output method=\"xml\" omit-xml-declaration=\"yes\"/>\
		<xsl:param name=\"singleIndent\" select=\"'    '\"/>\
		<xsl:template name=\"doIndent\">\
			<xsl:for-each select=\"ancestor::*\">\
				<xsl:value-of select=\"$singleIndent\"/>\
			</xsl:for-each>\
		</xsl:template>\
		<xsl:template match=\"text()\">\
			<xsl:copy/>\
		</xsl:template>\
		<xsl:template match=\"@*\">\
			<xsl:copy/>\
		</xsl:template>\
		<xsl:template match=\"*[text()]\">\
			<xsl:call-template name=\"doIndent\"/>\
			<xsl:copy>\
				<xsl:apply-templates select=\"node() | @*\"/>\
			</xsl:copy>\
			<xsl:value-of select=\"'&#xA;'\"/>\
		</xsl:template>\
		<xsl:template match=\"*[*]\">\
			<xsl:call-template name=\"doIndent\"/>\
			<xsl:copy>\
				<xsl:apply-templates select=\"@*\"/>\
				<xsl:value-of select=\"'&#xA;'\"/>\
				<xsl:apply-templates select=\"node()\"/>\
				<xsl:call-template name=\"doIndent\"/>\
			</xsl:copy>\
			<xsl:value-of select=\"'&#xA;'\"></xsl:value-of>\
		</xsl:template>\
		<xsl:template match=\"*\">\
			<xsl:call-template name=\"doIndent\"/>\
			<xsl:copy>\
				<xsl:apply-templates select=\"node() | @*\"/>\
			</xsl:copy>\
			<xsl:value-of select=\"'&#xA;'\"/>\
		</xsl:template>\
	</xsl:stylesheet>";

			if ( VARIANT_TRUE != this->xsl->loadXML(bstrXml.DataW()))
			{
				SM_TRACE(1, "SMXmlDom::SMXmlDom(): Failed to load built-in 'WsmTxt.xsl' document : " << (LPCSTR)this->xsl->parseError->Getreason());
			}
		}
	}
    SM_CATCH_ALL_DEFAULT_NO_HR
}

//----------------------------------------------------------------------------

SMXmlDom::~SMXmlDom()
{
	this->document = NULL;
	this->xsl = NULL;
	this->activeNode = NULL; // Prevent a first chance Exception in ::CoUninitialize below.
    // Deactivate COM
    ::CoUninitialize();
}

//----------------------------------------------------------------------------

HRESULT SMXmlDom::CreateNew()
{
	if ( NULL == document )
		return S_FALSE;

    HRESULT hr = S_OK;

    SM_TRY
	
	MSXML2::IXMLDOMProcessingInstructionPtr pi = this->document->createProcessingInstruction("xml", "version='1.0'");
	if (pi != NULL) 
	{
		this->document->appendChild(pi);
	}
	else
	{
		hr = E_FAIL;
	}
	this->activeNode = this->document;

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------


SMString SMXmlDom::GetLastParserError()
{
	int error = this->document->parseError->errorCode;
	int errLine = this->document->parseError->line;
	int errPos = this->document->parseError->linepos;
	int filePos = this->document->parseError->filepos;

	// Note: static_cast<>() is not the same as the (const char*) operator!
	const char* src = (const char*)this->document->parseError->srcText;
	const char* reason = (const char*)this->document->parseError->reason;
	stringstream ss;
	ss  << setfill('0');
	ss  << "!!!!! loadXML failed :\n"
		<< "error code: " << "0x" << hex << setw(8) << error << "\n";

	if ( reason )
		ss << "reason: " << reason << "\n";

	ss  << "at byte number " << "0x" << hex << setw(8) << filePos << "\n"
		<< "at line : " << errLine << " at character: " << errPos << "\n";

	if ( src )
		ss << "src text:\n"	<< src;

	return SMString(ss.str());
}

void SMXmlDom::LoadXml(const SMString& sXml)
{
	SM_ASSERT( IsUTF8(sXml) && "XML strings must be in UTF8 format!" );
	if ( !IsUTF8(sXml) )
		SM_TRACE(3, "IsUTF failed.  XML strings must be in UTF8 format.");

	// This could probably be put right before the usage of the document pointer.
	SMSingleLock SingleLock(&m_Mutex, true);

	// Bugs 1527 && 1237
	// Explicitly use wide version of string to prevent XML parsing errors.
	// Otherwise, the parser will die with end tag mismatches, etc.

	// Explicitly convert the narrow characters already in UTF-8 into wide characters.
	// We could use the default conversion of narrow->wide, but we wouldn't know if there
	// were any invalid UTF8 characters.

	// This makes the parser happy.  Earlier documentation for loadXML states that the passed
	// in string must be UTF16, but then docs for 3+ of MSXML say that it is no longer necessary.
	// However, if _bstr_t is given a narrow string, it up converts it to wide.  Since bstr_t clearly
	// doesn't use the CP_UT8 codepage, the parser only sometimes parses correctly.
	wstring wide = NarrowToWide( sXml.Data(), CP_UTF8, true );
	if ( wide.empty() )
	{
		SM_TRACE(1, "NarrowToWide failed.  Usually this means that there are invalid chars in the narrow string.");
		return;
	}

	// More explicit conversion.
	const _bstr_t bwide0( wide.c_str() );
	if ( VARIANT_TRUE != this->document->loadXML(bwide0) )
	{
		SMString error = GetLastParserError();

#if defined(XML_DOM_DEBUG)
		OutputDebugString( error );
#endif
		SM_TRACE(1, "SMXmlDom::LoadXml failed : " << error );

		// @@ HACK:
		// For some reason, passing in a const char* directly to SMRuntimeException
		// causes a memory exception of its own later!  This should be investigated.
		SMString s("SMXmlDom::LoadXml failed");
		throw SMRuntimeException(s);
	}
}

//----------------------------------------------------------------------------
// Returns the XML representation of the active node and all its descendants. Returns error if active node is not set.

HRESULT SMXmlDom::GetXml(SMString& sXml, const SMString& sNodeName, bool bLogErrors /* = false */)
{
	if ( NULL == activeNode )
		return S_FALSE;

    HRESULT hr = S_OK;

	SMSingleLock SingleLock(&m_Mutex, true);  // lock initially
    
	SM_TRY

	sXml.Empty();
    // First get a pointer to the specified node
	MSXML2::IXMLDOMNodePtr pNode = this->activeNode->selectSingleNode(sNodeName.Data());
    if ( NULL == pNode )
    {
		hr = E_INVALIDARG;
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::GetXml(): Failed to get node: " << sNodeName);
        }
        return hr;
    }

    // If we have a stylesheet to apply...
	if (this->xsl)
		sXml = static_cast<const wchar_t*>(pNode->transformNode(this->xsl));
	else
		sXml = static_cast<const wchar_t*>(pNode->xml);

	hr = !sXml.IsEmpty() ? S_OK : E_INVALIDARG;
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
			SM_LOG(hr, 1, "SMXmlDom::GetXml(): Failed to get xml string for node: " << sNodeName);
        }
        return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Return a human-readable representation of the XML tree

SMString SMXmlDom::TreeToString(const char* psPrefix /* = "" */, const SMString sNodeName)
{
    SMString sResult;

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    HRESULT hr = GetNode(sNodeName, pNode);
    if (SUCCEEDED(hr))
    {
        // Walk the tree, converting to string form
        WalkTree(pNode, 0, psPrefix, sResult);
    }
    else
    {
        SM_LOG(hr, 1, "SMXmlDom::TreeToString(): Failed to get node: " << sNodeName);
    }

    SM_CATCH_ALL_DEFAULT_NO_HR

    return sResult;
}


//----------------------------------------------------------------------------
// Walk all the Attributes in a loaded XML document, producing a text string
// representation of the tree.

void SMXmlDom::WalkTree(MSXML2::IXMLDOMNodePtr pNode, int nLevel, const char* psPrefix, SMString& sResult)
{
    SM_TRY

    const int INDENT_LEVEL = 3;
    const int MAX_SPRINTF = 65535;

    if (pNode != NULL)
    {
        BSTR bstrNodeName;
        pNode->get_nodeName(&bstrNodeName);
        SMString sNodeName(bstrNodeName);
        bool bSkipTag = false;

        // Don't bother with the '#document' or '#comment' tags
        if (!sNodeName.IsEmpty() && (sNodeName[0] == '#'))
            bSkipTag = true;

        if (!bSkipTag)
        {
            SMString sFormat;
            sFormat.sprintf("%s%*s%s:", psPrefix, nLevel * INDENT_LEVEL, "", sNodeName.Data());
			//@@ If the sprintf string length is greater than 64 k a stack overwrite will occur.
			// This is not a great way to pprotect against this, but I don't have a better idea at the moment.
			if (sResult.GetLength() < MAX_SPRINTF)
			{
				sResult += sFormat;
				++nLevel;
			}
        }
        ::SysFreeString(bstrNodeName);

        // Get the attributes (if any)
        MSXML2::IXMLDOMNamedNodeMapPtr pAttrs = NULL;
        MSXML2::IXMLDOMNodePtr         pChild = NULL;
        bool bFirst = true;
		pAttrs = pNode->attributes;
        if ( pAttrs != NULL )
        {
            pChild = pAttrs->nextNode();
            while (pChild != NULL)
            {
                CComBSTR bstrName;
                pChild->get_nodeName(&bstrName);
                SMString sNodeName(bstrName);
                VARIANT Value;
                pChild->get_nodeValue(&Value);
                if (Value.vt == VT_BSTR)
                {
                    CComBSTR bstrNodeValue = Value.bstrVal;
                    SMString sNodeValue(bstrNodeValue);
                    if (!bFirst)
						if (sResult.GetLength() < MAX_SPRINTF)
							sResult += ',';
                    else
                        bFirst = false;
                    SMString sFormat;
                    sFormat.sprintf(" %s=%s", sNodeName.Data(), sNodeValue.Data());
					if (sResult.GetLength() < MAX_SPRINTF)
						sResult += sFormat;
                }
                VariantClear(&Value);
                pChild = pAttrs->nextNode();
            }
        }

        if (!bSkipTag)
			if (sResult.GetLength() < MAX_SPRINTF)
				sResult += "\n";

        // Walk the tree for each child (if any)
        pNode->get_firstChild(&pChild);
        while (pChild != NULL)
        {
            CComBSTR bstrName;
            pChild->get_nodeName(&bstrName);
            SMString sNodeName(bstrName);
            WalkTree(pChild, nLevel, psPrefix, sResult);
            pChild = pChild->nextSibling;
        }
    }

    SM_CATCH_ALL_DEFAULT_NO_HR
}

//----------------------------------------------------------------------------
// Helper function: Create an IDOMNode of the given type.

MSXML2::IXMLDOMNodePtr SMXmlDom::CreateDOMNode(int nType, BSTR bstrName)
{
	if ( NULL == document )
		return S_FALSE;

    HRESULT hr = S_OK;

    MSXML2::IXMLDOMNodePtr pNode = NULL;
    VARIANT varType;

    varType.vt = VT_I4;
    V_I4(&varType) = (int)nType;

    SM_TRY

    pNode = this->document->createNode(varType, bstrName, "");
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::CreateDOMNode(): Failed to create node!");
        pNode = NULL;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return pNode;
}


//----------------------------------------------------------------------------

SMString SMXmlDom::GetString(const SMString& sAttributeName, bool bLogErrors /* = false */, const SMString& sDefault)
{
	if ( NULL == activeNode )
		return S_FALSE;

    SMString sValue;
    HRESULT hr = ReadStringAttribute(this->GetActiveNodeName(), sAttributeName, sValue, bLogErrors);
    if (bLogErrors && FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::GetString(): Error reading string value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }

	if ( FAILED(hr) || hr == S_FALSE )
		sValue = sDefault;

    return sValue;
}

//----------------------------------------------------------------------------

SMString SMXmlDom::GetElementString(bool bLogErrors, const SMString& sDefault)
{
    SMString sValue = this->GetText();
    if (bLogErrors && sValue.IsEmpty() )
    {
        SM_TRACE(1, "SMXmlDom::GetElementString(): Error reading string value! Node=" << this->GetActiveNodeName());
    }

	if ( sValue.IsEmpty() )
		sValue = sDefault;

    return sValue;
}

//----------------------------------------------------------------------------

int SMXmlDom::GetInteger(const SMString& sAttributeName, bool bLogErrors /* = false */, 
                               int nDefault /* = 0 */)
{
    SMString s = this->GetAttribute(sAttributeName);
    if ( bLogErrors && s.IsEmpty() )
    {
        SM_TRACE(1, "SMXmlDom::GetInteger(): Error reading integer value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
	return s.IsEmpty() ? nDefault : s.IntValue();
}

//----------------------------------------------------------------------------

DOUBLE SMXmlDom::GetDouble(const SMString& sAttributeName, bool bLogErrors /* = false */,
						DOUBLE nDefault /* = 0.0 */)
{
    SMString s = this->GetAttribute(sAttributeName);
    if ( bLogErrors && s.IsEmpty() )
    {
        SM_TRACE(1, "SMXmlDom::GetDouble(): Error reading double value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
	return s.IsEmpty() ? nDefault : s.DoubleValue();
}

//----------------------------------------------------------------------------

bool SMXmlDom::GetBoolean(const SMString& sAttributeName, bool bLogErrors /* = false */,
                               bool bDefault /* = false */)
{
	if ( NULL == activeNode )
		return false;

	int nValue = bDefault;
    HRESULT hr = ReadIntegerAttribute(this->GetActiveNodeName(), sAttributeName, nValue, bLogErrors);
    if (bLogErrors && FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::GetBoolean(): Error reading boolean value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
    return (nValue == 0) ? false : true;
}

//----------------------------------------------------------------------------

bool SMXmlDom::GetElementBoolean(bool bLogErrors /* = false */)
{
    bool result = false;

    SMString sValue = this->GetText();
    if (bLogErrors && sValue.IsEmpty() )
    {
        SM_TRACE(1, "SMXmlDom::GetElementBoolean(): Error reading string value! Node=" << this->GetActiveNodeName());
    }

	if ( !sValue.IsEmpty() )
		result = (sValue == "false") ? false : true;

	//if ( FAILED(hr) || hr == S_FALSE )
	//	sValue = sDefault;

    return result;
}

//----------------------------------------------------------------------------

int SMXmlDom::GetElementInteger(bool bLogErrors /* = false */)
{
    int result = 0;

    SMString sValue = this->GetText();
    if (bLogErrors && sValue.IsEmpty() )
    {
        SM_TRACE(1, "SMXmlDom::GetElementInteger(): Error reading string value! Node=" << this->GetActiveNodeName());
    }

	if ( !sValue.IsEmpty() )
		result = sValue.IntValue();

	//if ( FAILED(hr) || hr == S_FALSE )
	//	sValue = sDefault;

    return result;
}
//----------------------------------------------------------------------------
// Get an array of integers. On entry, nCount is the size of the int array
// pointed to by pnValues. On exit, nCount is the number of ints read.

void SMXmlDom::GetIntegerArray(const SMString& sAttributeName, int* pnValues, int& nCount, bool bLogErrors /* = false */)
{
    // Get the string
    SMString sValue = GetString(sAttributeName, bLogErrors);

    // Parse the string and populate the array
    int i = 0;
    for ( ; (i < nCount) && !sValue.IsEmpty(); i++)
    {
        SMString sToken = sValue.RemoveToken(" ");
        pnValues[i] = sToken.IntValue();
    }
    nCount = i;
}

//----------------------------------------------------------------------------
// Get an array of shorts. On entry, nCount is the size of the short array
// pointed to by pnValues. On exit, nCount is the number of shorts read.

void SMXmlDom::GetShortArray(const SMString& sAttributeName, short* pnValues, int& nCount, bool bLogErrors /* = false */)
{
    // Get the string
    SMString sValue = GetString(sAttributeName, bLogErrors);

    // Parse the string and populate the array
    int i = 0;
    for ( ; (i < nCount) && !sValue.IsEmpty(); i++)
    {
        SMString sToken = sValue.RemoveToken(" ");
        pnValues[i] = (short)sToken.IntValue();
    }
    nCount = i;
}

//----------------------------------------------------------------------------
// Get an array of float. On entry, nCount is the size of the float array
// pointed to by pnValues. On exit, nCount is the number of floats read.

void SMXmlDom::GetFloatArray(const SMString& sAttributeName, float* pnValues, int& nCount, bool bLogErrors /* = false */)
{
    // Get the string
    SMString sValue = GetString(sAttributeName, bLogErrors);

    // Parse the string and populate the array
    int i = 0;
    for ( ; (i < nCount) && !sValue.IsEmpty(); i++)
    {
        SMString sToken = sValue.RemoveToken(" ");
        pnValues[i] = (float)sToken.DoubleValue();
    }
    nCount = i;
}

//----------------------------------------------------------------------------

HRESULT SMXmlDom::SetString(const SMString& sAttributeName, const SMString& sValue)
{
	if ( NULL == activeNode )
		return S_FALSE;

    HRESULT hr = WriteStringAttribute(this->GetActiveNodeName(), sAttributeName, sValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::SetString(): Error writing string value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
    return hr;
}

//----------------------------------------------------------------------------

HRESULT SMXmlDom::SetInteger(const SMString& sAttributeName, int nValue)
{
	if ( NULL == activeNode )
		return S_FALSE;

    HRESULT hr = WriteIntegerAttribute(this->GetActiveNodeName(), sAttributeName, nValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::SetInteger(): Error writing integer value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
    return hr;
}

//----------------------------------------------------------------------------

HRESULT SMXmlDom::SetDouble(const SMString& sAttributeName, DOUBLE nValue)
{
	if ( NULL == activeNode )
		return S_FALSE;

    HRESULT hr = WriteDoubleAttribute(this->GetActiveNodeName(), sAttributeName, nValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::SetDouble(): Error writing integer value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
    return hr;
}

//----------------------------------------------------------------------------

HRESULT SMXmlDom::SetBoolean(const SMString& sAttributeName, bool bValue)
{
	if ( NULL == activeNode )
		return S_FALSE;

    HRESULT hr = WriteIntegerAttribute(this->GetActiveNodeName(), sAttributeName, (int)bValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::SetBoolean(): Error writing boolean value! Node=" << this->GetActiveNodeName() << ", Attribute=" << sAttributeName);
    }
    return hr;
}

//----------------------------------------------------------------------------
// Store an array of integers. nCount is the size of the int array pointed to
// by pnValues.

HRESULT SMXmlDom::SetIntegerArray(const SMString& sAttributeName, int* pnValues, int nCount)
{
    // Convert the integer array into a text string
    SMString sText;
    for (int i = 0; i < nCount; i++)
    {
        sText += pnValues[i];
        if (i < nCount - 1)
            sText += ' ';
    }

    // Set the string
    return SetString(sAttributeName, sText);
}

//----------------------------------------------------------------------------
// Store an array of shorts. nCount is the size of the short array pointed to
// by pnValues.

HRESULT SMXmlDom::SetShortArray(const SMString& sAttributeName, short* pnValues, int nCount)
{
    // Convert the integer array into a text string
    SMString sText;
    for (int i = 0; i < nCount; i++)
    {
        sText += pnValues[i];
        if (i < nCount - 1)
            sText += ' ';
    }

    // Set the string
    return SetString(sAttributeName, sText);
}

HRESULT SMXmlDom::SetFloatArray(const SMString& sAttributeName, float* pnValues, int nCount)
{
    // Convert the integer array into a text string
    SMString sText;
    for (int i = 0; i < nCount; i++)
    {
		SMString sFVal;
		sFVal.Format("%f",pnValues[i]);
		//@@ Is there no need for Seperator??
        sText +=  sFVal ;
        if (i < nCount - 1)
            sText += ' ';
    }

    // Set the string
    return SetString(sAttributeName, sText);
}


//----------------------------------------------------------------------------
// Read an integer field from the configuration.

HRESULT SMXmlDom::ReadIntegerAttribute(const SMString& sNodeName, 
                                      const SMString& sAttributeName, 
                                      int& nAttributeValue,
                                      bool bLogErrors /* = true */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadIntegerAttribute(): Failed to get node: " << sNodeName);
        }
        return hr;
    }

    // Get the element value
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadIntegerAttribute(): Failed to get element: " << sNodeName);
        }
        return hr;
    }

    // Get the attribute
	_variant_t varAttributeValue = pElement->getAttribute(sAttributeName.Data());
    // Load retrieved element value into input parameter
    if (varAttributeValue.vt != VT_NULL)
    {
        CComBSTR bstrIntValAsString;
        bstrIntValAsString = varAttributeValue.bstrVal;
        SMString sIntValAsString = bstrIntValAsString;
        nAttributeValue = sIntValAsString.IntValue();
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Read a DOUBLE field from the configuration.

HRESULT SMXmlDom::ReadDoubleAttribute (const SMString& sNodeName,
                                      const SMString& sAttributeName,
									  DOUBLE& nAttributeValue,
									  bool bLogErrors /* = true */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadDoubleAttribute(): Failed to get node: " << sNodeName);
        }
        return hr;
    }

    // Get the element value
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadDoubleAttribute(): Failed to get element: " << sNodeName);
        }
       return hr;
    }

    // Get the attribute
    VARIANT  varAttributeValue = pElement->getAttribute(sAttributeName.Data());
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadDoubleAttribute(): Failed to get attribute value: " << sAttributeName);
        }
        return hr;
    }

    // Load retrieved element value into input parameter
    if (varAttributeValue.vt != VT_NULL)
    {
        CComBSTR bstrDoubleValAsString;
        bstrDoubleValAsString = varAttributeValue.bstrVal;
        SMString sDoubleValAsString = bstrDoubleValAsString;
		nAttributeValue = sDoubleValAsString.DoubleValue();
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Read a string field from the configuration.

HRESULT SMXmlDom::ReadStringAttribute(const SMString& sNodeName, 
                                     const SMString& sAttributeName, 
                                     SMString& sAttributeValue,
                                     bool bLogErrors /* = true */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadStringAttribute(): Failed to get node: " << sNodeName);
        }
        return hr;
    }

    // Get the element value
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadStringAttribute(): Failed to get element: " << sNodeName);
        }
        return hr;
    }

    // Get the attribute
    VARIANT varAttributeValue = pElement->getAttribute(sAttributeName.Data());
    if (FAILED(hr))
    {
        if (bLogErrors)
        {
            SM_LOG(hr, 1, "SMXmlDom::ReadStringAttribute(): Failed to get attribute value: " << sAttributeName);
        }
        return hr;
    }

    // Load retrieved element value into input parameter
    if (varAttributeValue.vt != VT_NULL)
    {
        CComBSTR bstrAttributeValue;
        bstrAttributeValue = varAttributeValue.bstrVal;
        sAttributeValue = bstrAttributeValue;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Write an integer field to the configuration.

HRESULT SMXmlDom::WriteIntegerAttribute(const SMString& sNodeName, 
                                       const SMString& sAttributeName, 
                                       int  nAttributeValue)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteIntegerAttribute(): Failed to get node: " << sNodeName);
        return hr;
    }

    // Get the element object
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::WriteIntegerAttribute(): Failed to get element: " << sNodeName);
        return hr;
    }

    // Set the attribute
    VARIANT varAttributeValue;
    varAttributeValue.vt = VT_I4;
    V_I4(&varAttributeValue) = nAttributeValue;
    hr = pElement->setAttribute(sAttributeName.Data(), varAttributeValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteIntegerAttribute(): Failed to set attribute value: " << sAttributeName);
        return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Write a Double field to the configuration.

HRESULT SMXmlDom::WriteDoubleAttribute(const  SMString& sNodeName,
                                      const  SMString& sAttributeName,
									  DOUBLE nAttributeValue)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteDoubleAttribute(): Failed to get node: " << sNodeName);
        return hr;
    }

    // Get the element object
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::WriteDoubleAttribute(): Failed to get element: " << sNodeName);
        return hr;
    }

    // Set the attribute
    VARIANT varAttributeValue;
    varAttributeValue.vt = VT_R8;
    V_R8(&varAttributeValue) = nAttributeValue;
    hr = pElement->setAttribute(sAttributeName.Data(), varAttributeValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteDoubleAttribute(): Failed to set attribute value: " << sAttributeName);
        return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Write a string field to the configuration.

HRESULT SMXmlDom::WriteStringAttribute(const SMString& sNodeName, 
                                      const SMString& sAttributeName, 
                                      const SMString& sAttributeValue)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteStringAttribute(): Failed to get node: " << sNodeName);
        return hr;
    }

    // Get the element object
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::WriteStringAttribute(): Failed to get element: " << sNodeName);
        return hr;
    }

    // Set the attribute
    VARIANT varAttributeValue;
    CComBSTR bstrAttributeValue = sAttributeValue.Data();
    varAttributeValue.vt = VT_BSTR;
    V_BSTR(&varAttributeValue) = bstrAttributeValue;
    hr = pElement->setAttribute(sAttributeName.Data(), varAttributeValue);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteStringAttribute(): Failed to set element value: " << sAttributeName);
        return hr;
    }

	SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Write a text string (the text between the XML tags) to a node.

HRESULT SMXmlDom::WriteTextString(const SMString& sNodeName, 
                                 const SMString& sText)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the specified node
    MSXML2::IXMLDOMNodePtr pNode = NULL;
    hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteTextString(): Failed to get node: " << sNodeName);
        return hr;
    }

    // Get the element object
    MSXML2::IXMLDOMElementPtr pElement = pNode;
    if ( NULL == pElement )
    {
		hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::WriteTextString(): Failed to get element: " << sNodeName);
        return hr;
    }

    // Create a new text node and add it to the element
    MSXML2::IXMLDOMTextPtr pTextNode = this->document->createTextNode(sText.Data());
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteTextString(): Failed to create text node: " << sText);
        return hr;
    }
    MSXML2::IXMLDOMNodePtr pNewNode = NULL;
    pNewNode = pElement->appendChild(pTextNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::WriteTextString(): Failed to append text node: " << sText);
        return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Add a node to another node. Return pointer to the new node.

HRESULT SMXmlDom::AddNode(const SMString& sNodeName,
                         const SMString sParentNodeName /* = "Root" */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // Create the fully qualified node name
    SMString sFullNodeName;
    if (!sParentNodeName.IsEmpty() && (sParentNodeName.GetAt(0) != '/'))
        sFullNodeName = "//";
    sFullNodeName += sParentNodeName + ('/' + sNodeName);

    // First make sure the node doesn't exist already
    if (NodeExists(sFullNodeName))
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::AddNode(): Can't add " << sFullNodeName << " - already exists!");
        return hr;
    }

    // First get a pointer to the parent node
    MSXML2::IXMLDOMNodePtr pParentNode = NULL;
    MSXML2::IXMLDOMNodePtr pNewNode    = NULL;

    hr = GetNode(sParentNodeName, pParentNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::AddNode(): Failed to get parent node!");
        return hr;
    }

    // Now add the new node to the parent node
    CComBSTR bstrNodeName = sNodeName.Data();
    MSXML2::IXMLDOMNodePtr pNode = CreateDOMNode(MSXML2::NODE_ELEMENT, bstrNodeName);
    if (pNode == NULL)
    {
        hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::AddNode(): CreateDOMNode call failed for " << sNodeName);
        return hr;
    }

    // Insert the new node into the tree
    VARIANT after;
    after.vt = VT_EMPTY;
    pNewNode = pParentNode->insertBefore(pNode, after);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::AddNode(): InsertBefore method failed!");
         return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr; 
}
//----------------------------------------------------------------------------
// Delete a node from the list of nodes.

HRESULT SMXmlDom::DeleteNode(const SMString& sNodeName,
                            const SMString sParentNodeName /* = "Root" */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the parent node
    MSXML2::IXMLDOMNodePtr pParentNode = NULL;
    hr = GetNode(sParentNodeName, pParentNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::DeleteNode(): Failed to get parent node!");
        return hr;
    }

    // Get a pointer to the node to be deleted
    MSXML2::IXMLDOMNodePtr pNode = NULL;
	hr = GetNode(sNodeName, pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::DeleteNode(): Failed to get node to be deleted: " << sNodeName);
        return hr;
    }

    // Delete node
    pParentNode->removeChild(pNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::DeleteNode(): removeChild method failed!");
        return hr;
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Get a node from the configuration.

HRESULT SMXmlDom::GetNode(const SMString& sNodeName, MSXML2::IXMLDOMNodePtr& ppNode)
{
    HRESULT hr = S_OK;

    SM_TRY

    ppNode = NULL;

    // Ignore '#comment' tags
    if (sNodeName.Contains('#'))
    {
        hr = E_FAIL;
    }
    else
    {
        // Prefix "//" to find anywhere in the document (only if it's not already there).
        SMString sNodeSearchString;
        if (!sNodeName.IsEmpty() && (sNodeName.GetAt(0) != '/'))
            sNodeSearchString = "//";
        if (!sNodeName.IsEmpty())
        {
            sNodeSearchString += sNodeName;
            ppNode = this->document->selectSingleNode(sNodeSearchString.Data());
            if (hr != S_OK)
            {
                if (hr != S_FALSE)
                {
                 SM_LOG(hr, 1, "SMXmlDom::GetNode(): Failed to get node for " << sNodeSearchString);
                }
                hr = E_FAIL;
            }
            else if (ppNode == NULL)
            {
                SM_LOG(hr, 1, "SMXmlDom::GetNode(): Failed to get node for " << sNodeSearchString);
                hr = E_FAIL;
            }
        }
        else
        {
            //@@ Need to look into why this occurs???
            SM_LOG(hr, 1, "SMXmlDom::GetNode(): Failed to get node, empty search string.");
            hr = E_FAIL;
        }
    }

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

//----------------------------------------------------------------------------
// Get the list of nodes with a given parent.

HRESULT SMXmlDom::GetChildNodeList(vector<SMString>& vecNodeList,
                                  const SMString sParentNode /* = "Root" */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY
		MSXML2::IXMLDOMNodePtr pParentNode = sParentNode.IsEmpty() ? this->activeNode : this->activeNode->selectSingleNode(sParentNode.Data());
    // First get a pointer to the parent node
    if ( NULL == pParentNode )
    {
		hr = E_FAIL;
        SM_LOG(hr, 1, "SMXmlDom::GetChildNodeList(): Failed to get parent node!");
        return hr;
    }

	vecNodeList.clear();
	for ( long i = 0; i < pParentNode->childNodes->length; ++i )
	{
		if ( NODE_ELEMENT == pParentNode->childNodes->item[i]->nodeType )
		{
			vecNodeList.push_back(SMString(static_cast<const char*>(pParentNode->childNodes->item[i]->nodeName)));
		}
	}
    
    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}

HRESULT SMXmlDom::FindNodes(SMString expression, MSXML2::IXMLDOMNodeListPtr &resultList, const SMString sParentNode /* = "Root" */)
{
    HRESULT hr = S_OK;

    SMSingleLock SingleLock(&m_Mutex, true);  // lock initially

    SM_TRY

    // First get a pointer to the parent node
    MSXML2::IXMLDOMNodePtr pParentNode = NULL;
    hr = GetNode(sParentNode, pParentNode);
    if (FAILED(hr))
    {
        SM_LOG(hr, 1, "SMXmlDom::FindNodes(): Failed to get parent node!");
        return hr;
    }

    // Find all the children 
	resultList = pParentNode->selectNodes(expression.Data());
	if (FAILED(hr))
	{
	    SM_LOG(hr, 1, "SMXmlDom::FindNodes(): Failed to get child node list!");
        return hr;
	}

    SM_CATCH_ALL_DEFAULT(hr)

    return hr;
}
//----------------------------------------------------------------------------
void SMXmlDom::DeleteAllChildren()
{
	if ( NULL == activeNode )
		return;

	SMSingleLock SingleLock(&m_Mutex, true);
	while ( 0 < this->activeNode->childNodes->length )
	{
		if ( NULL == this->activeNode->removeChild(this->activeNode->childNodes->item[0]) )
		{
			throw SMRuntimeException("SMXmlDom::DeleteAllChildren failed");
		}
	}
}
//----------------------------------------------------------------------------
void SMXmlDom::CreatePath(const SMString & path, bool setActive)
{
	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr current = this->activeNode;
	for ( SMString currPath = path; !currPath.IsEmpty(); )
	{
		SMString s = SplitPathFront(currPath);
		if ( SMString(pathDelim) == s )
		{
			current = this->document;
		}
		else
		{
			bool found = false;
			for ( long i = 0; i < current->childNodes->length; ++i )
			{
				if ( NODE_ELEMENT != current->childNodes->item[i]->nodeType ) continue;
				if ( s == static_cast<const wchar_t*>(current->childNodes->item[i]->nodeName) )
				{
					current = current->childNodes->item[i];
					found = true;
					break;
				}
			}
			if ( !found )
			{
				MSXML2::IXMLDOMElementPtr e = this->document->createElement(s.Data());
				if ( NULL == e )
				{
					SM_TRACE(1, "SMXmlDom::CreateElements failed to create element \"" << s << "\" in \"" << path << "\"");
					throw SMRuntimeException("SMXmlDom::CreateElements failed");
				}
				current = current->appendChild(e);
				if ( NULL == current ) 
				{
					SM_TRACE(1, "SMXmlDom::CreateElements failed to append element \"" << s << "\" in \"" << path << "\"");
					throw SMRuntimeException("SMXmlDom::CreateElements failed");
				}

			}
		}
	}
	if ( setActive )
	{
		this->activeNode = current;
	}
}

//----------------------------------------------------------------------------
SMString SMXmlDom::SplitPathFront(SMString & path)
{
	SMString res;
	int pos = path.Find(pathDelim);
	if ( -1 == pos ) {
		res = path;
		path.Empty();
	} else {
		res = path.Left(0==pos ? pos+1 : pos);
		path = path.Mid(pos+1);
	}
	return res;
}

//----------------------------------------------------------------------------
void SMXmlDom::AppendElement(const SMString & name, bool setActive)
{
	if ( NULL == activeNode )
		return;

	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMElementPtr e = this->document->createElement(name.Data());
	if ( NULL == e )
	{
		SM_TRACE(1, "SMXmlDom::AppendElement failed to create element \"" << name << "\"");
		throw SMRuntimeException("SMXmlDom::AppendElement failed");
	}
	e = this->activeNode->appendChild(e);
	if ( NULL == e ) 
	{
		SM_TRACE(1, "SMXmlDom::AppendElement failed to append element \"" << name << "\"");
		throw SMRuntimeException("SMXmlDom::AppendElement failed");
	}
	if ( setActive )
	{
		this->activeNode = e;
	}
}
//----------------------------------------------------------------------------
bool SMXmlDom::NodeExists(const SMString & xpath) const
{
	SMSingleLock SingleLock(&m_Mutex, true);
	return NULL != this->activeNode && 
		NULL != this->activeNode->selectSingleNode(xpath.Data());
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetActiveNodeName() const
{
	if ( NULL == activeNode )
		return SMString("");

	SMSingleLock SingleLock(&m_Mutex, true);
	return static_cast<const wchar_t*>(this->activeNode->nodeName);
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetActiveNodePath() const
{
	if ( NULL == this->activeNode )
		return SMString("");

	SMSingleLock SingleLock(&m_Mutex, true);
	return GetNodePath(this->activeNode);
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetNodePath(const MSXML2::IXMLDOMNodePtr & node)
{
	if ( NULL == node )
		return SMString("");

	if ( NODE_DOCUMENT == node->nodeType ) 
		return pathDelim;
	SMString res;
	SMString name = static_cast<const wchar_t*>(node->nodeName);
	if ( !name.IsEmpty() && NULL != node->parentNode && NODE_DOCUMENT != node->parentNode->nodeType )
	{
		res = GetNodePath(node->parentNode);
	}
	res += pathDelim + name;
	return res;
}
//----------------------------------------------------------------------------
void SMXmlDom::MoveActiveUp()
{
	if ( NULL != this->activeNode && NULL != this->activeNode->parentNode )
	{
		this->activeNode = this->activeNode->parentNode;
	}
}
//----------------------------------------------------------------------------
void SMXmlDom::LoadFile(const SMString & fileName)
{
	SMSingleLock SingleLock(&m_Mutex, true);
	if ( VARIANT_TRUE != this->document->load(fileName.Data()) )
	{
		SM_TRACE(1, "SMXmlDom::LoadFile failed to load file \"" << fileName << "\"");
		throw SMRuntimeException("SMXmlDom::LoadFile failed");
	}
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetXmlString() const
{
	if ( NULL == this->activeNode )
		return SMString("");

	SMSingleLock SingleLock(&m_Mutex, true);

	_bstr_t bstr(L"");

    // If we have a stylesheet to apply...
	if (this->xsl)
		bstr = this->activeNode->transformNode(this->xsl);
	else
		bstr = this->activeNode->xml;

	const wchar_t* wide = (const wchar_t*)bstr;
	return SMString(wide);
}
//----------------------------------------------------------------------------
void SMXmlDom::SelectActiveNode(const SMString & xpath)
{
	if ( NULL == this->activeNode )
		return;

	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr p = this->activeNode->selectSingleNode(xpath.Data());
	if ( NULL != p )
	{
		this->activeNode = p;
	}
	else
	{
		SM_TRACE(1, "SMXmlDom::SetActiveNode failed to find node \"" << xpath << "\"");
		throw SMRuntimeException("SMXmlDom::SetActiveNode failed");
	}
}
//----------------------------------------------------------------------------
void SMXmlDom::SaveFile(const SMString & fileName) const
{
	SMSingleLock SingleLock(&m_Mutex, true);
	if (this->xsl)
	{
		SMString sXml = static_cast<const wchar_t*>(this->document->transformNode(this->xsl));
		std::ofstream ofstr(fileName.Data());
		if ( !ofstr.is_open() )
		{
			SM_TRACE(1, "SMXmlDom::SaveFile failed to save into file \"" << fileName << "\"");
			throw SMRuntimeException("SMXmlDom::SaveFile failed");
		}
		ofstr << sXml;
	}
	else
	{
		HRESULT hr = this->document->save(fileName.Data());
		if ( FAILED(hr) )
		{
			SM_TRACE(1, "SMXmlDom::SaveFile failed to save into file \"" << fileName << "\"");
			throw SMRuntimeException("SMXmlDom::SaveFile failed");
		}
	}
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetText(const SMString & xpath) const
{
	if ( NULL == activeNode )
		return SMString("");

	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr p = xpath.IsEmpty() ? this->activeNode : this->activeNode->selectSingleNode(xpath.Data());
	if ( NULL == p )
	{
		return "";
	}
	for ( long i = 0; i < p->childNodes->length; ++i )
	{
		if ( NODE_TEXT != p->childNodes->item[i]->nodeType ) continue;
		SMString s = static_cast<const wchar_t*>(static_cast<_bstr_t>(p->childNodes->item[i]->nodeValue));
		s.TrimLeft("\n\r\t ");
		s.TrimRight("\n\r\t ");
		if ( !s.IsEmpty() ) return s;
	}
	return "";
}
//----------------------------------------------------------------------------
void SMXmlDom::SetText(const SMString & text, const SMString & xpath)
{
	if ( NULL == this->activeNode )
		return;

	// Presumably, all of our internal "keys" in xpath are ANSI.
	// Only the data needs to be widened so that later retrieval of text
	// is in UTF8.

	// Don't let MSXML implicitly convert text into a wide string using an 
	// incorrect codepage.

	wstring wtext = NarrowToWide(text.Data(), CP_UTF8, true);

	// If the text actually has something, then make sure the widened version does too.
	if ( text.Size() && wtext.empty() )
	{
		SM_TRACE(2, "SMXmlDom::SetText 1st pass failed to convert narrow to wide string using UTF8.\"" << text << "\"");

		// Try another codepage, maybe this one came from an OS narrowed string.
		// Excerpt from http://support.microsoft.com/kb/108450:
		// MultiByteToWideChar() Codepages CP_ACP/CP_OEMCP ......
		// CP_ACP instructs the API to use the currently set default Windows ANSI codepage.
		// CP_OEMCP instructs the API to use the currently set default OEM codepage. 
		//
		// If Win32 ANSI APIs are used to get filenames from a Windows NT system, use CP_ACP when converting the string.
		// Windows NT retrieves the name from the physical device and translates the OEM name into Unicode.
		// The Unicode name is translated into ANSI if an ANSI API is called, then it can be translated back into Unicode with MultiByteToWideChar(). 
		//
		//If filenames are being retrieved from a file that is OEM encoded, use CP_OEMCP instead.

		wtext = NarrowToWide(text.Data(), CP_ACP, true);
		if ( wtext.empty() ) {
			SM_TRACE(1, "SMXmlDom::SetText 2nd pass failed to convert narrow to wide string using UTF8 and CP_ACP.\"" << text << "\"");
			return;
		} else {
			SM_TRACE(2, "SMXmlDom::SetText succeeded 2nd pass using CP_ACP.");
		}

		// The following operation is not needed as Conversion to Unicode has succeeded.
		//// Now the string is wide, but an ANSI codepage.
		//// Try to convert the ANSI codepage to UTF8...
		//// If this fails, it has been shown to be nonfatal and MSXML is cool with wide CP_ACP strings.
		//string narrow = WideToNarrow( wtext.c_str(), CP_UTF8, true );
		//if ( narrow.empty() ) 
		//{
		//	SM_TRACE(1, "SMXmlDom::SetText failed 3rd pass convert wide to narrow string using CP_UTF8.\"" << text << "\"");
		//} 
		//else 
		//{
		//	SM_TRACE(2, "SMXmlDom::SetText succeeded 3rd pass using CP_UTF8.");
		//	wstring wtext2 = NarrowToWide(narrow.c_str(), CP_UTF8, true);
		//	if ( wtext2.empty() )
		//	{
		//		SM_TRACE(1, "SMXmlDom::SetText failed 4th pass to convert narrow to wide string using CP_UTF8.\"" << text << "\"");
		//	} 
		//	else
		//	{
		//		SM_TRACE(2, "SMXmlDom::SetText succeeded 4th pass using CP_UTF8.");
		//		wtext = wtext2;
		//	}
		//}
	}

	SMString wxpath(xpath);
	_bstr_t btext(wtext.data()), bxpath(wxpath.DataW());
	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr p = xpath.IsEmpty() ? this->activeNode : this->activeNode->selectSingleNode(bxpath);
	if ( NULL == p )
	{
		SM_TRACE(1, "SMXmlDom::SetText failed to find node \"" << xpath << "\"");
		throw SMRuntimeException("SMXmlDom::SetText failed");
	}
	MSXML2::IXMLDOMTextPtr txt = this->document->createTextNode(btext);
	if ( NULL == txt )
	{
		SM_TRACE(1, "SMXmlDom::SetText failed to create text node");
		throw SMRuntimeException("SMXmlDom::SetText failed");
	}
	if ( NULL == p->appendChild(txt) ) 
	{
		SM_TRACE(1, "SMXmlDom::SetText failed to append text node");
		throw SMRuntimeException("SMXmlDom::SetText failed");
	}
}
//----------------------------------------------------------------------------
void SMXmlDom::PushActiveNode()
{
	SMSingleLock SingleLock(&m_Mutex, true);
	this->pushStack.push(this->GetActiveNodePath());
}
//----------------------------------------------------------------------------
void SMXmlDom::PopActiveNode()
{
	SMSingleLock SingleLock(&m_Mutex, true);
	if ( !this->pushStack.empty() )
	{
		SMString s = this->pushStack.top();
		this->pushStack.pop();
		this->SelectActiveNode(s);
	}
}
//----------------------------------------------------------------------------
SMString SMXmlDom::GetAttribute(const SMString & attr, const SMString & xpath) const
{
	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr p = xpath.IsEmpty() ? this->activeNode : this->activeNode->selectSingleNode(xpath.Data());
	//MSXML2::DOMNodeType t = p->nodeType;
	if ( NULL == p || NODE_ELEMENT != p->nodeType )
	{
		return "";
	}
	MSXML2::IXMLDOMElementPtr e = p;
	if ( NULL == e ) throw SMRuntimeException("SMXmlDom::GetAttribute failed.");
	p = e->attributes->getNamedItem(attr.Data());
	if ( NULL == p )
	{
		return "";
	}
	else
	{
		return static_cast<const wchar_t*>(static_cast<_bstr_t>(p->nodeValue));
	}
}
//----------------------------------------------------------------------------
void SMXmlDom::SetAttribute(const SMString & attr, const SMString & val, const SMString & xpath)
{
	SMSingleLock SingleLock(&m_Mutex, true);
	MSXML2::IXMLDOMNodePtr p = xpath.IsEmpty() ? this->activeNode : this->activeNode->selectSingleNode(xpath.Data());
	if ( NULL == p )
	{
		SM_TRACE(1, "SMXmlDom::SetAttribute failed to find node \"" << xpath << "\"");
		throw SMRuntimeException("SMXmlDom::SetAttribute failed");
	}
	MSXML2::IXMLDOMElementPtr e = p;
	
	if ( NULL == e ) throw SMRuntimeException("SMXmlDom::SetAttribute failed.");
	MSXML2::IXMLDOMAttributePtr a = this->document->createAttribute(attr.Data());
	if ( NULL == a )
	{
		SM_TRACE(1, "SMXmlDom::SetAttribute failed to create attribute node");
		throw SMRuntimeException("SMXmlDom::SetAttribute failed");
	}
	SMString sVal = val;
	a->value = sVal.DataW();
	a = e->setAttributeNode(a);
}
//----------------------------------------------------------------------------
// EOF
