#include <afxcoll.h>
#include <afxtempl.h>



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

class FSystemEntry
{
public:
	FSystemEntry(CString FullPathName)
		:	mFullPathName(FullPathName)
	{
	}
	virtual ~FSystemEntry()
	{
	}
	
	CString GetFUllPathName()
	{
	  	return mFullPathName;
	}
	virtual void PrintInfo() = 0;

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	virtual void Initialize() = 0;
	
private:
	FSystemEntry();
	CString mFullPathName;	
};

class FileEntry : public FSystemEntry
{
public:
	FileEntry(	CString 				FileName,
					CString 				FullPathName,
					WIN32_FIND_DATA	FileData	)
		:	FSystemEntry(FullPathName),
			mFileName(FileName),
			mFileData(FileData)
			
	{
	}

	void PrintInfo();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize();
	
private:
	CString				mFileName;
	WIN32_FIND_DATA	mFileData;
};

class DirEntry : public FSystemEntry
{
public:
	DirEntry(CString DirName,
				CString FullPathName)
		:	FSystemEntry(FullPathName),
			mDirName(DirName)
	{
	
	}
	// testing for now.
	void PrintInfo();

	// will eventually take a CTreeCtrl as a parameter (and an
	// array that will contain a reference to the current item
	// for future reference by the CTreeCtrl w/ the same lparam
	// as the array offset).
	void Initialize();

private:
	CTypedPtrArray<CPtrArray,FSystemEntry *> 	mEntries;
   CString 												mDirName;
	HANDLE												mFileHandle;
};

