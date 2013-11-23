//----------------------------------------------------------------------------
//
//  $Archive: /Mobile/Orbiter/Source Code/SMUtilities/SMXmlFormatter.cpp $
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
//  $Revision: 13 $
//
//  This class generates properly formatted XML strings.  Defining the XML
//  requires clients to set an active node, then define attributes and 
//  elements below it.
//
//----------------------------------------------------------------------------

//#region Source control file history
// $History: SMXmlFormatter.cpp $
// 
// *****************  Version 13  *****************
// User: Arodriguez   Date: 2/15/08    Time: 3:08p
// Updated in $/Mobile/Orbiter/Source Code/SMUtilities
// Updated copyright notice (2008).
// 
// *****************  Version 11  *****************
// User: Jheuerman    Date: 5/29/07    Time: 10:37a
// Updated in $/Mobile/SMUtilities
// Fixed newline bug.  If an element contained an empty string "" the
// output would insert a newline between the opening and closing tag.
// This has been fixed.  The code now exports empty elements using the
// proper <foo/> syntax.
// 
// *****************  Version 10  *****************
// User: Arodriguez   Date: 5/25/07    Time: 4:21p
// Updated in $/Mobile/SMUtilities
// Added trace level to LOG Messages.
// 
// *****************  Version 9  *****************
// User: Arodriguez   Date: 4/25/07    Time: 12:54p
// Updated in $/Mobile/SMUtilities
// Changed default spacing from 2 spaces to 4.
// 
// *****************  Version 8  *****************
// User: Jheuerman    Date: 4/25/07    Time: 11:47a
// Updated in $/Mobile/SMUtilities
// 
// *****************  Version 7  *****************
// User: Jheuerman    Date: 4/25/07    Time: 10:00a
// Updated in $/Mobile/SMUtilities
// 
// *****************  Version 6  *****************
// User: Arodriguez   Date: 4/24/07    Time: 6:12p
// Updated in $/Mobile/SMUtilities
// Fixed compiler error in AddElementDouble().
// 
// *****************  Version 5  *****************
// User: Jheuerman    Date: 4/24/07    Time: 4:48p
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
// User: Arodriguez   Date: 4/20/07    Time: 6:32p
// Updated in $/Mobile/SMUtilities
// Added return values where needed.
// 
// *****************  Version 1  *****************
// User: Arodriguez   Date: 4/20/07    Time: 6:23p
// Created in $/Mobile/SMUtilities
// Added stub for SMXmlFormatter.
//#endregion

// --------
// Includes
// --------

#include "StdAfx.h"
#include <stack>

#include "SMTraceUtility.h"
#include "SMMutex.h"
#include "SMSingleLock.h"
#include "SMXmlFormatter.h"

//----------
// Constants
//----------

const char *XmlHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";

//---------
// Typedefs
//---------

typedef std::stack<SMXmlFormatterNode*> nodeStack;

//-------
// Macros
//-------

// This macro creates an SMSingleLock object on the stack.  If we've been instructed to be
// thread-safe, we lock the mutex and let the SMSingleLock destructor automatically unlock
// the mutex when the function returns.

#define SMART_LOCK()\
SMSingleLock singleLock(m_pMutex);\
if( m_pMutex != NULL ) singleLock.Lock();

// This macro passes the parameter 'x' along to SM_LOG() if we've enabled error logging.
// Having a macro do this cleans up the code a bit by converting a two-line operation into one.

#define LOG_ERROR(x)\
if( m_bLogErrors ) SM_LOG(E_FAIL,1,##x##);

// ----------------------
// SMXmlFormatter members
// ----------------------

SMXmlFormatter::SMXmlFormatter(const SMString& sRootNode, bool bMultithreaded /*= false*/)
	: m_root(NULL)
	, m_activeNode(NULL)
	, m_lastNodeAccessed(NULL)
    , m_bLogErrors(true)
	, m_pMutex(NULL)
{
	// Set all three node pointers to the root
	m_root = m_activeNode = m_lastNodeAccessed = SMXmlFormatterNode::createRootNode(sRootNode);

	// If the caller wants us to be thread-safe, allocate a new mutex
    if( bMultithreaded )
        m_pMutex = new SMMutex;
}

SMXmlFormatter::~SMXmlFormatter()
{
	// Delete our root node
	if( m_root )
	{
		delete m_root;
		m_root = NULL;
	}

	// Delete our mutex
    if( m_pMutex )
    {
        delete m_pMutex;
        m_pMutex = NULL;
    }
}

// This method sets the active node within the XML block, ensuring that each
// sub-node is created.  Sub-nodes are defined by separating them by a forward
// slash "/".  By default, the path is relative to the currently active node,
// but you may supply an absolute path by leading off with a slash "/".

HRESULT SMXmlFormatter::SetActiveNode(const SMString& sPathAndNode)
{
	SMART_LOCK();

	// Attempt to navigate to the node
	if( navigateToNode(sPathAndNode) )
	{
		// Success!
		m_lastNodeAccessed = m_activeNode;
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::SetActiveNode(): Error setting active node to \""<<sPathAndNode<<"\".");
    return -1;
}

// This method is functionally identical to SetActiveNode() above, but creates a new instance
// of the final node in the path.  This is useful for creating multiple blocks of XML.

HRESULT SMXmlFormatter::CreateActiveNode(const SMString& sPathAndNode)
{
	SMART_LOCK();

	// We want to separate the final node from the rest of the path, so
	// look for the LAST slash
	int pos = sPathAndNode.ReverseFind('/');
	if( pos != -1 )
	{
		// If the path began with a slash, then just move us to the root and proceed
		if( pos == 0 )
		{
			m_activeNode = m_root;
		}
		// Otherwise, call our normal SetActiveNode() on the first part of the path
		else if( SetActiveNode( sPathAndNode.Left(pos) ) == -1 )
		{
			return -1;
		}
	}

	// Now isolate the last node name
	int finalNodeLength = sPathAndNode.GetLength() - (pos+1);
	SMString finalNode( sPathAndNode.Right(finalNodeLength) );

	// Take care of some special cases that we don't allow
	if( finalNodeLength == 0 ||
		finalNode.StartsWith(".") || 
		finalNode.StartsWith("/") || 
		(finalNode == m_root->getName() && m_activeNode == m_root) )
	{
		// Oops, something went wrong
		LOG_ERROR("SMXmlFormatter::CreateActiveNode(): Cannot create a node at path \""<<sPathAndNode<<"\".");
		return -1;
	}

	// Create new child node at last part
	m_activeNode = navigateToChild( finalNode, true );
	
	// How'd we do?
	if( m_activeNode != NULL )
	{
		// Success!  The new node is created and has become the active node
		m_lastNodeAccessed = m_activeNode;
		return S_OK;
	}

	// Oops, something went wrong.  navigateToChild() will have already reported the error.
	return -1;
}

// This method gets a string representing the path to the current node.

SMString SMXmlFormatter::GetActiveNode()
{
	SMART_LOCK();

	nodeStack path;

	// Starting with the currently active node and working upwards towards the root,
	// push each node onto the stack
	SMXmlFormatterNode *node = m_activeNode;
	while( node )
	{
		path.push(node);
		node = node->getParent();
	}

	SMString str;

	// Now pop each node off the stack and appent its name to our string
	while( !path.empty() )
	{
		str += "/";
		str += path.top()->getName();
		path.pop();
	}

	return str;
}

HRESULT SMXmlFormatter::AddElementString(const SMString& sElementName, const SMString& sValue)
{
	SMART_LOCK();

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, sValue);
}

HRESULT SMXmlFormatter::AddElementInteger(const SMString& sElementName, int nValue)
{
	SMART_LOCK();

	// Convert the int to a string
	SMString str(nValue);

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, str);
}

HRESULT SMXmlFormatter::AddElementDouble(const SMString& sElementName, double fValue)
{
	SMART_LOCK();

	// Convert the double to a string
	SMString str;
	str.sprintf("%f", fValue);

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, str);
}

HRESULT SMXmlFormatter::AddElementBoolean(const SMString& sElementName, bool bValue)
{
	SMART_LOCK();

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, (bValue)? ("1"): ("0"));
}

// This method creates an element which contains a list of integers within
// a comma delimited string.

HRESULT SMXmlFormatter::AddElementIntegerArray(const SMString& sElementName, 
                                               int* pnValues, int nCount)
{
	SMART_LOCK();

	SMString str;

	// Iterate through each value, adding it to our final string
	for(int x=0; x<nCount; x++)
	{
		if( x != 0 )
			str += ",";

		str += SMString(pnValues[x]);
	}

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, str);
}

// This method creates an element which contains a list of floats within
// a comma delimited string.

HRESULT SMXmlFormatter::AddElementFloatArray(const SMString& sElementName, 
                                             float* pnValues, int nCount)
{
	SMART_LOCK();

	SMString str;

	// Iterate through each value, adding it to our final string
	for(int x=0; x<nCount; x++)
	{
		if( x != 0 )
			str += ",";

		str += SMString(pnValues[x]);
	}

	// Add the element as a child of the currently active node
	return addElementAndValue(sElementName, str);
}

HRESULT SMXmlFormatter::AddAttributeString(const SMString& sAttributeName, const SMString& sValue)
{	
	SMART_LOCK();

	// Add the attribute into our most recently-accessed node.  This will either be the
	// active node, or one of its immediate children (depending on whether one of the AddElementX()
	// functions has been called or not).
	if( m_lastNodeAccessed )
	{
		m_lastNodeAccessed->addAttributeAndValue(sAttributeName, sValue);
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::AddAttributeString(): Cannot proceed due to a previous error.  Has another function recently failed?");
	return -1;
}

HRESULT SMXmlFormatter::AddAttributeInteger(const SMString& sAttributeName, int nValue)
{
	SMART_LOCK();

	// Convert the int to a string
	SMString str(nValue);
	
	// Add the attribute into our most recently-accessed node.  This will either be the
	// active node, or one of its immediate children (depending on whether one of the AddElementX()
	// functions has been called or not).
	if( m_lastNodeAccessed )
	{
		m_lastNodeAccessed->addAttributeAndValue(sAttributeName, str);
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::AddAttributeInteger(): Cannot proceed due to a previous error.  Has another function recently failed?");
	return -1;
}

HRESULT SMXmlFormatter::AddAttributeDouble(const SMString& sAttributeName, double nValue)
{
	SMART_LOCK();

	SMString str;

	// Convert the double to a string
	str.sprintf("%f", nValue);

	// Add the attribute into our most recently-accessed node.  This will either be the
	// active node, or one of its immediate children (depending on whether one of the AddElementX()
	// functions has been called or not).
	if( m_lastNodeAccessed )
	{
		m_lastNodeAccessed->addAttributeAndValue(sAttributeName, str);
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::AddAttributeDouble(): Cannot proceed due to a previous error.  Has another function recently failed?");
	return -1;
}

HRESULT SMXmlFormatter::AddAttributeBoolean(const SMString& sAttributeName, bool bValue)
{
	SMART_LOCK();

	// Add the attribute into our most recently-accessed node.  This will either be the
	// active node, or one of its immediate children (depending on whether one of the AddElementX()
	// functions has been called or not).
	if( m_lastNodeAccessed )
	{
		m_lastNodeAccessed->addAttributeAndValue(sAttributeName, (bValue)? ("1"): ("0"));
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::AddAttributeBoolean(): Cannot proceed due to a previous error.  Has another function recently failed?");
	return -1;
}

// This method generates an XML block based on the nodes, elements, attributes and values specified
// through the AddX() functions.

SMString SMXmlFormatter::Format()
{
	SMART_LOCK();

	// Ensure we actually have a tree to export!
	if( m_root )
	{
		// Create our empty XML header
		SMString xml(XmlHeader);
		
		// Append the root element, and all its children, to the string
		m_root->format(xml);
		return xml;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::Format(): Cannot format XML while the root node is empty.");
	return "";
}

bool SMXmlFormatter::navigateToNode(const SMString& sPathAndNode)
{
	// This local copy of the path allows us to make changes
	SMString sPath;

	// If the path starts with a slash, then it's an absolute path
	if( sPathAndNode.StartsWith("/") )
	{
		// Set our active node to the root's parent (which we'll represent with NULL),
		// and remove the leading slash
		m_activeNode = NULL;
		sPath = sPathAndNode.Mid(1, sPathAndNode.GetLength()-1);
	}
	// It's a relative path, so ensure we have an active node to start from
	else if( m_activeNode != NULL )
	{
		// Use the path as-is
		sPath = sPathAndNode;
	}
	else
	{
		// Oops, we can't use a relative path if our active node hasn't been set yet!
		LOG_ERROR("SMXmlFormatter::navigateToNode(): Cannot use a relative path without initially setting the active node.");
		return false;
	}

	// Loop through each part of the path, setting our active node every step of the way
	while( sPath.GetLength() != 0 )
	{
		// Get the next node name
		SMString name = sPath.RemoveToken("/");

		// Is it the "up" keyword?
		if( name == ".." )
		{
			// Ensure we're not at the root
			if( m_activeNode == m_root || m_activeNode == NULL )
			{
				LOG_ERROR("SMXmlFormatter::navigateToNode(): Cannot navigate up using \"..\" because active node is at the m_root.");		
				return false;
			}

			// Recurse one level upwards
			m_activeNode = m_activeNode->getParent();
		}
		// If it's not the "stay here" keyword, then its a node name
		else if( name != "." )
		{
			// Navigate to (or create) a child node with this name
			m_activeNode = navigateToChild(name);
			
			// Did we navigate okay?
			if( !m_activeNode )
				return false;
		}
	}

	// If they simply provided "/" as the path, then our active node will still be NULL from above
	if( m_activeNode == NULL )
		m_activeNode = m_root;

	// Our active node is now the most recently-accessed node
	m_lastNodeAccessed = m_activeNode;
	return true;
}

SMXmlFormatterNode *SMXmlFormatter::navigateToChild(const SMString& sChildName, bool forceCreate /*=false*/)
{
	// Are we currently at the root?
	if( m_activeNode == NULL )
	{
		// Ensure the caller got the root name correct
		if( sChildName != m_root->getName() )
		{
			// Nope!  Report the error and return.
			LOG_ERROR("SMXmlFormatter::navigateToChild(): Incorrect m_root name.  Expected \""<<m_root->getName()<<"\", got \""<<sChildName<<"\".");			
			return NULL;
		}

		// Ensure the caller doesn't want us to create another instance of the root!
		if( forceCreate )
		{
			LOG_ERROR("SMXmlFormatter::navigateToChild(): Incorrect m_root name.  Expected \""<<m_root->getName()<<"\", got \""<<sChildName<<"\".");
			return NULL;
		}

		// Success!
		return m_root;
	}

	// Find a child node with this name.  If we can't, then create one!
	SMXmlFormatterNode *result = m_activeNode->findChild(sChildName, forceCreate);
	if( result )
		return result;

	// Oops, something went wrong
    LOG_ERROR("SMXmlFormatter::navigateToChild(): Cannot set a leaf node as the active node.  Node \""<<sChildName<<"\" is a leaf because it contains a value.");
	return NULL;
}

int SMXmlFormatter::addElementAndValue(const SMString& sElementName, const SMString& sValue)
{
	// Ensure we've correctly set an active node before trying to add an element
	if( m_activeNode == NULL )
	{
		// Oops!
		LOG_ERROR("SMXmlFormatter::addElementAndValue(): Cannot proceed due to a previous error.  Has another function recently failed?");
		return -1;
	}

	// Create a child element with this name and value
	SMXmlFormatterNode *node = m_activeNode->addElementAndValue(sElementName, sValue);

	// How'd we do?
	if( node != NULL )
	{
		// Success!  This new node is now our most recently-accessed node.
		m_lastNodeAccessed = node;
		return S_OK;
	}

	// Oops, something went wrong
	LOG_ERROR("SMXmlFormatter::addElementAndValue(): Node \""<<sElementName<<"\" cannot be given a value because it has child nodes.");
    return -1;
}

// --------------------------
// SMXmlFormatterNode members
// --------------------------

// Constructor for non-leaf nodes
SMXmlFormatterNode::SMXmlFormatterNode(const SMString& sNodeName, SMXmlFormatterNode *pParentNode/*=NULL*/)
	: name(sNodeName), parent(pParentNode), isLeaf(false)
{
}

// Constructor for leaf nodes
SMXmlFormatterNode::SMXmlFormatterNode(const SMString& sElementName, const SMString& sValue, SMXmlFormatterNode *pParentNode/*=NULL*/)
	: name(sElementName), value(sValue), parent(pParentNode), isLeaf(true)
{
}

// Destructor
SMXmlFormatterNode::~SMXmlFormatterNode()
{
}

// Used only once... to create the root node for our XML tree
SMXmlFormatterNode *SMXmlFormatterNode::createRootNode(const SMString& sRootName)
{
	return new SMXmlFormatterNode(sRootName);
}

SMXmlFormatterNode *SMXmlFormatterNode::findChild(const SMString& sChildName, bool forceCreate /*=false*/)
{
	// Look through all our children for a node with this name.  But since we can
	// have SEVERAL children with this name, we're only interested in the last one.
	// Thus, we'll iterate through the children in reverse order.
	for(nodeVector::reverse_iterator x = children.rbegin();
		x != children.rend();
		++x)
	{
		// Did we find our node?
		if( sChildName == (*x)->getName() )
		{
			// Is it a valid candidate to be the active node?
			if( (*x)->isLeaf )
				return NULL;
			
			// Does the caller want us to create a new one or just
			// return the existing one?
			if( !forceCreate )
				return (*x);
		}
	}

	// Couldn't find the node (or the caller wants a new instance), so create it now
	SMXmlFormatterNode *newChild = new SMXmlFormatterNode(sChildName, this);
	children.push_back(newChild);
	return newChild;
}

SMXmlFormatterNode *SMXmlFormatterNode::addElementAndValue(const SMString& sElementName, const SMString& sValue)
{
	// Look through all our children for a node with this name.  We SHOULDN'T find one.
	for(nodeVector::iterator x = children.begin();
		x != children.end();
		++x)
	{
		// If we found one, then we can't rightly add another one!
		if( sElementName == (*x)->getName() &&
			(*x)->isLeaf == false )
		{
			return NULL;
		}
	}

	// Didn't find any other node with this name, so it's safe to create it now
	SMXmlFormatterNode *newChild = new SMXmlFormatterNode(sElementName, sValue, this);
	children.push_back(newChild);
	return newChild;
}

void SMXmlFormatterNode::addAttributeAndValue(const SMString& sAttributeName, const SMString& sValue)
{
	SMString s;

	// The XML specification states that if an attribute's value contains a double-quote,
	// then the value may be wrapped in a single quote instead
	char quote = sValue.Contains('"')? ('\''): ('"');

	// Append this attribute and value to our attributes string
	attributes += s.sprintf(" %s=%c%s%c", sAttributeName.Data(), quote, sValue.Data(), quote);
}

void SMXmlFormatterNode::format(SMString& xml, int indentLevel/*=0*/)
{
	SMString s;

	// If we're a leaf, then we have no children and can just export ourselves and return
	if( isLeaf )
	{
		// Add our element and value to the XML string.  But let's be clever and check to see
		// if this tag's value is an empty string.  If so, we'll export an empty tag <foo/>
		// rather than an opening and closing tag back-to-back <foo></foo>.
		if( value.GetLength() == 0 )
			xml += s.sprintf("%*s<%s%s/>\r\n", indentLevel, "", name.Data(), attributes.Data());
		else
			xml += s.sprintf("%*s<%s%s>%s</%s>\r\n", indentLevel, "", name.Data(), attributes.Data(), value.Data(), name.Data());
		return;
	}

	// We're NOT a leaf, so only add our opening element for now
	xml += s.sprintf("%*s<%s%s>\r\n", indentLevel, "", name.Data(), attributes.Data());

	// Now iterate through all our children and let them export their tags
	for(nodeVector::iterator x = children.begin();
		x != children.end();
		++x)
	{
		// Add two more spaces each time we descend a level
		(*x)->format(xml, indentLevel + 4);
	}

	// Now that our children have been exported, we can add our closing element and return
	xml += s.sprintf("%*s</%s>\r\n", indentLevel, "", name.Data());
}
