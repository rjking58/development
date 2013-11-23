/************************************************************************************
    Filename: reader.c
    
    Project: Binary XZite Markup Language (BXML) reader.

    Description:
    
     This module implements the functionality of the BXML database language. It is
     used by the XZite family of Remotes. It supports multiple instances of BXML
     databases through the use of context structures. Opening, validation,
     navigation (tag search, path search, and iteration), and data retrieval are
     features of this module.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/05/07    ryoung      Initial implementation.
************************************************************************************/

#include "..\inc\types.h"
#include "..\inc\ascii.h"
#include "..\inc\syserr.h"
#include "..\inc\bxml.h"
#include "..\inc\strlist.h"
#include "..\inc\debug.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>




BXML_Context_t *BXML_Open(s8 *pszDBName) {

BXML_Context_t 	*C;
FILE 			*f_p;
#ifdef _LINUX_
DEBUG_SCOPE("bxml.open:");
#endif
	if ((f_p = fopen(pszDBName,"r")) == NULL) {
#ifdef _LINUX_
		debug("%s unable to open database\n", szScope);
#endif
		gErrno = kBXML_Err_FileError;
		return NULL;
	}
	if ((C = calloc(sizeof(BXML_Context_t),1)) != NULL) {
	
		C->bValid = false;											/* Until it is validated, don't allow access. */
		C->bm.sp = C->bm.acTagStack;								/* Init stack pointer. */
		C->pstFile = f_p;											/* Initialize the database file pointer. */
		C->bm.iDataLen = kBXML_Len_Invalid;							/* Set data length as invalid in case of a read attempt. */
	}
	return C;
}
	

/************************************************************************************
	Function: BXML_Validate()
	
	Description: Validate the specified BXML database by creating the dictionary to
				 vocabulary cross reference, reading all tags, checking for correct
				 tag nesting and opening the root scope.

    Inputs: C = pointer to a BXML context structure.
    		pstVocabulary = pointer to local vocabulary to reference against.

   Returns: kBXML_Err_None if OK, otherwise a BXML_Err_t error code.
	
************************************************************************************/
BXML_Err_t BXML_Validate(BXML_Context_t *C, const StrList_t *pstVocabulary) {

#ifdef _LINUX_
DEBUG_SCOPE("bxml.validate:");
#endif
	char	*pszPtr, *buf =NULL;
	u32 	i, idx;
	s32		iTagID;
	u32		iDataLen;
	u32		iDictEntries;
	u32		iDictSize;
	BXML_Header_t	stDBHeader;


    /* Create a dictionary to vocabulary cross reference map. */

	if (C->bValid) {												/* If already validated... */

		return kBXML_Err_AlreadyValid;								/* Return with failure. */
	}	

	fread(&stDBHeader, sizeof(stDBHeader), 1, C->pstFile);			/* Read database header. */
	if (strncmp(stDBHeader.acDocType, szBXML_DocType, sizeof(stDBHeader.acDocType))) {
#ifdef _LINUX_		
		debug("%s unknown database file format\n", szScope);		/* If we don't recognize the doc type... */
#endif
		return kBXML_Err_UnknownFormat;
	}
	iDictEntries = stDBHeader.iDictEntries;
	iDictSize = (stDBHeader.wDictSize.L & 0xff) | ((stDBHeader.wDictSize.H & 0xff << 8) & 0xff);
#ifdef _LINUX_
	debug("%s Dictionary has %d entries [%d bytes]\n", szScope, iDictEntries, iDictSize);
#endif
	if ((C->paiTagMap = malloc(iDictEntries)) != NULL) {			/* Allocate space for cross reference table. */

		for (i = 0;	i < iDictEntries; i++) {
			
			C->paiTagMap[i] = kBXML_TagID_NA;						/* Reset tag cross reference. */
		}
	    if ((buf = malloc(iDictSize)) != NULL) {
			fread(buf, iDictSize, 1, C->pstFile);					/* Read database dictionary. */
			pszPtr = buf;
			C->pstVocabulary = pstVocabulary;						/* Store pointer to vocabulary. */
			for (i = 0; i < iDictEntries; i++) {
		
				//if ((idx = StrList_Find(pszPtr, C->pstVocabulary)) == kFind_NotFound) {
                if ((idx = StrList_Find_by_list(pszPtr, 
                                                (void *)(C->pstVocabulary->pszString),
                                                C->pstVocabulary->iEntries )) == kFind_NotFound) {
#ifdef _LINUX_	
                
					debug("%s %d:%s:{NA}\n", szScope, i, pszPtr);
#else
                
#endif
				}
				else {
				
					C->paiTagMap[i] = idx;							/* Map dictionary tag ID to vocabulary tag ID. */
#ifdef _LINUX_
					debug("%s %d:%s->%d\n",szScope, i, pszPtr, idx);
#endif
				}
				while(*pszPtr++);									/* Scan to next entry in dictionary. */
			}
		}
	}
	if (!C->paiTagMap || !buf) {									/* If we failed to allocate both memory blocks... */
#ifdef _LINUX_
		debug("%s out of memory\n", szScope);
#endif
		BXML_Close(C);												/* Free the context. */
		return kBXML_Err_NoMemory;
	}
	/* We created the cross reference, now validate the database structure. */

	C->bm.iFPos = ftell(C->pstFile);								/* Set initial database file position. */
	C->bm.iDBStart = C->bm.iFPos;									/* Save start of database file position. */
	while (true) {                                              	
	                                                            	
		if ((iTagID = fgetc(C->pstFile)) != EOF) {					/* Read next tag. */
		                                                        	
			if (iTagID & kmBXML_TagFlag_Close) {					/* If it's a closing tag... */
                                                                	
				i = iTagID & kmBXML_TagData;	                	/* Keep only ID. */
                if (C->bm.sp <= C->bm.rp) {							/* If out of scope... */
#ifdef _LINUX_
					debug("%s out of scope <%d>\n", szScope, C->pstVocabulary->pszString[C->paiTagMap[i]]);             
#endif
					return kBXML_Err_OutOfScope;
				}
				else if (i != *(--C->bm.sp)) {                      /* If not correctly nested... */
#ifdef _LINUX_
#if DEBUG
                    debug("\n%s trying to close </%s> inside <%s>\n", szScope, C->pstVocabulary->pszString[C->paiTagMap[i]], C->pstVocabulary->pszString[C->paiTagMap[*C->bm.sp]]);
#endif
#endif
					return kBXML_Err_BadNest;
                }
#ifdef _LINUX_
#ifdef DEBUG
				debug("</%s>", C->pstVocabulary->pszString[C->paiTagMap[i]]);
#endif
#endif
				iDataLen = 0;
			}
			else {
				
				if (C->bm.sp >= &C->bm.acTagStack[kBXML_StackSize-1]) {
				
#ifdef _LINUX_
    				debug("\n%s tag stack overflow @%d\n", szScope, kBXML_StackSize);
#endif
					return kBXML_Err_StackOvf;
				}
                *(C->bm.sp++) = iTagID;                             /* Push tag ID on stack. */
#ifdef _LINUX_
#ifdef DEBUG
				debug("<%s>", C->pstVocabulary->pszString[C->paiTagMap[iTagID]]);           	
#endif
#endif
				if ((iDataLen = fgetc(C->pstFile)) != EOF) {		/* Read data length. */
#ifdef _LINUX_
#ifdef DEBUG
					for (i = 0; i < iDataLen; i++) {
						debug("%c",fgetc(C->pstFile));
					}
#endif
#endif


					fseek(C->pstFile, iDataLen, SEEK_CUR);			/* Skip data field. */
				}
				else break;
			}
#ifdef _LINUX_
#ifdef DEBUG
			if (!iDataLen) debug("\n");
#endif
#endif
		}
		else break;
	}

    if( buf )
    {
        free( buf );
    }

	if (C->bm.sp != &C->bm.acTagStack[0]) {							/* If scope wasn't properly closed... */
		
		return kBXML_Err_EOF;										/* Report end of file! */
	}
	fseek(C->pstFile, C->bm.iFPos, SEEK_SET);             			/* Seek to start of database. */
	BXML_ResetDB(C);												/* Reset current database scope. */
    C->bValid = true;
	return kBXML_Err_None;
}			


	
/************************************************************************************
	Function: BXML_Close()
	
	Description: Close the specified BXML context and associated database. This is
				 done by releasing allocated memory and closing the database file.

    Inputs: C = pointer to a BXML context structure.
   Returns: None.
	
************************************************************************************/
void BXML_Close(BXML_Context_t* C) {

	if (C->paiTagMap) free(C->paiTagMap);							/* Release cross reference. */
	fclose(C->pstFile);												/* Close database file. */
	free(C);														/* Release context structure. */
}




/************************************************************************************
	Function: BXML_SetRoot()
	
	Description: Make the current tag scope the root of the structure to limit
				 further searches or iterators within that scope. This will prevent
				 a search from proceeding to the end of the database if the tag ID
				 is not found anywhere. 

    Inputs: C = pointer to a BXML context structure.
   Returns: None.
	
************************************************************************************/

void BXML_SetRoot(BXML_Context_t *C) {

	C->bm.rp = C->bm.sp - 1;										/* Set root pointer to current scope. */
}


/************************************************************************************
	Function: BXML_ResetRoot()
	
	Description: Reset the tag stack root pointer to the beginning of the stack.

    Inputs: C = pointer to a BXML context structure.
   Returns: None.
	
************************************************************************************/

void BXML_ResetRoot(BXML_Context_t *C) {

	C->bm.rp = C->bm.acTagStack;									/* Reset the root pointer. */
}


/************************************************************************************
	Function: BXML_ResetDB()
	
	Description: Reset the database and open the root scope. This will reset the
				 database file position, stuff the root tag at the first stack
				 position, set the stack pointer to just after the root tag so
				 we are open and reset the root pointer.

    Inputs: C = pointer to a BXML context structure.
   Returns: None.
	
************************************************************************************/

void BXML_ResetDB(BXML_Context_t *C) {

    C->bm.acTagStack[0] = C->paiTagMap[kBXML_TagID_ROOT];			/* Copy root scope ID to root of stack... */
	C->bm.sp = &C->bm.acTagStack[1];								/* Put stack pointer . */
	C->bm.iFPos = C->bm.iDBStart;									/* Reset file position to start of database. */
	C->bm.iDataLen = kBXML_Len_Invalid;								/* Set data length as invalid in case of a read attempt. */
	BXML_ResetRoot(C);												/* Reset the tag stack root pointer. */
}



/************************************************************************************
	Function: BXML_Bookmark()
	
	Description: Bookmark the current location in the database for later use. This
				 provides a quick resume mechanism without the need for the tag
				 searching process to be repeated. A bookmark allocates memory that
				 should be freed via BXML_FreeBookmark() after the caller is done
				 with it.

    Inputs: C = pointer to a BXML context structure.
   Returns: BXML_Bookmark_t* = bookmark pointer to be used with BXML_GoBookmark().
	
************************************************************************************/

BXML_Bookmark_t *BXML_Bookmark(BXML_Context_t *C) {
BXML_Bookmark_t *N;

	N = malloc(sizeof(BXML_Bookmark_t));
	memcpy(N, &C->bm, sizeof(BXML_Bookmark_t));	
	return N;	
}


/************************************************************************************
	Function: BXML_FreeBookmark()
	
	Description: Release the specified Bookmark resource. This will release the
				 memory that was allocated for the bookmark. After releasing a
				 bookmark, the application should not attempt to use it.

    Inputs: N = pointer to a BXML_Bookmark_t resource.
   Returns: N/A
	
************************************************************************************/

void BXML_FreeBookmark(BXML_Bookmark_t *N) {

	free(N);
}


/************************************************************************************
	Function: BXML_GoBookmark()
	
	Description: 

    Inputs: C = pointer to a BXML context structure and a bookmark reference.
   Returns: None.
	
************************************************************************************/

void BXML_GoBookmark(BXML_Context_t *C, BXML_Bookmark_t *N) {

	memcpy(&C->bm, N, sizeof(BXML_Bookmark_t));
}

			
/************************************************************************************
	Function: BXML_GetCurTag()
	
 Description: Return the current tag ID from the database translated to our local
 			  vocabulary (passed when database was validated).

    Inputs: C = pointer to a BXML context structure.
   
   Returns: s32 = current local Tag ID if successful or a BXML_Err_t error code.
	C->bm.iDataLen = length of tags data field if no error occured.

************************************************************************************/
s32 BXML_GetCurTag(BXML_Context_t *C) {
#ifdef _LINUX_
DEBUG_SCOPE("bxml.getcurtag:");
#endif	
	s32		iTagID;
	u32		len;
	bool	bCloseFlag;
	                                                            	

	if (C->bValid) {													/* If database has been validated... */
                                                                    	
		fseek(C->pstFile, C->bm.iFPos, SEEK_SET);               		/* Seek to current tag. */
#ifdef _LINUX_
		debug("%s seeking to 0x%04x\n", szScope, ftell(C->pstFile));       	
#endif                                                                    	
		if ((iTagID = fgetc(C->pstFile)) != EOF) {						/* Read tag. */
#ifdef _LINUX_
			debug("%s read tag <%d>\n", szScope, iTagID);
#endif

#ifdef DEBUG
			bCloseFlag = (iTagID & kmBXML_TagFlag_Close);				/* Extract close flag. */
#endif
			iTagID = C->paiTagMap[iTagID & kmBXML_TagData];				/* Cross reference to our vocabulary. */

#ifdef DEBUG
			if (bCloseFlag) {											/* If it's a closing tag... */

#ifdef _LINUX_
				debug("%s closing tag <%s> not expected\n", szScope, C->pstVocabulary->pszString[iTagID]);
#endif
				return kBXML_Err_OutOfScope;
			}
			else
#endif
			{
				if ((len = fgetc(C->pstFile)) != EOF) {					/* Read data length. */

					C->bm.iDataLen = len;								/* Save data field length. */
				}
				else C->bm.iDataLen = kBXML_Len_Invalid;				/* Invalidate length field. */
				return iTagID;
			}
		}
		else return kBXML_Err_EOF;										/* EOF trying to read tag! */
	}
	else return kBXML_Err_Invalid;
}			


/************************************************************************************
	Function: BXML_ReadData()
	
	Description: Read the data field at the current database position. This function
				 will read the data field associated with the current tag scope into
				 a buffer provided by the caller.

    Inputs: C = pointer to a BXML context structure.

   Returns: true if successful, false if not.
	
************************************************************************************/

bool BXML_ReadData(BXML_Context_t *C, s8 *buf) {
u32	i;


	if (C->bValid) {

		if (C->bm.iDataLen >= 0) {										/* If last operation succeeded... */

            fseek(C->pstFile, C->bm.iFPos+2, SEEK_SET);             	/* Seek to data field, skip tag and length bytes. */
			i = fread(buf, sizeof(s8), C->bm.iDataLen, C->pstFile);		/* Read data field (0 is valid size). */
			buf[i] = kASCII_NUL;										/* Terminate the data field. */
			if (i == C->bm.iDataLen) return true;						/* If successful... */
		}
	}                                                               	
	return false;														/* Indicate failure. */
}



/************************************************************************************
	Function: BXML_Traverse()
	
	Description: Scan to and return the next known tag ID from the database in
				 our local vocabulary (mapped to internal ID codes). Tag ID's that
				 are not in our vocabulary are skipped as are closing tags.

    Inputs: C = pointer to a BXML context structure.
   
   Returns: s32 = local Tag ID if successful or a BXML_Err_t error code (< 0).
	C->bm.iDataLen = length of tags data field if no error occured.

************************************************************************************/
s32 BXML_Traverse(BXML_Context_t *C) {
#ifdef _LINUX_
DEBUG_SCOPE("bxml.traverse:");
#endif	
	u32		len;
	                                                            	

	if (C->bValid) {													/* If database has been validated... */
                                                                    	
		fseek(C->pstFile, C->bm.iFPos+1, SEEK_SET);               		/* Seek to current tag's data length. */
#ifdef _LINUX_

		debug("%s seeking to 0x%04x\n", szScope, ftell(C->pstFile));       	
#endif                                                                    	
		if ((len = fgetc(C->pstFile)) == EOF) {							/* Read data length. */
                                                                    	
			return kBXML_Err_EOF;										/* If we hit the end of file... */
		}
		else {

			fseek(C->pstFile, len, SEEK_CUR);							/* Skip over data field. */
			return BXML_GetNextTag(C);									/* Return the next known tag. */
		}                                                           	
	}
	else return kBXML_Err_Invalid;
}



s32 BXML_GetNextTag(BXML_Context_t *C) {
#ifdef _LINUX_
DEBUG_SCOPE("bxml.getnexttag:");
#endif	
	s32		iTagID;
	u32		len;
	bool	bCloseFlag;


	if (C->bValid) {													/* If database has been validated... */

		while (true) {
		
			if ((iTagID = fgetc(C->pstFile)) != EOF) {					/* Read next tag. */
			
				bCloseFlag = (iTagID & kmBXML_TagFlag_Close);			/* Extract close flag. */
				iTagID = C->paiTagMap[iTagID & kmBXML_TagData];			/* Cross reference to our vocabulary. */
#ifdef _LINUX_
				debug("%s read tag <%s>\n", szScope, C->pstVocabulary->pszString[iTagID]);
#endif
				if (bCloseFlag) {										/* If it's a closing tag... */

#ifdef _LINUX_
					debug("%s popping <%s>\n", szScope, C->pstVocabulary->pszString[iTagID]);
#endif

	                if (--C->bm.sp <= C->bm.rp) {						/* If out of scope... */
	
#ifdef _LINUX_
						debug("%s out of scope <%d>\n", szScope, iTagID);             
#endif
//						C->bm.sp++;										/* Keep in scope! */
						return kBXML_Err_OutOfScope;
	                }
				}
				else {
#ifdef TAGSTACK_CHECK
					if (C->bm.sp >= &C->bm.acTagStack[kBXML_StackSize-1]) {	/* If tag stack overflowed... */
#ifdef _LINUX_
	    				debug("%s tag stack nesting overflow @ <%d>\n", szScope, iTagID);
#endif
						return kBXML_Err_StackOvf;
					}
#endif

#ifdef _LINUX_
					debug("%s pushing <%s>\n", szScope, C->pstVocabulary->pszString[iTagID]);
#endif
	                *(C->bm.sp++) = iTagID;                            	/* Push tag ID on stack. */
					if (iTagID == kBXML_TagID_NA) {						/* If tag isn't in our vocabulary... */

						if ((len = fgetc(C->pstFile)) != EOF) {			/* Read data length. */
	
							fseek(C->pstFile, len, SEEK_CUR);			/* Skip data field. */
						}
						else return kBXML_Err_EOF;						/* Report end of file! */
					}
					else {

#ifdef _LINUX_
						debug("%s save location\n", szScope);
#endif
						C->bm.iFPos = ftell(C->pstFile)-1;				/* Save location of tag ID. */
						if ((len = fgetc(C->pstFile)) != EOF) {			/* Read data length. */
	
							C->bm.iDataLen = len;						/* Save data field length. */
						}
						else C->bm.iDataLen = kBXML_Len_Invalid;		/* Invalidate length field. */
						break;											/* Let's go home. */
					}
				}
			}
			else return kBXML_Err_EOF;									/* EOF trying to read tag! */
		}
		return iTagID;													/* Success! */
	}
	else return kBXML_Err_Invalid;
}			


/************************************************************************************
	Function: BXML_Descend()
	
	Description: Skip to the end of the current tag scope and return the next known
				 tag ID from the database in our local vocabulary (mapped to internal
				 ID codes). Tag ID's that are not in our vocabulary are skipped.
				 This function provides the ability to iterate through tags at the
				 same level in the database.

    Inputs: C = pointer to a BXML context structure.
   
   Returns: s32 = local Tag ID if successful or a BXML_Err_t error code (< 0).
	C->bm.iDataLen = length of tags data field if no error occured.

************************************************************************************/
s32 BXML_Descend(BXML_Context_t *C) {
#ifdef _LINUX_
DEBUG_SCOPE("bxml.descend:");
#endif	
	s32		iTagID;
	s8		*save_scope;
	u32		len;
	                                                            	

	if (C->bValid) {													/* If database has been validated... */
                                                                    	
		save_scope = C->bm.rp;											/* Save the current scope. */
		BXML_SetRoot(C);												/* Limit scope to current tag. */
		while ((iTagID = BXML_Traverse(C)) != kBXML_Err_OutOfScope) {
		
			if (iTagID < 0) {											/* If no errors, keep going. */
				
				C->bm.rp = save_scope;									/* Restore original scope. */
				return (BXML_Err_t)iTagID;								/* If error, return error code. */
			}
		}
		C->bm.rp = save_scope;											/* Restore original scope. */
		return BXML_GetNextTag(C);										/* Return the next known tag. */
	}
	return kBXML_Err_Invalid;
}			


/************************************************************************************
	Function: BXML_FindTag()
	
	Description: Search for a local (original mapped to local vocabulary) tag ID
				 within the current root scope of the database. If it is found, the
				 tag ID is returned and the BXML_Context_t::bm.iDataLen variable is set
				 to the length of the tag's data field (0 if it was a closing tag).
				 The caller may use the length value to allocate memory for the data
				 field before a call to BXML_ReadData().
				 
				 If the tag was not found, an error code of type BXML_Err_t is
				 returned. 

    Inputs: C = pointer to a BXML context structure.

   Returns: A BXML_Err_t code (BXML_Err_None if successful).
	C->bm.iDataLen = length of tags data field if no error occured.
	
************************************************************************************/
BXML_Err_t BXML_FindTag(BXML_Context_t *C, s8 iDesiredTagID) {
	
	s32		iTagID;

	                                                            	
	if (C->bValid && (iDesiredTagID < C->pstVocabulary->iEntries)) {	/* If database and tag ID are valid... */

		while ((iTagID = BXML_Traverse(C)) != iDesiredTagID) {
		
			if (iTagID < 0) {
				
				return (BXML_Err_t)iTagID;								/* If error, return error code. */
			}
		}
		return kBXML_Err_None;											/* Signal success! */
	}
	else return kBXML_Err_Invalid;
}		


/************************************************************************************
	Function: BXML_FindPath()
	
	Description: Search for a local (original mapped to local vocabulary) tag ID
				 within the current root scope of the database. If it is found, the
				 tag ID is returned and the BXML_Context_t::bm.iDataLen variable is set
				 to the length of the tag's data field (0 if it was a closing tag).
				 The caller may use the length value to allocate memory for the data
				 field before a call to BXML_ReadData().
				 
				 If the tag was not found, an error code of type BXML_Err_t is
				 returned. 

    Inputs: C = pointer to a BXML context structure.

   Returns: A BXML_Err_t code (BXML_Err_None if successful).
	C->bm.iDataLen = length of last tags data field if no error occured.
	
************************************************************************************/
BXML_Err_t BXML_FindPath(BXML_Context_t *C, BXML_Path_t pstPath) {
	
	s32		iFindID, iTagID;
	u32		i;
	
		                                                            	
	if (C->bValid) {											/* If database is valid... */

//		BXML_ResetRoot(C);

/*[rdy] Check if current path is the root of the desired path. */
//		for (i = 0; i < (C->bm.sp-
		
		while (iFindID = *pstPath++) {
			
			if (iFindID < C->pstVocabulary->iEntries) {
#ifdef _LINUX_
				debug("%s/", C->pstVocabulary->pszString[iFindID]);	
#endif
			}
			else {
#ifdef _LINUX_
                debug("%d/", iFindID);	
#endif
            }
			if ((iTagID = BXML_FindTag(C, iFindID)) != kBXML_Err_None) {

				break;
			}
		}
		return (BXML_Err_t)iTagID;								/* If error, return error code. */
	}
	else return kBXML_Err_Invalid;
}		


