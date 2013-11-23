

#include <stdafx.h>
#include "iftree.h"
#include <assert.h>
#include <string.h>
#include <strstrea.h>

long	IFTree::NextIdent = 0;


IFTree::	IFTree(	CTreeCtrl &TreeCtrl,
						IFTree * Parent,
						int		lvl		)
	:	mParent (Parent),
		mTreeCtrl(TreeCtrl),
		mHTREEITEM(0),
		mSelected(Off),
		mLvl(lvl)
{
	mMyIdent = NextIdent++;
}

IFTree::~IFTree()
{
	int	ChildCnt = mChildren.GetSize();
	int	ChildCur;

	for (ChildCur = 0; ChildCur < ChildCnt; ChildCur++)
	{
		delete mChildren[ChildCur];
	}
}

IFTree * IFTree::GetParent()
{
  	return mParent;
}

HTREEITEM IFTree::GetTreeItem()
{
	return mHTREEITEM;
}

IFTree::SelectionFlag IFTree::GetSelect()
{
	return mSelected;
}

void IFTree::SetSelectToAllChildren()
{
	int ChildCnt = mChildren.GetSize();
	int ChildCur;

	mSelected = IFTree::On;
	UpdateImages();

	if(ChildCnt > 0)
	{
		for (ChildCur = 0; ChildCur < ChildCnt; ChildCur++)
		{
			mChildren[ChildCur]->SetSelectToAllChildren();
		}
	}
}

void IFTree::ClearSelectToAllChildren()
{
	int ChildCnt = mChildren.GetSize();
	int ChildCur;

	mSelected = IFTree::Off;
	UpdateImages();

	if(ChildCnt > 0)
	{
		for (ChildCur = 0; ChildCur < ChildCnt; ChildCur++)
		{
			mChildren[ChildCur]->ClearSelectToAllChildren();
		}
	}
}

void IFTree::ToggleSelect()
{
	if(	mSelected == IFTree::Some 
		|| mSelected == IFTree::Off)
	{
		SetSelectToAllChildren();
	}
	else
	{
		ClearSelectToAllChildren();
	}

	if(GetParent())
	{
		GetParent()->UpdateParentByChildren();
	}
}

void IFTree::SetImages(TV_ITEM * tv_item)
{
	switch (mSelected)
	{
		case IFTree::Off:
			tv_item->iImage = 0;
			tv_item->iSelectedImage = 0;	
			break;
		case IFTree::On:
			tv_item->iImage = 1;
			tv_item->iSelectedImage = 1;	
			break;
		case IFTree::Some:
			tv_item->iImage = 2;
			tv_item->iSelectedImage = 2;	
			break;
	}
}

void IFTree::UpdateImages()
{
	TV_ITEM tv_item;
	
	tv_item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_HANDLE ;
	tv_item.hItem = mHTREEITEM;
	SetImages(&tv_item);

	mTreeCtrl.SetItem(&tv_item);
}

void IFTree::UpdateParentByChildren()
{
	int ChildCnt = mChildren.GetSize();
	int ChildCur;
	int OnCnt = 0;

	for (ChildCur = 0; ChildCur < ChildCnt; ChildCur++)
	{
		if(	mChildren[ChildCur]->GetSelect() == IFTree::Some
			||	mChildren[ChildCur]->GetSelect() == IFTree::On	)
		{
			OnCnt++;
		}
	}
	
	if(OnCnt == ChildCnt)
	{
		mSelected = IFTree::On;
	}
	else if (OnCnt == 0)
	{
		mSelected = IFTree::Off;
	}
	else
	{
		mSelected = IFTree::Some;
	}

	UpdateImages();

	if(GetParent())
	{
		GetParent()->UpdateParentByChildren();
	}

}
									
void IFTree::Initialize()
{
	ostrstream	NodeName;
	
	NodeName << "Node" << mMyIdent << ends;
	
	char	*TStr = new char [strlen(NodeName.str()) + 1];

	strcpy(TStr,NodeName.str());

	if (mParent)
	{
		mTreeStruct.hParent = GetParent()->GetTreeItem();
	}
	else
	{
		mTreeStruct.hParent = NULL;
	}
	mTreeStruct.hInsertAfter = TVI_SORT;
	mTreeStruct.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	mTreeStruct.item.pszText = TStr;
	mTreeStruct.item.cchTextMax = strlen(TStr);
	mTreeStruct.item.lParam = (long) this;
	
	SetImages(&(mTreeStruct.item));
				 
	mHTREEITEM = mTreeCtrl.InsertItem(&mTreeStruct); 	
	
	if (mLvl < 3)
	{
		for (int x = 0; x < 3; x++)
		{
			IFTree * newItem = new IFTree(mTreeCtrl,this,mLvl + 1);
			newItem->Initialize();
			mChildren.Add(newItem);
		}
	}

	NodeName.rdbuf()->freeze(0);
}

#if 0
CString	FileEntry::GetName()
{
	return mFileName;
}

HTREEITEM	FileEntry::GetTreeItem()
{
	return mTreeItemHandle;
}


void FileEntry::PrintInfo()
{
	// nothing for now.
}
void FileEntry::Initialize(CTreeCtrl	&TreeCtrl)
{
	ostrstream	NodeName;
	
	NodeName << "Node" << mMyIdent << ends;
	
	char	*TStr = new char [strlen(NodeName.str() + 1];

	strcpy(TStr,NodeName.str());

	// nothing for now..
	mTreeStruct.hParent = GetParent()->GetTreeItem();
	mTreeStruct.hInsertAfter = TVI_SORT;
	mTreeStruct.item.mask = TVIF_TEXT | TVIF_PARAM;
	mTreeStruct.item.pszText = TStr;
	mTreeStruct.item.cchTextMax = mFileName.GetLength();
	mTreeStruct.item.lParam = 44;
	
	mTreeItemHandle = TreeCtrl.InsertItem(&mTreeStruct); 	

	delete [] TStr;		
}

CString	DirEntry::GetName()
{
	return mDirName;
}

DirEntry::~DirEntry()
{
	int EntryCnt = mEntries.GetSize();
	int EntryOfst;

	for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
	{
		delete mEntries[EntryCnt];
	}

}

HTREEITEM	DirEntry::GetTreeItem()
{
	return mTreeItemHandle;
}

void DirEntry::Initialize(CTreeCtrl	&TreeCtrl)
{
	WIN32_FIND_DATA 	*EntryData = new WIN32_FIND_DATA;
	int					EntryOfst;
	int					EntryCnt;
	HANDLE				FHandle;

	char	*TStr = new char [mDirName.GetLength() + 1];

	strcpy(TStr,(LPCTSTR) mDirName);

	
	
	// Get all names from this directory..
	FHandle = FindFirstFile("c:\\*.*",		// address of name of file to search for  
									EntryData );	// address of returned information 
									
									
		
	if (FHandle == INVALID_HANDLE_VALUE)
	{
		assert(FALSE);
	}
	else
	{
		do
		{
	      // if directory.. build new directory structure
	      if (EntryData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	      {
	      	mEntries.Add(new DirEntry(	EntryData->cFileName,
													EntryData->cFileName,
													this						));
	      }
	      // else new file structure...
	      else 
	      {
	      	mEntries.Add(new FileEntry(EntryData->cFileName,
													EntryData->cFileName,
													*EntryData,
													this						));
	      }
			
			
		} while ( FindNextFile(	FHandle,		
										EntryData   ) );
	
		FindClose(FHandle);
		if(GetParent())
		{
			mTreeStruct.hParent = GetParent()->GetTreeItem();
		}
		else
		{
			mTreeStruct.hParent = NULL;
		}
		mTreeStruct.hInsertAfter = TVI_SORT;
		mTreeStruct.item.mask = TVIF_TEXT | TVIF_PARAM;
		mTreeStruct.item.pszText = TStr;
		mTreeStruct.item.cchTextMax = mDirName.GetLength();
		mTreeStruct.item.lParam = 44;
		
					  
		mTreeItemHandle = TreeCtrl.InsertItem(&mTreeStruct); 	
		


		EntryCnt = mEntries.GetSize();
		for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
		{
			mEntries[EntryOfst]->Initialize(TreeCtrl);
		}
	}
	delete [] TStr;
	delete EntryData;
}

void DirEntry::PrintInfo()
{

}

#endif
