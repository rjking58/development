// game2Doc.cpp : implementation of the CGame2Doc class
//

#include "stdafx.h"
#include "game2.h"

#include "game2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int const UNIT_COUNT = 10;

/////////////////////////////////////////////////////////////////////////////
// CGame2Doc

IMPLEMENT_DYNCREATE(CGame2Doc, CDocument)

BEGIN_MESSAGE_MAP(CGame2Doc, CDocument)
	//{{AFX_MSG_MAP(CGame2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGame2Doc construction/destruction

CGame2Doc::CGame2Doc() : mUnitCount(0)
{
	// TODO: add one-time construction code here
	mUnitMap.InitHashTable(MAX_MAP_HASH);

}

CGame2Doc::~CGame2Doc()
{
}

BOOL CGame2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	InitDocument();
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGame2Doc serialization

void CGame2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_sizeDoc;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_sizeDoc;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGame2Doc diagnostics

#ifdef _DEBUG
void CGame2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGame2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGame2Doc commands

void CGame2Doc::InitDocument()
{
	int x;

	// initialize size of document...

	m_sizeDoc = CSize(	MAP_WIDTH  * ICON_SCALE,
								MAP_HEIGHT * ICON_SCALE);
	mMapHeight = MAP_HEIGHT;
	mMapWidth  = MAP_WIDTH;

	// TODO : make this better

	// make 10 units and place them on the map...
	for (x = 0; x < 10 ; x++)
	{
		Soldier *aSoldier;
		// TODO:  clean these up somewhere...
		// CMap
		aSoldier = new Soldier(x,x);

		aSoldier->RegisterObserver(&theMap);

		mUnitMap.SetAt(aSoldier,aSoldier);
		theMap.PositionNew(	x,			//new x,y
				 					x,
				 					aSoldier);
		mUnitCount++;
	}

}

int CGame2Doc::GetMapWidth()
{
	return mMapHeight;
}

int CGame2Doc::GetMapHeight()
{
	return mMapWidth;
}




BOOL CGame2Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	InitDocument();
	
	return TRUE;
}

void CGame2Doc::OnCloseDocument() 
{
	POSITION	nextMapPos;
	Unit *		currUnit;
	Unit *		currUnitKey;

	// TODO: Add your specialized code here and/or call the base class
	// this should be moved to common code so that is also called for a 
	// document delete!

	//CMap
	nextMapPos = mUnitMap.GetStartPosition();

	while(nextMapPos != NULL)
	{
		mUnitMap.GetNextAssoc( nextMapPos, currUnitKey, currUnit );
		delete currUnit;
	}
  

	mUnitMap.RemoveAll();
	
	CDocument::OnCloseDocument();
}
