#ifndef DIRINTFC_H
#define DIRINTFC_H


#include <iostream.h>
#include <fstream.h>


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
						FSystemEntry 	*ParentEntry,
                  int            LevelNo)
		:	mFullPathName(FullPathName),
			mParentEntry(ParentEntry),
         mLevelNo(LevelNo)
	{
		mItemID = mCurrentItemID;
		mCurrentItemID++;
	}
	virtual ~FSystemEntry()
	{
	}
	unsigned unsigned long GetItemID()
	{
		return mItemID;
	}
	
	CString GetFullPathName()
	{
	  	return mFullPathName;
	}
	FSystemEntry	*GetParent()
	{
	  	return mParentEntry;
	}

   int GetLevelNo()
   {
      return mLevelNo;
   }
	
	virtual void PrintInfo() = 0;
	virtual CString GetName() = 0;

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	virtual void Initialize(ofstream & HTMLfile) = 0;
	
private:
	FSystemEntry();
	FSystemEntry	*mParentEntry;
	CString 			mFullPathName;	
	long	 			mItemID;
	static long		mCurrentItemID;
   int            mLevelNo;

};



class FileEntry : public FSystemEntry
{
public:
	FileEntry(	CString 				FileName,
					CString 				FullPathName,
					WIN32_FIND_DATA	FileData,
               FSystemEntry		*ParentEntry=0,
               int               LevelNo = 1       )
		:	FSystemEntry(FullPathName,ParentEntry,LevelNo),
			mFileName(FileName),
			mFileData(FileData)
			
	{
	}

	CString	GetName();

	void PrintInfo();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize(ofstream & HTMLfile);
	
private:
	CString				mFileName;
	WIN32_FIND_DATA	mFileData;
};

class DirEntry : public FSystemEntry
{
public:
	DirEntry(CString 			DirName,
				CString 			FullPathName,
				FSystemEntry	*ParentEntry=0,
            int            LevelNo=0        )
		:	FSystemEntry(FullPathName,ParentEntry,LevelNo),
			mDirName(DirName),
			mAggregate_size(0)
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
	void 			Initialize(ofstream & HTMLfile);

private:
	// data
	CTypedPtrArray<CPtrArray,FSystemEntry *> 	mEntries;
   CString 												mDirName;
	unsigned long 										mAggregate_size;

	// interface

};

#endif