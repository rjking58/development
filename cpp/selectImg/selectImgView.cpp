// selectImgView.cpp : implementation of the CSelectImgView class
//

#include "stdafx.h"
#include "selectImg.h"

#include "selectImgDoc.h"
#include "selectImgView.h"

#include "iftree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView

IMPLEMENT_DYNCREATE(CSelectImgView, CTreeView)

BEGIN_MESSAGE_MAP(CSelectImgView, CTreeView)
	//{{AFX_MSG_MAP(CSelectImgView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_RBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView construction/destruction

CSelectImgView::CSelectImgView()
	:	mNodeName("node1"),
		mTheTree(0)
{
	// TODO: add construction code here

}

CSelectImgView::~CSelectImgView()
{
	delete mTheTree;
}

BOOL CSelectImgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView drawing

void CSelectImgView::OnDraw(CDC* pDC)
{
	CSelectImgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView printing

BOOL CSelectImgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSelectImgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSelectImgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView diagnostics

#ifdef _DEBUG
void CSelectImgView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSelectImgView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CSelectImgDoc* CSelectImgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSelectImgDoc)));
	return (CSelectImgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSelectImgView message handlers

void CSelectImgView::OnInitialUpdate() 
{
	CTreeCtrl			&TreeCtrl =	GetTreeCtrl( );
	long					Styles;
	char					*TStr = new char [mNodeName.GetLength() + 1];

	strcpy(TStr,(LPCTSTR) mNodeName);
	
	//28X12
	mMyImageList.Create( 28, 12, ILC_COLOR4,10,10);
	
	mSelectedBM.LoadBitmap(IDB_CIRC_S);
	mNotSelectedBM.LoadBitmap(IDB_CIRC_NS);
	mSomeSelectedBM.LoadBitmap(IDB_CIRC_SS);
	
	// COLORREF
	// 0
	mMyImageList.Add( &mNotSelectedBM,RGB(10,10,10));
	// 1
	mMyImageList.Add( &mSelectedBM,RGB(10,10,10));
	// 2
	mMyImageList.Add( &mSomeSelectedBM,RGB(10,10,10));

	TreeCtrl.SetImageList( &mMyImageList, TVSIL_NORMAL );
	
	CTreeView::OnInitialUpdate();
	
	Styles = GetWindowLong(	m_hWnd,		// handle of window
							GWL_STYLE	// offset of value to set
					  					// new value
									);	
	Styles |= ( TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT );

	SetWindowLong(	m_hWnd,		// handle of window
					GWL_STYLE,	// offset of value to set
					Styles	  	// new value
				  );

	mTheTree = new IFTree(TreeCtrl);
	
	mTheTree->Initialize();

	// TODO: Add your specialized code here and/or call the base class
	
}

void CSelectImgView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl	&TreeCtrl =	GetTreeCtrl( );
	CPoint		ScreenPoint;
	UINT			HitFlags;
	HTREEITEM	ItemToTest;
	
	// get our current mouse position..
	::GetCursorPos(&ScreenPoint);
	// convert to client..
	ScreenToClient(&ScreenPoint);
	// hit test for the selection Icon.
   ItemToTest = TreeCtrl.HitTest(ScreenPoint,&HitFlags);

	if((HitFlags & TVHT_ONITEMICON) != 0)
	{
		
		((IFTree *) TreeCtrl.GetItemData(ItemToTest))->ToggleSelect();
		Invalidate();
	}

	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}



void CSelectImgView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CTreeCtrl	&TreeCtrl =	GetTreeCtrl( );

//	TreeCtrl.Get
	
	*pResult = 0;
}

void CSelectImgView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CSelectImgView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
