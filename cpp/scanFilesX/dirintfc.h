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

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	virtual void Initialize() = 0;
   virtual void OpenTest() = 0;
	
private:
	FSystemEntry();
	FSystemEntry	*mParentEntry;
	CString 			mFullPathName;	
};

class FileEntry : public FSystemEntry
{
public:
	FileEntry(  CString 				FullPathName,
					WIN32_FIND_DATA	FileData,
					FSystemEntry		*ParentEntry=0	)
		:	FSystemEntry(FullPathName,ParentEntry),
			mFileName(FullPathName),
			mFileData(FileData)
			
	{
	}

	CString	GetName();

	void PrintInfo();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize();
   void OpenTest();
	
private:
	CString				mFileName;
	WIN32_FIND_DATA	mFileData;
};

class DirEntry : public FSystemEntry
{
public:
	DirEntry(CString 			FullPathName,
				FSystemEntry	*ParentEntry=0)
		:	FSystemEntry(FullPathName,ParentEntry),
			mDirName(FullPathName)
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
	void Initialize();
   void OpenTest();

private:
	CTypedPtrArray<CPtrArray,FSystemEntry *> 	mEntries;
   CString 												mDirName;
};

#endif