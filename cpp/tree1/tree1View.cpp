// tree1View.cpp : implementation of the CTree1View class
//

#include "stdafx.h"
#include "tree1.h"

#include "tree1Doc.h"
#include "tree1View.h"
#include "dirintfc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTree1View

IMPLEMENT_DYNCREATE(CTree1View, CTreeView)

BEGIN_MESSAGE_MAP(CTree1View, CTreeView)
	//{{AFX_MSG_MAP(CTree1View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree1View construction/destruction

CTree1View::CTree1View()
{
	// TODO: add construction code here

}

CTree1View::~CTree1View()
{
}

BOOL CTree1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	// The user can expand or collapse a parent item’s list of 
	// child items by double-clicking the parent item. A tree 
	// control that has the TVS_HASBUTTONS style adds a button 
	// to the left side of each parent item. The user can click 
	// the button to expand or collapse the child items as an 
	// alternative to double-clicking the parent item. TVS_HASBUTTONS 
	// does not add buttons to items at the root of the hierarchy. 
	// To do so, you must combine TVS_HASLINES, TVS_LINESATROOT, 
	// and TVS_HASBUTTONS.

//	The SetWindowLong function changes an attribute of the specified window. The function also sets a 32-bit (long) value at the specified offset into the extra window memory of a window. 

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTree1View drawing

void CTree1View::OnDraw(CDC* pDC)
{
	CTree1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTree1View printing

BOOL CTree1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTree1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTree1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTree1View diagnostics

#ifdef _DEBUG
void CTree1View::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTree1View::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTree1Doc* CTree1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTree1Doc)));
	return (CTree1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTree1View message handlers

void CTree1View::OnInitialUpdate() 
{

	DirTreeFactory			*di;
	FileEntry				*fobj;
	const int				NodeNamesz = 100;
	int						x;
	CTreeCtrl& TreeCtrl =	GetTreeCtrl( );
	TV_INSERTSTRUCT			TreeStruct;
	long					Styles;
	char					NodeName[NodeNamesz];

	x = 1;
	di = new DirTreeFactory;
	fobj = di->GetFirstFile();
	if(fobj != NULL)
	{
		delete fobj;
		while (		(x < 10 		)
				&&	(! di->IsDone()	)	)
		{
			fobj = di->GetNextFile();
			if(fobj != NULL)
			{
				delete fobj;
			}
			x++;
		}
	}
 
	

	CTreeView::OnInitialUpdate();


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




// BOOL GetItem( TV_ITEM* pItem );
//   
// Return Value
// Nonzero if successful; otherwise 0.
// Parameters
// pItem   A pointer to a TV_ITEM structure.
// Remarks
// Call this function to retrieve the attributes of the specified tree view item.
// The TV_ITEM structure is defined as follows:
//   
// typedef struct _TV_ITEM {  tvi
//     UINT       mask;            
//     HTREEITEM  hItem;           // item this structure refers to
//     UINT       state;           
//     UINT       stateMask;       
//     LPSTR      pszText;         
//     int        cchTextMax;      
//     int        iImage;          
//     int        iSelectedImage;  
//     int        cChildren;       
//     LPARAM     lParam;          // 32-bit value to associate with item
// } TV_ITEM;
//   
// mask   Array of flags that indicate which of the other structure members contain valid data or which are to be filled in. It can be a combination of these values:
// ·	TVIF_CHILDREN   The cChildren member is valid.
// ·	TVIF_HANDLE   The hItem member is valid.
// ·	TVIF_IMAGE   The iImage member is valid.
// ·	TVIF_PARAM   The lParam member is valid.
// ·	TVIF_SELECTEDIMAGE   The iSelectedImage member is valid.
// ·	TVIF_STATE   The state and stateMask members are valid.
// ·	TVIF_TEXT   The pszText and cchTextMax members are valid.
// state and stateMask   Variables specifying the current state of the item and the valid states of the item. They can be any valid combination of state values. Valid states are:
// ·	TVIS_CUT   The item is selected as part of a cut and paste operation.
// ·	TVIS_DISABLED   The item is disabled and is drawn using the standard disabled style and color.
// ·	TVIS_DROPHILITED   The item is selected as a drag-and-drop target.
// ·	TVIS_EXPANDED   The item’s list of child items is currently expanded; that is, the child items are visible. This value applies only to parent items.
// ·	TVIS_EXPANDEDONCE   The item’s list of child items has been expanded at least once. The TVN_ITEMEXPANDING and TVN_ITEMEXPANDED notification messages are not sent for parent items that have specified this value. This value applies only to parent items.
// ·	TVIS_FOCUSED   The item has the focus and is surrounded by a standard focus rectangle. Although more than one item may be selected, only one item can have the focus.
// ·	TVIS_OVERLAYMASK   The item’s overlay image is included when the item is drawn. The index of the overlay image must be specified in the state member of the TV_ITEM structure by using the Win32 INDEXTOOVERLAYMASK macro. The overlay image must be added to the tree view’s image list by using the CImageList::SetOverlayImage function. This value should not be combined with any other value.
// ·	TVIS_SELECTED   The item is selected. The appearance of a selected item depends on whether it has the focus and on whether the system colors are used for selection.
// ·	TVIS_STATEIMAGEMASK   The item’s state image is included when the item is drawn. The index of the state image must be specified in the state member of the TV_ITEM structure by using the Win32 INDEXTOSTATEIMAGEMASK macro. This value should not be combined with any other value.
// pszText   Address of a null-terminated string containing the item text if the structure specifies item attributes. If this member is the LPSTR_TEXTCALLBACK value, the parent window is responsible for storing the name. In this case, the tree view control sends the parent window a TVN_GETDISPINFO notification message when it needs the item text for displaying, sorting, or editing, and the tree view sends a TVN_SETDISPINFO notification when the item text changes. If the structure is receiving item attributes, this member is the address of the buffer that receives the item text.
// cchTextMax   Size of the buffer pointed to by the pszText member if the structure is receiving item attributes. This member is ignored if the structure specifies item attributes.
// iImage and iSelectedImage   Indexes of the icon image and selected icon image within the image list. If either member is the I_IMAGECALLBACK value, the parent window is responsible for storing the corresponding images. In this case, the tree view control sends the parent a TVN_GETDISPINFO notification message when it needs to display the images and a TVN_SETDISPINFO notification message when the images change.
// cChildren   Number of child items associated with the item. If this member is the I_CHILDRENCALLBACK value, the parent window is responsible for drawing the child items. In this case, the tree view control sends the parent a TVN_GETDISPINFO notification message when it needs to display the child items and a TVN_SETDISPINFO notification message when the attributes of a child item change.


//The TV_INSERTSTRUCT structure is defined as follows:
//  
//typedef struct _TV_INSERTSTRUCT {
//    HTREEITEM hParent;       
//    HTREEITEM hInsertAfter;  
//    TV_ITEM   item;   
//} TV_INSERTSTRUCT;
  

//hInsertAfter   Handle of the item after which the new item is to be inserted or one of the following values:
//·	TVI_FIRST   Inserts the item at the beginning of the list.
//·	TVI_LAST   Inserts the item at the end of the list.
//·	TVI_SORT   Inserts the item into the list in alphabetical order.

	TreeStruct.hParent = NULL;
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"Item1");

	m_TreeItemHandle[0] =  TreeCtrl.InsertItem(&TreeStruct); 	
	

	TreeStruct.hParent = m_TreeItemHandle[0];
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"SubItem1a");


	m_TreeItemHandle[1] = TreeCtrl.InsertItem(&TreeStruct);		// HTREEITEM hInsertAfter );

	TreeStruct.hParent = m_TreeItemHandle[0];
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"SubItem1b");


	m_TreeItemHandle[2] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );


	TreeStruct.hParent = m_TreeItemHandle[1];
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"SubItem1a1");


	m_TreeItemHandle[3] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );

	TreeStruct.hParent = m_TreeItemHandle[1];
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"SubItem1a2");


	m_TreeItemHandle[4] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );

	TreeStruct.hParent = m_TreeItemHandle[3];
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"SubItem1a1a");


	m_TreeItemHandle[5] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );

	TreeStruct.hParent = NULL;
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"Item2");


	m_TreeItemHandle[6] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );

	TreeStruct.hParent = NULL;
	TreeStruct.hInsertAfter = TVI_SORT;
	TreeStruct.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TreeStruct.item.pszText = NodeName;
	TreeStruct.item.cchTextMax = NodeNamesz - 1;	
	strcpy(NodeName,"Item3");


	m_TreeItemHandle[7] = TreeCtrl.InsertItem(&TreeStruct);			// HTREEITEM hInsertAfter );


	for (x = 0 ; x < 8 ; x++)
	{
		char	NodeName2[NodeNamesz];
		TV_ITEM tv_item;

		tv_item.hItem = m_TreeItemHandle[x];
		tv_item.mask = TVIF_HANDLE | TVIF_TEXT  | TVIF_CHILDREN;

		// MAKE SURE TO PUT A STRING FOR RECEIVING THE TEXT...
		
		tv_item.pszText = NodeName;
		tv_item.cchTextMax = NodeNamesz - 1;
		TreeCtrl.GetItem(&tv_item);

		sprintf(NodeName2,"%s (cChildren:%d)",NodeName,tv_item.cChildren);

		tv_item.pszText = NodeName2;
		tv_item.cchTextMax = NodeNamesz - 1;
		tv_item.mask = TVIF_HANDLE | TVIF_TEXT;
		TreeCtrl.SetItem(&tv_item);
	}
}

BOOL CTree1View::DestroyWindow() 
{
	

	return CTreeView::DestroyWindow();
}
