//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMXmlDom.h $
//  Package : SMUtilities
//
//  Copyright © 2007-2008 Smith Micro Software, Inc., All Rights Reserved.
//
//  This software is the intellectual property of Smith Micro Software, Inc.
//  It is protected by state law, copyright law, and/or international
//  treaties. Neither receipt nor possession of this software (in any
//  form) confers any right to reproduce, use, or disclose it, in whole
//  or in part, without written authorization from Smith Micro Software, Inc.
//
//  $Author: Tfiner $
//  $Date: 6/09/08 2:20p $
//  $Modtime: 6/09/08 1:45p $
//  $Revision: 32 $
//
//  TODO: Add description here.
//
//----------------------------------------------------------------------------
#pragma once

#ifndef VersionControlHistory
// $History: SMXmlDom.h $
// 
// *****************  Version 32  *****************
// User: Tfiner       Date: 6/09/08    Time: 2:20p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Fixes for bugs: 1237 and 1520.
// 1. Explicitly convert narrow to wide using UTF8 codepage.
// 2. Use wide char functions.
// 
// *****************  Version 31  *****************
// User: Zsukhanov    Date: 4/03/08    Time: 4:39a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Remove deprecated methods
// 
// *****************  Version 30  *****************
// User: Cchang       Date: 3/31/08    Time: 11:22a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// put back Arodriguez's version since GetString has problem...
// 
// *****************  Version 28  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 27  *****************
// User: Vtokarev     Date: 18.01.08   Time: 9:42
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 26  *****************
// User: Vtokarev     Date: 15.01.08   Time: 12:19
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 25  *****************
// User: Vtokarev     Date: 14.01.08   Time: 16:54
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 24  *****************
// User: Vtokarev     Date: 14.01.08   Time: 15:18
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 23  *****************
// User: Vtokarev     Date: 14.01.08   Time: 13:34
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 22  *****************
// User: Vtokarev     Date: 13.12.07   Time: 10:08
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 21  *****************
// User: Vtokarev     Date: 10.12.07   Time: 10:24
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 20  *****************
// User: Ozhuk        Date: 12/03/07   Time: 4:26p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 19  *****************
// User: Ozhuk        Date: 12/03/07   Time: 3:56p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 18  *****************
// User: Ozhuk        Date: 12/03/07   Time: 3:26p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// LocationTechnologyProfile added.
// 
// *****************  Version 17  *****************
// User: Admin        Date: 11/27/07   Time: 3:18p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// AccessPoint class added.
// 
// *****************  Version 16  *****************
// User: Sanderson    Date: 11/16/07   Time: 3:03p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Embedded 'ReadableXML' XSL into code
// 
// *****************  Version 15  *****************
// User: Sanderson    Date: 11/15/07   Time: 7:03p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Restored XML formatting for debug
// 
// *****************  Version 14  *****************
// User: Admin        Date: 11/12/07   Time: 10:32a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// WriteTextString overload to use pNode was added.
// 
// *****************  Version 13  *****************
// User: Admin        Date: 11/09/07   Time: 10:34a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Added AppendChild method, which can be used to add several nodes with
// the same name to the same parent node.
// 
// *****************  Version 12  *****************
// User: Admin        Date: 11/01/07   Time: 6:53a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 11  *****************
// User: Admin        Date: 10/30/07   Time: 11:33a
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// New Serialization format.
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
// User: Jwu          Date: 9/13/07    Time: 4:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Modified comments for the declaration of method GetXmlForActiveNode
// 
// *****************  Version 5  *****************
// User: Jwu          Date: 9/13/07    Time: 3:27p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// 
// *****************  Version 4  *****************
// User: Jwu          Date: 9/12/07    Time: 2:09p
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

#include <stack>
#include "SMUtilitiesLink.h"
#include "SMString.h"
#include "SMMutex.h"


// For XML ActiveX control access
#import "msxml6.dll" named_guids

class SMUTILITIES_API SMXmlDom
{
public:
	SMXmlDom(bool bReadableFormat = false);
	virtual ~SMXmlDom();
	void CreatePath(const SMString & path, bool setActive = true);
	void AppendElement(const SMString & name, bool setActive = true);
	SMString GetActiveNodeName() const;
	SMString GetActiveNodePath() const;
    bool NodeExists(const SMString & xpath) const;
	void DeleteAllChildren();
	void LoadXml(const SMString& sXml);
	void LoadFile(const SMString & fileName);
	void MoveActiveUp();
	void SelectActiveNode(const SMString & xpath);
	SMString GetXmlString() const;
	void SaveFile(const SMString & fileName) const;
	SMString GetText(const SMString & xpath = "") const;
	void SetText(const SMString & text, const SMString & xpath = "");
	void PushActiveNode();
	void PopActiveNode();
	SMString GetAttribute(const SMString & attr, const SMString & xpath = "") const;
	void SetAttribute(const SMString & attr, const SMString & val, const SMString & xpath = "");
	
private:
	static SMString SplitPathFront(SMString & path);
	static SMString GetNodePath(const MSXML2::IXMLDOMNodePtr & node);
	SMString GetLastParserError();
	
private: // data
	MSXML2::IXMLDOMDocumentPtr document;
	MSXML2::IXMLDOMNodePtr activeNode;
	static const char pathDelim = '/';
	std::stack<SMString> pushStack;
	mutable SMMutex  m_Mutex;

public:
    // The following helper functions are "relative" - they work for the
    // currently active node, so that it doesn't have to be passed in to every
    // method.
    
	SMString GetElementString (bool bLogErrors = false, const SMString& sDefault = SMString(""));
	bool     GetElementBoolean(bool bLogErrors = false);
	int		 GetElementInteger(bool bLogErrors = false);
    SMString GetString        (const SMString& sAttributeName, bool bLogErrors = false, const SMString& sDefault = SMString(""));
    int      GetInteger       (const SMString& sAttributeName, bool bLogErrors = false, int nDefault = 0);
    DOUBLE   GetDouble        (const SMString& sAttributeName, bool bLogErrors = false, DOUBLE nDefault = 0.0);
    bool     GetBoolean       (const SMString& sAttributeName, bool bLogErrors = false, bool bDefault = false);
    void     GetIntegerArray  (const SMString& sAttributeName, int* pnValues, int& nCount, bool bLogErrors = false);
    void     GetShortArray    (const SMString& sAttributeName, short* pnValues, int& nCount, bool bLogErrors = false);
    void     GetFloatArray    (const SMString& sAttributeName, float* pnValues, int& nCount, bool bLogErrors = false);

    HRESULT   SetString        (const SMString& sAttributeName, const SMString& sValue);
	//Add attribute to the specified node;
    HRESULT   SetInteger       (const SMString& sAttributeName, int nValue);
    HRESULT   SetDouble        (const SMString& sAttributeName, DOUBLE nValue);
    HRESULT   SetBoolean       (const SMString& sAttributeName, bool bValue);
    HRESULT   SetIntegerArray  (const SMString& sAttributeName, int* pnValues, int nCount);
    HRESULT   SetShortArray    (const SMString& sAttributeName, short* pnValues, int nCount);
    HRESULT   SetFloatArray    (const SMString& sAttributeName, float* pnValues, int nCount);

	HRESULT   GetChildren    (vector<SMString>& vecNodeList)
	{ 
		return GetChildNodeList(vecNodeList, this->GetActiveNodeName()); 
	};

    HRESULT ReadIntegerAttribute (const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  int& nAttributeValue,
                                  bool bLogErrors = true);
    HRESULT ReadDoubleAttribute	 (const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  DOUBLE& nAttributeValue,
                                  bool bLogErrors = true);
    HRESULT ReadStringAttribute  (const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  SMString& sAttributeValue,
                                  bool bLogErrors = true);
   HRESULT WriteIntegerAttribute(const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  int  nAttributeValue);
    HRESULT WriteDoubleAttribute  (const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  DOUBLE nAttributeValue);
    HRESULT WriteStringAttribute (const SMString& sNodeName,
                                  const SMString& sAttributeName,
                                  const SMString& sAttributeValue);
    HRESULT WriteTextString      (const SMString& sNodeName, 
                                  const SMString& sText);
    HRESULT AddNode(const SMString& sNodeName, const SMString sParentNodeName = "Root");
	HRESULT DeleteNode(const SMString& sNodeName, const SMString sParentNodeName = "Root");
	HRESULT GetChildNodeList(std::vector<SMString>& vecNodeList, const SMString sParentNode = "");
	HRESULT FindNodes(SMString expression, MSXML2::IXMLDOMNodeListPtr & resultList, const SMString sParentNode = "Root");
	
	// Get the XML representation for the given node and all its descendants.
    HRESULT GetXml(SMString& sXml, const SMString& sNodeName, bool bLogErrors = false);

    // Return a human-readable representation of the XML tree
    SMString TreeToString(const char* psPrefix = "", const SMString sNodeName = "Root");
	

private:
    HRESULT CreateNew();
    HRESULT GetNode(const SMString& sNodeName, MSXML2::IXMLDOMNodePtr& ppNode);
    void    WalkTree(MSXML2::IXMLDOMNodePtr pNode, int nLevel, const char* psPrefix, SMString& sResult);
    MSXML2::IXMLDOMNodePtr CreateDOMNode(int nType, BSTR bstrName);
	

	MSXML2::IXMLDOMDocumentPtr xsl;
	
    // Disable compiler generation of copy constructor & assignment operator.
    SMXmlDom           (const SMXmlDom&);
    SMXmlDom& operator=(const SMXmlDom&);

};

//----------------------------------------------------------------------------
