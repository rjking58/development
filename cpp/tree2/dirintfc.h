#ifndef DIRINTFC_H
#define DIRINTFC_H



#include <afxcoll.h>
#include <afxtempl.h>
#include <afx.h>



// class TreeControl
//{
//
//	CTreeCtrl *	MFCTreeCntrl;
//
//
//}

//FileEntry object... this is a composite patterned class that
//  abstracts the directory/file tree into a generic tree w/ all the 
//  pertinent required info about current files/directories that are on the 
//  disk...

class FSystemEntry : public CObject
{
public:
	FSystemEntry(	CString 			FullPathName,
						FSystemEntry 	*ParentEntry)
		:	mFullPathName(FullPathName),
			mParentEntry(ParentEntry)
	{
	}
	virtual ~FSystemEntry()
	{
	}
	
	CString GetFUllPathName()
	{
	  	return mFullPathName;
	}
	FSystemEntry	*GetParent()
	{
	  	return mParentEntry;
	}
	
	virtual void PrintInfo() = 0;
	virtual CString GetName() = 0;
	virtual HTREEITEM	GetTreeItem()=0;

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	virtual void Initialize(CTreeCtrl	&TreeCtrl) = 0;
	
private:
	FSystemEntry();
	FSystemEntry	*mParentEntry;
	CString 			mFullPathName;	
};

class FileEntry : public FSystemEntry
{
public:
	FileEntry(	CString 				FileName,
					CString 				FullPathName,
					WIN32_FIND_DATA	FileData,
					FSystemEntry		*ParentEntry=0	)
		:	FSystemEntry(FullPathName,ParentEntry),
			mFileName(FileName),
			mFileData(FileData)
			
	{
	}

	CString	GetName();
	HTREEITEM	GetTreeItem();

	void PrintInfo();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize(CTreeCtrl	&TreeCtrl);
	
private:
	CString				mFileName;
	WIN32_FIND_DATA	mFileData;
	TV_INSERTSTRUCT	mTreeStruct;
	HTREEITEM			mTreeItemHandle;
};

class DirEntry : public FSystemEntry
{
public:
	DirEntry(CString 			DirName,
				CString 			FullPathName,
				FSystemEntry	*ParentEntry=0)
		:	FSystemEntry(FullPathName,ParentEntry),
			mDirName(DirName)
	{
	
	}
	~DirEntry();

	// testing for now.
	void PrintInfo();
	CString GetName();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize(CTreeCtrl	&TreeCtrl);
	HTREEITEM	GetTreeItem();

private:
	CTypedPtrArray<CPtrArray,FSystemEntry *> 	mEntries;
   CString 												mDirName;
	TV_INSERTSTRUCT									mTreeStruct;
	HTREEITEM											mTreeItemHandle;
};

#endif