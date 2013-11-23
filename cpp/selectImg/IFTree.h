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

class IFTree
{
public:
	enum SelectionFlag
	{
		Off,
		On,
		Some
	};


	IFTree(	CTreeCtrl &TreeCtrl,
				IFTree * Parent=0,
				int		lvl=0	);
	~IFTree();
	IFTree *GetParent();
	
	HTREEITEM	GetTreeItem();

	void				SetSelectToAllChildren();
	void				ClearSelectToAllChildren();
	SelectionFlag	GetSelect();
	void				ToggleSelect();
	void				SetImages(TV_ITEM * tv_item);
	void				UpdateImages();

	void UpdateParentByChildren();
	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	virtual void Initialize();

	
private:
	// interface
	IFTree();
	
	// data
	IFTree										*mParent;
	CTypedPtrArray<CPtrArray,IFTree *> 	mChildren;
	CTreeCtrl									&mTreeCtrl;
	HTREEITEM									mHTREEITEM;
	SelectionFlag								mSelected;
	TV_INSERTSTRUCT							mTreeStruct;
	long											mMyIdent;
	static long									NextIdent;
	int											mLvl;
};

#if 0
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

#endif
