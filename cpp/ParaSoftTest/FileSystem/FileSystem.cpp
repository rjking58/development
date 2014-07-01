//FileSystem Class design example.


// abstract base class for a file system entry
//   all abstract semantic rules followed..
//      o destructor declared virtual so that deleted from base class pointers 
//        yields defined behavior.
//      o non-variant behaviors common to subclasses brought into base class.
class FSystemEntry
{
public:
   FSystemEntry(  CString          FullPathName,
                  FSystemEntry    *ParentEntry);
   virtual           ~FSystemEntry();
   
   CString           GetFullPathName();
   FSystemEntry      *GetParent();
   
   virtual void      PrintInfo() = 0;
   virtual CString   GetName() = 0;
   virtual boolean   GetBooleanAttribute() = 0;

   
private:
   
   FSystemEntry      *mParentEntry; // for traversing up tree.
   CString           mFullPathName; // so that file system calls
                                    // don't require constructing this
};

// entry for a single file.
// 
class FileEntry : public FSystemEntry
{
public:
   FileEntry(  CString           FileName,
               CString           FullPathName,
               WIN32_FIND_DATA   FileData,
               FSystemEntry      *ParentEntry=0   );

   CString   GetName();
   HTREEITEM   GetTreeItem();

   void PrintInfo();

   
private:
   CString            mFileName;
};

// collection of Dir entry.  Note the pointer array declared as 
// pointers to 'FSystemEntries'.  
class DirEntry : public FSystemEntry
{
public:
   DirEntry(CString        DirName,
            CString        FullPathName,
            FSystemEntry   *ParentEntry=0);
   ~DirEntry();

   // testing for now.
   void PrintInfo();
   CString GetName();


private:
   CTypedPtrArray<CPtrArray,FSystemEntry *>    mEntries;
   CString                                     mDirName;
   TV_INSERTSTRUCT                           mTreeStruct;
   HTREEITEM                                 mTreeItemHandle;
};
