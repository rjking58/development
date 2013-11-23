

#include <stdafx.h>
#include "dirintfc.h"
#include <assert.h>
#include <string.h>

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
	char	*TStr = new char [mFileName.GetLength() + 1];

	strcpy(TStr,(LPCTSTR) mFileName);

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


