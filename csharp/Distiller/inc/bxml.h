/************************************************************************************
    Filename: bxml.h
    
    Project: XZite binary XML reader.

    Description:
    
     Interface to the BXML structure and parser.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/06/07    ryoung      Moved into seperate file.
************************************************************************************/

#ifndef BXML_H
#define BXML_H


#include "types.h"
#include "strlist.h"
#include <stdio.h>


/*--------------------------------------------
				Constants
----------------------------------------------*/

static const char szBXML_DocType[]= "bxml10";	/* Binary distilled XML doc type ID. */
#define kmBXML_TagFlag_Close	0x80            /* Flag bit in a tagID to tell when a tag is closing a section. */
#define kmBXML_TagData      	0x7f			/* Data field of tag ID. */

typedef enum {

	kBXML_Err_None			= 0,				/* No error. */
	kBXML_Err_TagNotFound	= -1,				/* Search tag wasn't found within scope. */
	kBXML_Err_EOF			= -2,				/* End of file was reached. */
	kBXML_Err_AlreadyValid	= -3,				/* Attempt to validate a previously validated database. */
	kBXML_Err_NoMemory		= -4,				/* Out of memory error. */
	kBXML_Err_BadNest		= -5,				/* Closing tag ID doesn't match current scope. */
	kBXML_Err_StackOvf		= -6,				/* Tag stack overflowed. */
	kBXML_Err_OutOfScope	= -7,				/* Closing tag without opening tag (i.e. first tag is closing tag) */
	kBXML_Err_Invalid		= -8,				/* The database is not yet validated. */
	kBXML_Err_UnknownFormat	= -9,				/* Unknown database file format or invalid structure. */	
	kBXML_Err_FileError		= -10,				/* Problem accessing database file (file not found). */
	
} BXML_Err_t;

enum {
	kBXML_DocTypeLen 	= 6,					/* Length of doc type ID (szBXML_DocType). */
	kBXML_StackSize		= 16,					/* Max tag nesting depth. */
    kBXML_MaxTagDataLen = 255,                  /* Max length (in bytes) of a tags data field. */
    kBXML_MaxDictTags   = 128,  				/* Max number of unique dictionary entries allowed (bit 7 reserved). */
    kBXML_MaxTagLen     = 32,                   /* Max length (in bytes) of a tag name. */
	kBXML_Len_Invalid	= -1,					/* An invalid tag Data Length. */
	kBXML_TagID_NA		= -1,					/* Unknown tag ID. */
	kBXML_TagID_ROOT	= 0,					/* Root tag ID is ALWAYS zero by design. */
};

/*--------------------------------------------
			   Context structure
----------------------------------------------*/
typedef struct {

	u32		iDBStart;							/* File offset to start of database (from 0). */
	u32		iFPos;								/* File offset to tag currently in scope (from 0). */
	s32		iDataLen;							/* Length of current data field. */
	s8		*sp;								/* "Tag Stack" stack pointer (-> acTagStack). */
	s8		*rp;								/* "Tag Stack" current root pointer. */
	s8		acTagStack[kBXML_StackSize];		/* Embedded tag stack. */

} BXML_Bookmark_t;

typedef struct {

	bool	bValid;								/* Signifies if the database is OK to use. */
	const StrList_t *pstVocabulary;				/* Pointer to a local vocabulary. */
	FILE	*pstFile;							/* BXML database associated with this context. */
	s8		*paiTagMap;							/* Dictionary to vocabulary cross reference. */
	BXML_Bookmark_t bm;							/* The bookmark data sub structure. */

} BXML_Context_t;


/*--------------------------------------------
				General typedefs
----------------------------------------------*/

typedef s8 BXML_Tag_t;
typedef BXML_Tag_t BXML_Path_t[];




/*--------------------------------------------
				File structures
		PACKED TO SAVE MEMORY ON DEVICE!
----------------------------------------------*/

typedef struct   {
	
	s8	acDocType[kBXML_DocTypeLen];			/* BXML doc type ID. */
	struct  {									/* Size (in bytes) of embedded dictionary. */
		u8		L;								/* Low byte. */
		u8		H;								/* High byte. */
	} wDictSize;
	u8	iDictEntries;							/* Number of dictionary entries in file. */

} BXML_Header_t;



/*--------------------------------------------
		Public function prototypes
----------------------------------------------*/
BXML_Context_t *BXML_Open(s8 *pszDBName);
void    BXML_Close(BXML_Context_t* C);
BXML_Err_t BXML_Validate(BXML_Context_t *C, const StrList_t *pstVocabulary);
s32 	BXML_GetNextTag(BXML_Context_t *C);
s32 	BXML_Traverse(BXML_Context_t *C);
s32		BXML_Descend(BXML_Context_t *C);
BXML_Err_t BXML_FindTag(BXML_Context_t *C, BXML_Tag_t iDesiredTagID);
BXML_Err_t BXML_FindPath(BXML_Context_t *C, BXML_Path_t pstPath);
bool 	BXML_ReadData(BXML_Context_t *C, s8 *buf);
void 	BXML_SetRoot(BXML_Context_t *C);
void	BXML_ResetRoot(BXML_Context_t *C);
void 	BXML_ResetDB(BXML_Context_t *C);
BXML_Bookmark_t *BXML_Bookmark(BXML_Context_t *C);
void 	BXML_FreeBookmark(BXML_Bookmark_t *N);
void	BXML_GoBookmark(BXML_Context_t *C, BXML_Bookmark_t *N);


#endif	// BXML_H
