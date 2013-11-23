#include <strstrea.h>

// #include <stdafx.h>
#include "dirintfc.h"
#include <assert.h>
#include <string.h>

CString	FileEntry::GetName()
{
	return mFileName;
}


void FileEntry::PrintInfo()
{
	// nothing for now.
}
void FileEntry::Initialize()
{
   // cout << mFileName << endl;
}

const int BUFFSIZE = 1024;

void FileEntry::OpenTest()
{
   FILE *theFile;
   char buffer[BUFFSIZE];
   int  amtRead;
   
   theFile = fopen(mFileName,"rb");
   DWORDLONG currsize = 0;
   if (theFile)
   {
      while(! feof(theFile))
      {
	      // get all data and test against size...
         amtRead = fread(&buffer,1,BUFFSIZE,theFile);
         currsize += amtRead;
      }
      // good open!
      fclose(theFile);
      if (currsize != mFileData.nFileSizeLow)
      {
         cout << endl << "Size mismatch on file: " << mFileName << endl;
      }
//	  else
//	  {
         // cout << mFileName << " is Good" << endl;
//	  }
//      cout << mFileName << "(" << (long) currsize << ") [" << (long) mFileData.nFileSizeLow << "]" << endl ;
      // cout << "GOOD open on:" << mFileName << endl;

   }
   else
   {
      cout << "bad open on:" << mFileName << endl;
   }
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


void DirEntry::Initialize()
{
	WIN32_FIND_DATA 	*EntryData = new WIN32_FIND_DATA;
	int					EntryOfst;
	int					EntryCnt;
	HANDLE				FHandle;

    //cout << mDirName << endl;
   
	// Get all names from this directory..
   ostrstream fileSpec;
   fileSpec << mDirName << "\\*.*" << ends;
   
	FHandle = FindFirstFile(fileSpec.str(),		// address of name of file to search for  
									EntryData );	// address of returned information 
									
   fileSpec.rdbuf()->freeze(0);
                              
		
	if (FHandle == INVALID_HANDLE_VALUE)
	{
		assert(FALSE);
	}
	else
	{
		do
		{
         if (     strcmp(EntryData->cFileName,".") 
               && strcmp(EntryData->cFileName,".."))
         {
            ostrstream fullName;
            fullName << mDirName << "\\" << EntryData->cFileName << ends;
            
	         // if directory.. build new directory structure
	         if (EntryData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	         {
	         	mEntries.Add(new DirEntry(	fullName.str(),
			   										this						));
	         }
	         // else new file structure...
	         else 
	         {
	         	mEntries.Add(new FileEntry(fullName.str(),
			   										*EntryData,
			   										this						));
	         }
            
            fullName.rdbuf()->freeze(0);                                       
         }
			
		} while ( FindNextFile(	FHandle,		
										EntryData   ) );
	
		FindClose(FHandle);


		EntryCnt = mEntries.GetSize();
		for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
		{
			mEntries[EntryOfst]->Initialize();
		}
	}
	delete EntryData;
}

void DirEntry::OpenTest()
{
	int					EntryOfst;
	int					EntryCnt;
   
	EntryCnt = mEntries.GetSize();
	for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
	{
		mEntries[EntryOfst]->OpenTest();
	}

}


void DirEntry::PrintInfo()
{

}


