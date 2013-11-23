//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMXmlFormatter.h $
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
//  $Author: Arodriguez $
//  $Date: 2/15/08 3:08p $
//  $Modtime: 2/15/08 2:50p $
//  $Revision: 8 $
//
//  This class generates properly formatted XML strings.  Defining the XML
//  requires clients to set an active node, then define nodes, attributes, and 
//  elements below it.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMXmlFormatter.h $
// 
// *****************  Version 8  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 6  *****************
// User: Jheuerman    Date: 5/29/07    Time: 10:37a
// Updated in $/Mobile/SMUtilities
// Fixed newline bug.  If an element contained an empty string "" the
// output would insert a newline between the opening and closing tag.
// This has been fixed.  The code now exports empty elements using the
// proper <foo/> syntax.
// 
// *****************  Version 5  *****************
// User: Jheuerman    Date: 4/25/07    Time: 11:47a
// Updated in $/Mobile/SMUtilities
// 
// *****************  Version 4  *****************
// User: Jheuerman    Date: 4/24/07    Time: 4:17p
// Updated in $/Mobile/SMUtilities
// 
// *****************  Version 3  *****************
// User: Jheuerman    Date: 4/24/07    Time: 3:51p
// Updated in $/Mobile/SMUtilities
// 
// *****************  Version 2  *****************
// User: Arodriguez   Date: 4/20/07    Time: 6:33p
// Updated in $/Mobile/SMUtilities
// Added automatic linking and exported the SMXmlFormatter class.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 4/20/07    Time: 6:23p
// Created in $/Mobile/SMUtilities
// Added stub for SMXmlFormatter.
//#endregion

#pragma once

// --------
// Includes
// --------

#include <vector>
#include "SMUtilitiesLink.h"
#include "SMString.h"

//---------------------
// Forward declarations
//---------------------

class SMMutex;
class SMXmlFormatterNode;
class SMXmlFormatterLeaf;

//---------
// Typedefs
//---------

typedef std::vector<SMString*> stringVector;
typedef std::vector<SMXmlFormatterNode*> nodeVector;

//--------------------------------
// SMXmlFormmatter class interface
//--------------------------------

class SMUTILITIES_API SMXmlFormatter
{
public:
	// ------------
	// Construction
	// ------------
    SMXmlFormatter(const SMString& sRootNode, bool bMultithreaded = false);

	// -----------
	// Destruction
	// -----------
	~SMXmlFormatter();

	// --------------
    // Public helpers
	// --------------
    void LogErrors(bool bLogErrors = true)
    { m_bLogErrors = bLogErrors; }

public:
	// ---------------
	// Node navigation
	// ---------------
    HRESULT SetActiveNode(const SMString& sPathAndNode);
	HRESULT CreateActiveNode(const SMString& sPathAndNode);

	SMString GetActiveNode();
    //bool NodeExists(const SMString& sPathAndNode);
    
	// ----------------
	// Element creation
	// ----------------
    HRESULT AddElementString      (const SMString& sElementName, const SMString& sValue);
    HRESULT AddElementInteger     (const SMString& sElementName, int nValue);
    HRESULT AddElementDouble      (const SMString& sElementName, double nValue);
    HRESULT AddElementBoolean     (const SMString& sElementName, bool bValue);
    HRESULT AddElementIntegerArray(const SMString& sElementName, int* pnValues, int nCount);
    HRESULT AddElementFloatArray  (const SMString& sElementName, float* pnValues, int nCount);

	// ------------------
	// Attribute creation
	// ------------------
    HRESULT AddAttributeString    (const SMString& sAttributeName, const SMString& sValue);
    HRESULT AddAttributeInteger   (const SMString& sAttributeName, int nValue);
    HRESULT AddAttributeDouble    (const SMString& sAttributeName, double nValue);
    HRESULT AddAttributeBoolean   (const SMString& sAttributeName, bool bValue);

	// ----------
	// XML output
	// ----------
    SMString Format();
    
public:
	// For future development (XML Parsing)
    //SMString GetElementString      (const SMString& sElementName, bool bLogErrors = false, const SMString& sDefault = SMString(""));
    //int      GetElementInteger     (const SMString& sElementName, bool bLogErrors = false, int nDefault = 0);
    //double   GetElementDouble      (const SMString& sElementName, bool bLogErrors = false, double fDefault = 0.0);
    //bool     GetElementBoolean     (const SMString& sElementName, bool bLogErrors = false, bool bDefault = false);
    //void     GetElementIntegerArray(const SMString& sElementName, int* pnValues, int& nCount, bool bLogErrors = false, int nDefault = 0);
    //void     GetElementShortArray  (const SMString& sElementName, short* pnValues, int& nCount, bool bLogErrors = false, short nDefault = 0);
    //void     GetElementFloatArray  (const SMString& sElementName, float* pnValues, int& nCount, bool bLogErrors = false, double fDefault = 0.0);

    //vector<SMString> GetChildren();

	//void Parse(const SMString& sXmlData);

private:
	// ---------------
	// Private helpers
	// ---------------
    bool navigateToNode                (const SMString& sPathAndNode);
    SMXmlFormatterNode *navigateToChild(const SMString& sChildName, bool forceCreate = false);
    int addElementAndValue             (const SMString& sElementName, const SMString& sValue);

	// ---------------------------------------------------------------------
    // Disable compiler generation of copy constructor & assignment operator
	// ---------------------------------------------------------------------
    SMXmlFormatter(const SMXmlFormatter&);
    SMXmlFormatter& operator=(const SMXmlFormatter&);

private:
    SMXmlFormatterNode* m_root;			// Our root node
    SMXmlFormatterNode* m_activeNode;	// Our active node
    SMXmlFormatterNode* m_lastNodeAccessed; // The last node we've accessed (will either be the active node or one of its immediate children)
    
	bool                m_bLogErrors;	// Should we log runtime errors to SM_LOG?
    SMMutex*            m_pMutex;		// Should we protect against concurrency?
};

//--------------------------
// SMXmlFormmatterNode class
//--------------------------

class SMXmlFormatterNode {

private:
	// ------------
	// Construction
	// ------------
	SMXmlFormatterNode(const SMString& sNodeName, SMXmlFormatterNode *pParentNode = NULL);
	SMXmlFormatterNode(const SMString& sElementName, const SMString& sValue, SMXmlFormatterNode *pParentNode = NULL);

public:
	// -----------
	// Destruction
	// -----------
	~SMXmlFormatterNode();

	// ------------------
	// Accessor functions
	// ------------------

	// Get this element's name
	const SMString &getName()
	{ return name; }

	// Get this element's parent node
	SMXmlFormatterNode *getParent()
	{ return parent; }

	// If this element contains a value rather than child nodes, then it's a leaf
	bool isLeaf;

	// -------
	// Runtime
	// -------

	// Used only once... to create the root node for our XML tree
	static SMXmlFormatterNode *createRootNode(const SMString& sRootName);

	// Returns a child element by name
	SMXmlFormatterNode *findChild(const SMString& sChildName, bool forceCreate = false);

	// Adds a new child element
	SMXmlFormatterNode *addElementAndValue(const SMString& sElementName, const SMString& sValue);
	
	// Adds a new attribute
	void addAttributeAndValue(const SMString& sAttributeName, const SMString& sValue);

	// Appends this node's XML, as well as all its child nodes
	void format(SMString& xml, int indentLevel = 0);

private:
	SMString name;			// This element's name
	SMString attributes;	// Concatination of all this element's attributes
	SMString value;			// If we're a leaf, this is our value
	nodeVector children;	// If we're not a leaf, these are our child elements

	SMXmlFormatterNode *parent;	// This is our parent node
};
