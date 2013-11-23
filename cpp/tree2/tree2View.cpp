// tree2View.cpp : implementation of the CTree2View class
//

#include "stdafx.h"
#include "tree2.h"

#include "tree2Doc.h"
#include "tree2View.h"
#include "dirintfc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree2View

IMPLEMENT_DYNCREATE(CTree2View, CTreeView)

BEGIN_MESSAGE_MAP(CTree2View, CTreeView)
	//{{AFX_MSG_MAP(CTree2View)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree2View construction/destruction

CTree2View::CTree2View()
	: m_aDE("C:\\","C:\\")
{
	// TODO: add construction code here

}

CTree2View::~CTree2View()
{
}

BOOL CTree2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTree2View drawing

void CTree2View::OnDraw(CDC* pDC)
{
	CTree2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTree2View printing

BOOL CTree2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTree2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTree2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTree2View diagnostics

#ifdef _DEBUG
void CTree2View::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTree2View::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTree2Doc* CTree2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTree2Doc)));
	return (CTree2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree2View message handlers

void CTree2View::OnInitialUpdate() 
{

	const int			NodeNamesz = 100;
	CTreeCtrl			&TreeCtrl =	GetTreeCtrl( );
	TV_INSERTSTRUCT	TreeStruct;
	long					Styles;
	char					NodeName[NodeNamesz];


//	x = 1;
//	di = new DirTreeFactory;
//	fobj = di->GetFirstFile();
//	if(fobj != NULL)
//	{
//		delete fobj;
//		while (		(x < 10 		)
//				&&	(! di->IsDone()	)	)
//		{
//			fobj = di->GetNextFile();
//			if(fobj != NULL)
//			{
//				delete fobj;
//			}
//			x++;
//		}
//	}
 



	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	// setup the extra's on the tree view...

	Styles = GetWindowLong(	m_hWnd,		// handle of window
							GWL_STYLE	// offset of value to set
					  					// new value
									);	
	Styles |= ( TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT );

	SetWindowLong(	m_hWnd,		// handle of window
					GWL_STYLE,	// offset of value to set
					Styles	  	// new value
				  );	

 
// 	TreeStruct.hParent = NULL;
// 	TreeStruct.hInsertAfter = TVI_SORT;
// 	TreeStruct.item.mask = TVIF_TEXT | TVIF_PARAM;
// 	TreeStruct.item.pszText = NodeName;
// 	TreeStruct.item.cchTextMax = NodeNamesz - 1;
// 	TreeStruct.item.lParam = 44;
// 	strcpy(NodeName,"Item1");
// 
// 	m_TreeItemHandle[0] =  TreeCtrl.InsertItem(&TreeStruct); 	
// 	
// 
// 	TreeStruct.hParent = m_TreeItemHandle[0];
// 	TreeStruct.hInsertAfter = TVI_SORT;
// 	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT | TVIF_PARAM;
// 	TreeStruct.item.pszText = NodeName;
// 	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
// 	TreeStruct.item.lParam = 66;
// 	strcpy(NodeName,"SubItem1a");
// 	m_TreeItemHandle[1] =  TreeCtrl.InsertItem(&TreeStruct); 	
// 
	m_aDE.Initialize(TreeCtrl);
	

}



void CTree2View::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	TV_ITEM	*Old = &(pNMTreeView->itemOld);
	TV_ITEM *New = &(pNMTreeView->itemNew);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
