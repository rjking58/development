

#include "dirintfc.h"
#include <assert.h>
#include <string.h>
#include <iostream.h>
#include <strstrea.h>


long FSystemEntry::mCurrentItemID = 1;


CString	FileEntry::GetName()
{
	return mFileName;
}


void FileEntry::PrintInfo()
{
	// nothing for now.
}
void FileEntry::Initialize(ofstream & HTMLfile)
{
   cout << "(" << GetLevelNo() << ") " << "FILE:" << GetFullPathName() << endl;
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
		delete mEntries[EntryOfst];
	}

}


void DirEntry::Initialize(ofstream & HTMLfile)
{
	// tv_item
	WIN32_FIND_DATA 	*EntryData = new WIN32_FIND_DATA;
	int					EntryOfst;
	int					EntryCnt;
	HANDLE				FHandle;
	ostrstream			TStr;
	ostrstream			TStr2;


	TStr << mDirName << ends;
	TStr2 << GetFullPathName() << "\\*.*" << ends;
	
	cout << "(" << GetLevelNo() << ") " << GetFullPathName() << endl;
	// Get all names from this directory..
	FHandle = FindFirstFile(TStr2.str(),		// address of name of file to search for  
									EntryData );	// address of returned information 
									
									
		
	if (FHandle ==INVALID_HANDLE_VALUE)
	{
		assert(FALSE);
	}
	else
	{
		do
		{
			if(	(strcmp(EntryData->cFileName,"." ))
				&&	(strcmp(EntryData->cFileName,"..")) )
			{
				ostrstream			NewFullpath;

				NewFullpath << GetFullPathName() << "\\" << EntryData->cFileName << ends;

			   // if directory.. build new directory structure
				if (EntryData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		      {
		      	mEntries.Add(new DirEntry(	EntryData->cFileName,
														NewFullpath.str(),
														this,
                                          GetLevelNo()+1       ));
		      }
		      // else new file structure...
			   else 
				{
               // add entry ONLY if it is a '.url' file.
               int nameLen = strlen(EntryData->cFileName);
               if (     nameLen > 4
                     && EntryData->cFileName[nameLen -4] == '.'
                     && (     EntryData->cFileName[nameLen -3] == 'u'
                           || EntryData->cFileName[nameLen -3] == 'U' )
                     && (     EntryData->cFileName[nameLen -2] == 'r'
                           || EntryData->cFileName[nameLen -2] == 'R' )
                     && (     EntryData->cFileName[nameLen -1] == 'l'
                           || EntryData->cFileName[nameLen -1] == 'L' )   )  
               {
   		      	mEntries.Add(new FileEntry(EntryData->cFileName,
	   													NewFullpath.str(),
		   												*EntryData,
			   											this,
                                             GetLevelNo()+1      ));
               }
		      }
			
				NewFullpath.rdbuf()->freeze(0);
			}

		} while ( FindNextFile(	FHandle,		
										EntryData   ) );
	
		FindClose(FHandle);


		EntryCnt = mEntries.GetSize();

		for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
		{
			mEntries[EntryOfst]->Initialize(HTMLfile);
		}

	}
	TStr2.rdbuf()->freeze(0);
	TStr.rdbuf()->freeze(0);

	delete EntryData;

}

void DirEntry::PrintInfo()
{

}


