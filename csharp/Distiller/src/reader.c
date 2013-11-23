/************************************************************************************
    Filename: reader.c
    
    Project: XZite binary XML reader.

    Description:
    
     This utility will read a binary XZite configuration file and allow a user to
     extract fields from it. It is the counterpart to the XML distiller for XZite.
     
	 This utility will search through fields using their tag ID's and looking up the
	 tag names from the pre-built dictionary stored after the file header.


History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/05/07    ryoung      Initial implementation.
************************************************************************************/

#include "types.h"
#include "ascii.h"
#include "syserr.h"
#include "bxml.h"
#include "strlist.h"
#include "debug.h"
#include "rgetopt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*--------------------------------------------
			    Local constants
----------------------------------------------*/

enum {
	kTagID_root = 0,
	kTagID_home,
	kTagID_activities,
	kTagID_activity,
	kTagID_macro,
	kTagID_rgb565,
	kTagID_data,
	kTagID_name8,
	kTagID_name16,
	kTagID_devices,
	kTagID_device,
	kTagID_prefix,
	kTagID_executor,
	kTagID_icondef,
	kTagID_iconref,	
	kTagID_width,
	kTagID_height,
	kTagID_brand,
	kTagID_codeset,
	kTagID_model,
	kTagID_favorites,	
    kTagID_favorite,
	kTagID_profile,
	kTagID_string,
	kTagID_digit,
	kTagID_trigger,
	kTagID_keymap,
	kTagID_functions,
	kTagCount
};

const StrList_t stVocabulary = {
	kTagCount,
	"???",				/* pszString[-1] */
	{
		"root",
		"home",
		"activities",
		"activity",
		"macro",
		"rgb565",
		"data",
		"name8",
		"name16",
		"devices",
		"device",
		"prefix",
		"executor",
		"icondef",
		"iconref",	
		"width",
		"height",
		"brand",
		"codeset",
		"model",	
		"favorites",	
        "favorite",    
		"profile",
		"string",		
		"digit",
		"trigger",
		"keymap",
		"functions",
	}
};

/* These are the tags in our database that are links to external database files (folders). */

const BXML_Tag_t DB_Folders[] = {
	kTagID_activities,
	kTagID_devices
};


/* Private functions. */

s32 OpenDB(s8 *db, bool bInteractive);


bool gbInteractive = false;

static const optStruct_t optionList[] = {
   	{'d', false, (char**)&gbDebugOutput},
   	{'i', false, (char**)&gbInteractive},
};
#define kNumCmdOptions (sizeof(optionList)/4)   /* Number of command line options. */



int main(int argc, char **argv) {

	Err_t   iErr;
	
	
    printf("\nXZite config file BXML reader. (CYGWIN_NT-5.1, ryoung 1.5.22(0.156/4/2) 2006-11-13 17:01\n\n");

    iErr = GetOpt(argc, argv, optionList, kNumCmdOptions);
    if (iErr) {
    	
        exit(kErr_Bad_Parm);
    }
	iErr = OpenDB(argv[1], gbInteractive);
	exit(iErr);
}



s32 OpenDB(s8 *db, bool bInteractive) {

	Err_t   iErr;
	BXML_Context_t *C;
	u32 	n;
	s32		i;
	s8		*p;
	s8		*buf;
	BXML_Path_t	list = {kTagID_devices, kTagID_device, kTagID_model, kTagID_name8, 0};
	BXML_Path_t	list2 = {kTagID_devices, kTagID_device, kTagID_model, kTagID_name8, 0};
	BXML_Bookmark_t *bm = 0;
	

	if ((C = BXML_Open(db)) == NULL) {						/* Open the database for access. */
		
		return gErrno;										/* BXML_Open() returns the error in gErrno. */
	}
	if ((iErr = BXML_Validate(C, &stVocabulary)) < 0) {
		
		printf("error: failed to validate database (%d)\n", iErr);
		return iErr;
	}

	while (true) {

		if (bInteractive) {
			
			debug("sp:%d rp:%d pos:%04x\n", C->bm.sp - C->bm.acTagStack, C->bm.rp - C->bm.acTagStack, ftell(C->pstFile));
			printf("%s> ", stVocabulary.pszString[(C->bm.sp == C->bm.acTagStack)?0:*(C->bm.sp-1)]);
			fscanf(stdin, "%hhd", &list[0]);
			if (list[0] == 30) {
				
				BXML_SetRoot(C);
				printf("set root:<%s>\n", stVocabulary.pszString[(C->bm.sp == C->bm.acTagStack)?0:*(C->bm.sp-1)]);
				continue;
			}
			else if (list[0] == 40) {
				
				BXML_ResetDB(C);
				printf("reset DB>\n");
				continue;
			}
			else if (list[0] == 50) {
			
				if ((i = BXML_Traverse(C)) > 0) {
					
					if (C->bm.iDataLen) {
	
						buf = malloc(C->bm.iDataLen);
						if (BXML_ReadData(C, buf) == false) {
							printf("failed to read tag %s\n", stVocabulary.pszString[i]);
						}
						else if (i == kTagID_devices) {
						
							buf[C->bm.iDataLen] = '\0';			/* Terminate file name string. */
							debug("opening %s\n", buf);
							OpenDB(buf, true);
						}
						else printf("%s/%s   [tagID [%d]]\n",stVocabulary.pszString[i], buf, i);
						free(buf);
					}
					continue;
				}
				else return kBXML_Err_None;
			}
			else if (list[0] == 60) {
			
				if (bm) BXML_GoBookmark(C, bm);
				BXML_SetRoot(C);
				i = BXML_GetCurTag(C);
				do {					
					if (C->bm.iDataLen) {
	
						buf = malloc(C->bm.iDataLen+1);			/* +1 for possible string terminator. */
						if (BXML_ReadData(C, buf) == false) {
							printf("failed to read tag %s\n", stVocabulary.pszString[i]);
						}
						else if (i == kTagID_devices) {
						
							buf[C->bm.iDataLen] = '\0';			/* Terminate file name string. */
							debug("opening %s\n", buf);
							OpenDB(buf, false);
						}
						else {
							
							for (p = C->bm.rp; p < C->bm.sp; p++) {
								printf("%s/",stVocabulary.pszString[*p]);
							}
							printf("%s\n", buf);
						}
						free(buf);
					}
					else {
						for (p = C->bm.rp; p < C->bm.sp; p++) {
							printf("%s/",stVocabulary.pszString[*p]);
						}
						putc('\n', stdout);
					}						
				} while ((i = BXML_Traverse(C)) > 0);
				continue;
			}
			else if (list[0] == 70) {

				bm = BXML_Bookmark(C);
			}
			else if (list[0] == 80) {

				if ((i = BXML_Descend(C)) > 0) {
					
					if (C->bm.iDataLen) {
	
						buf = malloc(C->bm.iDataLen);
						if (BXML_ReadData(C, buf) == false) {
							printf("failed to read tag %s\n", stVocabulary.pszString[i]);
						}
						else if (i == kTagID_devices) {
						
							buf[C->bm.iDataLen] = '\0';			/* Terminate file name string. */
							debug("opening %s\n", buf);
							OpenDB(buf, true);
						}
						else printf("%s/%s\n",stVocabulary.pszString[i], buf);
						free(buf);
					}
					continue;
				}
				else if (i == kBXML_Err_OutOfScope) {
					
					printf("out of scope\n");
				}
				return kErr_None;
			}
			else if (list[0] == 90) {

				return kErr_None;
			}
			else {		
		
				list[1] = 0;
			}
#if 1
			BXML_FindTag(C, list[0]);
			if (C->bm.iDataLen) {
	
				buf = malloc(C->bm.iDataLen);
				if (BXML_ReadData(C, buf) == false) {
					printf("failed to read tag data\n");
				}
				printf("%s\n", buf);
				free(buf);
			}		
#endif

		}
		else {
						
			if (bm) BXML_GoBookmark(C, bm);
			BXML_SetRoot(C);
			i = BXML_GetCurTag(C);
			do {					
				if (C->bm.iDataLen) {
	
					buf = malloc(C->bm.iDataLen+1);			/* +1 for possible string terminator. */
					if (BXML_ReadData(C, buf) == false) {
						printf("failed to read tag %s\n", stVocabulary.pszString[i]);
					}
					else {
						
						for (p = C->bm.rp; p < C->bm.sp; p++) {
							printf("%s/",stVocabulary.pszString[*p]);
						}
						printf("%s\n", buf);
						if (i == kTagID_devices) {
					
							buf[C->bm.iDataLen] = '\0';			/* Terminate file name string. */
							debug("opening %s\n", buf);
							OpenDB(buf, false);
						}
					}
					free(buf);
				}
				else {
					for (p = C->bm.rp; p < C->bm.sp; p++) {
						printf("%s/",stVocabulary.pszString[*p]);
					}
					putc('\n', stdout);
				}						
			} while ((i = BXML_Traverse(C)) > 0);
		}
//		printf("bxml.findpath: returned %d\n", BXML_FindPath(C, list));
#if 0
		for (n = 0; list[n]; n++) {
			
			if (list[n] < stVocabulary.iEntries) {

				debug("searching for %s\n", stVocabulary.pszString[list[n]]);	
			}
			else debug("searching for %d\n", list[n]);	
			if ((i = BXML_FindTag(C, list[n])) == kBXML_Err_None) {
				
//				printf("found %s:%d bytes\n", stVocabulary.pszString[list[n]],i);
#if 0
				if (C->bm.iDataLen) {

					buf = malloc(C->bm.iDataLen);
					if (BXML_ReadData(C, buf) == false) {
						printf("failed to read tag %s\n", stVocabulary.pszString[list[n]]);
					}
					printf("%s:%s\n",stVocabulary.pszString[list[n]], buf);
					free(buf);
				}
#endif
			}
			else {
				
				if (list[n] < stVocabulary.iEntries) {

					printf("<%s> not found:%d\n", stVocabulary.pszString[list[n]], i);
				}
				else printf("<%d> not found:%d\n", list[n], i);
			}
		}
#endif
		if (!bInteractive) break;
	}
	BXML_Close(C);
}

