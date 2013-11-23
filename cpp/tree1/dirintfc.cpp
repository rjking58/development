

#include <stdafx.h>
#include "dirintfc.h"



void FileEntry::PrintInfo()
{
	// nothing for now.
}
void FileEntry::Initialize()
{
	// nothing for now..
}



DirEntry::Initialize()
{
	WIN32_FIND_DATA 	EntryData;
	int					EntryOfst;
	int					EntryCnt;
	// Get all names from this directory..
	FHandle = FindFirstFile(	"c:\\*.*",		// address of name of file to search for  
											&EntryData );	// address of returned information 
		
	if (FHandle == INVALID_HANDLE_VALUE)
	{
		assert(FALSE);
	}
	else
	{
		do
		{
	      // if directory.. build new directory structure
	      if (EntryData.dwFileAttrbutes & FILE_ATTRIBUTE_DIRECTORY )
	      {
	      	mEntries.Add(new DirEntry(	EntryData.cFileName,
													EntryData.cFileName	));
	      }
	      // else new file structure...
	      else 
	      {
	      	mEntries.Add(new FileEntry(EntryData.cFileName,
													EntryData.cFileName,
													EntryData				));
	      }
			
			
		} while ( FindNextFile(	FHandle,		
										&EntryData   ) );
	
		FindClose(FHandle);
		
		EntryCnt = mEntries.GetSize();
		for (EntryOfst = 0; EntryOfst < EntryCnt; EntryOfst++)
		{
			// mEntries[EntryCnt]->Initialize();
		}
	}
}

DirEntry::PrintInfo()
{

}


