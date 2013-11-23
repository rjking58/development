/************************************************************************************
    Filename: distiller.c
    
    Project: XZite XML distiller.

    Description:
    
     This utility will take an XZite configuration file in ASCII XML format and
     create a binary representation of it for use in the remote firmware. It does not
     support all XML features such as attributes nor the standard XML header. This
     format allows a remote with older firmware to continue to work with a newer
     configuration file with unknown tags by simply ignoring the unknown data fields.
     The binary format also takes up considerably less space in our serial flash.
     
     The general idea is to scan the input file for tags and build a dictionary
     that gets stored at the beginning of the output file just after the header.
     Tags are converted into indexes into the dictionary with a following data field
     length byte, optional data and closing or opening tag. Tags may be nested but
     must be closed in LIFO order.
     
     For example, the following is properly nested:
     
     	<devices>My devices				   
     		<devicetype>TV</devicetype>
     	</devices>
     		
     The following is not legal nesting:
     			  
     	<devices>My devices				   
     		<devicetype>TV</devices>    	<-- Error, closing </devices> inside
     	</devicetype>							of <devicetype>.
     
	 Tag names are arbitrarily limited to 32 characters to prevent the firmware data
	 from being unneccesarily bloated. Tag data fields are limited to 255 bytes. To
	 support data fields of greater length, the firmware may handle a specific tags
	 data by simply adding it to the end of previous data. This is possible since it
	 is the firmware designer that implements the functionality of each tag name.
	 Simply use a <starttag>,<datatag>,<endtag> mechanism. Any amount of data may
	 therefore be collected within <starttag> and <endtag>.

History:

 Date       Author      Description
------------------------------------------------------------------------------------
02/01/07    ryoung      Initial implementation.
************************************************************************************/

#include "types.h"
#include "ascii.h"
#include "rgetopt.h"
#include "strlist.h"
#include "bxml.h"
#include "debug.h"
#include "syserr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>



enum {

    kWorkStringSize     = 255,                  /* Size of the work string buffer. */
};


static const char ShortHelpMsg[] =

    "Synopsis: d <options>\n"
    "\nThis utility translates an XZite configuration file from ASCII XML format\n"
    "into a binary format suitable for use with the XZite remote firmware.\n\n"
    "\t-?\tShow detailed description.\n"
    "\t-i\tSpecifies the input filename (default is stdin).\n"
    "\t-o\tSpecifies the output filename (default is stdout).\n"
    "\t-l\tTells the parser to allow multi-line data past CR/LF in data fields.\n";

static const char UsageMsg[] =

    "    This utility will take an XZite configuration file in ASCII XML format and      \n"
    "    create a binary representation of it for use in the remote firmware. It does not\n"
    "    support all XML features such as attributes nor the standard XML header. This   \n"
    "    format allows a remote with older firmware to continue to work with a newer     \n"
    "    configuration file with unknown tags by simply ignoring the unknown data fields.\n"
    "    The binary format also takes up considerably less space in our serial flash.    \n"
    "\n"
    "    The general idea is to scan the input file for tags and build a dictionary      \n"
    "    that gets stored at the beginning of the output file just after the header.     \n"
    "    Tags are converted into indexes into the dictionary with a following data field \n"
	"    length byte, optional data and closing or opening tag. Tags may be nested but   \n"
    "    must be closed in LIFO order.\n"
    "\n"
    "    For example, the following is properly nested:\n"
    "\n"
    "    	<devices>My devices\n"
    "    		<devicetype>TV</devicetype>\n"
    "    	</devices>\n"
    "\n"
    "    The following is not legal nesting:\n"
    "\n"
    "    	<devices>My devices\n"
    "    		<devicetype>TV</devices>    	<-- Error, closing </devices> inside\n"
    "    	</devicetype>							of <devicetype>.\n"
	"\n"
    "    Tag names are arbitrarily limited to 32 characters to prevent the firmware data\n"
    "    from being unneccesarily bloated. Tag data fields are limited to 255 bytes. To\n" 
    "    support data fields of greater length, the firmware may handle a specific tags\n" 
    "    data by simply adding it to the end of previous data. This is possible since it\n"
    "    is the firmware designer that implements the functionality of each tag name.\n"   
    "    Simply use a <starttag>,<datatag>,<endtag> mechanism. Any amount of data may\n"   
    "    therefore be collected within <starttag> and <endtag>.\n";                         
        

typedef enum {
	
	kCloseType_None = 0,
	kCloseType_Norm,
	kCloseType_EmptyTag,
	kCloseType_Comment
} CloseType_t;

/*--------------------------------------------
        		Globals
----------------------------------------------*/
CloseType_t geCloseTag = kCloseType_None;

/*--------------------------------------------
        Local function prototypes.
----------------------------------------------*/

static char *GetToken(char *pszStrBuf, FILE *infile /*, CloseType_t *eCloseTagStatus*/);


    

int main(int argc, char **argv) {

int 	i, idx, y;
int     *sp, *stack_top_p, *stack;         		/* Tag stack pointer. */
FILE 	*fs, *fd;
char 	str[kWorkStringSize+1];				    /* +1 for added line terminator. */
char    buf[kBXML_MaxTagDataLen];               /* Temp buffer for Tag data information. */
char	*pszTok;
StrList_t *pstTags;
int     c;
int		len, dict_len = 0;
int		avail;
Err_t   iErr;

const char  *szInfile_p = NULL;                 
const char  *szOutfile_p = NULL;                
bool        bShowUsage = false;
bool		bAllowCRLF = false;

const optStruct_t optionList[] = {
    {'?', false, (char**)&bShowUsage},
    {'d', false, (char**)&gbDebugOutput},
	{'l', false, (char**)&bAllowCRLF},
    {'i', true,  (char**)&szInfile_p},
    {'o', true,  (char**)&szOutfile_p},
};

#define kNumCmdOptions (sizeof(optionList)/4)   /* Number of command line options. */



    fprintf(stderr,"\nXZite config file XML distiller. (CYGWIN_NT-5.1, ryoung 1.5.22(0.156/4/2) 2006-11-13 17:01\n\n");
	
    /* Parse options and show usage if an error occurs. */

    iErr = GetOpt(argc, argv, optionList, kNumCmdOptions);
    if (iErr) {
    	
        fprintf(stderr,"%s",ShortHelpMsg);
        exit(kErr_Bad_Parm);
    }
    else if (bShowUsage) {

        fprintf(stderr,"%s",UsageMsg);
        exit(kErr_None);
    }

    /* Open the input and output streams. */
    
    if (szInfile_p) {

    	if ((fs = fopen(szInfile_p,"r")) == NULL) {
    		
    		perror(szInfile_p);
    		exit(-1);
    	}
    }
    else {
        
        fs = stdin;
    }
	if ((fd = fopen(szOutfile_p,"w+b")) == NULL) {

		fd = stdout;		
	}

    /* Initialize the dictionary. */

    stack = calloc(kBXML_StackSize, sizeof(sp));				/* Get space for tag stack to handle nesting. */
	sp = stack;													/* Init our stack pointer. */
	pstTags = malloc((kBXML_MaxDictTags * sizeof(char*)) + sizeof(StrList_t));	/* Get space for dictionary entry pointers. */
	if ((pstTags == NULL) || (sp == NULL)) {
		
		perror("error: out of memory\n");
		exit(-1);
	}
	pstTags->iEntries = kBXML_MaxDictTags;
	stack_top_p = sp + kBXML_StackSize;							/* Calculate top of tag stack for later. */
	for (i = 0; i <kBXML_MaxDictTags; i++) pstTags->pszString[i] = "";	/* Initialize the dictionary tag pointers. */

	/* Search for unique tags from input file and add to dictionary. */

    fprintf(stderr,"Building dictionary...\n");
	avail = 0;
	while (pszTok = GetToken(str, fs)) {

		if ((i = StrList_Find(pszTok, pstTags)) == kFind_NotFound){ 	/* If tag is not in dictionary... */

            len = strlen(str)+1;                                /* +1 to factor in string terminator. */
            if (len > (kBXML_MaxTagLen+1)) {
                
                fprintf(stderr,"error: tag name '%s' is too long.\n", str);
                exit(-1);
            }
            dict_len += len;									/* Keep track of dictionary size. */
			pstTags->pszString[avail] = malloc(len);			/* Add tag to dictionary. */
			strcpy(pstTags->pszString[avail], str);						
			debug("added %d:%s\n", avail, pstTags->pszString[avail]);
            avail++;											/* Move to next tag slot. */
		}
	}
    fprintf(stderr,"Added %d entries to dictionary.\n", avail);
    fputs(szBXML_DocType, fd);							        /* Write header to output file. */
	fputc((dict_len & 0xff), fd);						        /* Offset past header to config structure (low byte). */
	fputc(((dict_len >> 8) & 0xff), fd);				        /* Offset past header to config structure (high byte). */
	fputc(avail, fd);						        			/* Write number of dictionary entries. */
	for (i = 0; i < avail; i++) {

        fputs(pstTags->pszString[i],fd);                        /* Write one tag name to the dictionary. */
        fputc(kASCII_NUL, fd);                                  /* Include string terminator. */
    }
    fprintf(stderr,"Distilling XML input to binary form.\n");
	geCloseTag = kCloseType_None;								/* Reset the global close tag tracker. */
    sp[0] = -1;                                             	/* Initialize the tag stack. */
    rewind(fs);                                                 /* Return to beginning of input file. */
	idx = 0;													/* Reset data field buffer index. */
	while (pszTok = GetToken(str, fs)) {

		if ((i = StrList_Find(pszTok, pstTags)) != kFind_NotFound) {

            if (geCloseTag != kCloseType_None) {

				if (geCloseTag == kCloseType_Norm) {
				
	                if (i != *sp) {                             	/* If closing tag is not correctly nested... */
	                
	                    fprintf(stderr,"\nerror: trying to close </%s> inside of <%s>\n", pstTags->pszString[i], pstTags->pszString[*sp]);
	                    exit(-1);
	                }
	                sp--;                                       	/* Pop tag since we've closed it. */
					idx = 0;										/* Reset data field buffer index. */
	    			debug("</%s>", pstTags->pszString[i]);
	                fputc((i | kmBXML_TagFlag_Close), fd);       	/* Write binary tag with close flag. */
	            }
				else if (geCloseTag == kCloseType_EmptyTag) {
				
	    			debug("<%s/>", pstTags->pszString[i]);			/* Create an empty tag (open;no data;close). */
	                fputc(i, fd);                                   /* Write binary tag. */
					fputc(0, fd);									/* Write zero length. */
	                fputc((i | kmBXML_TagFlag_Close), fd);          /* Write binary tag with close flag. */
				}
				else {
				
					fprintf(stderr, "\nerror: unknown return code geCloseTag == %d\n", geCloseTag);
					exit(-1);
				}
			}
            /* It must be an opening tag. */
            else {

    			debug("<%s>", pstTags->pszString[i]);
				if (++sp >= stack_top_p) {
				
    				fprintf(stderr,"\nerror: tag stack nesting overflow @%d\n", kBXML_StackSize);
					exit(-1);
				}
                *sp = i;                                  		/* Push tag ID on stack. */
                fputc(i, fd);                                   /* Write binary tag. */
                while (((c = fgetc(fs)) != EOF) && isspace(c)); /* Skip whitespace. */
                fseek(fs,-1,SEEK_CUR);                          /* Backup since we want the previous character read. */
                for (idx = 0; idx < kBXML_MaxTagDataLen; idx++) {

                    buf[idx] = fgetc(fs);
                    if ((buf[idx] == EOF) || buf[idx] == kASCII_LT) {
                        
                        break;
                    }
                }
                fseek(fs,-1,SEEK_CUR);                          /* Preserve previous character on next read. */

				/* If enabled: Scan data string and truncate at CR or LF. */

            	if (!bAllowCRLF) {

	            	for (y = 0; y < idx; y++) {
	            		
						if ((buf[y] == kASCII_CR) ||(buf[y] == kASCII_LF)) {
							
							idx = y;
							break;
						}
	            	}
            	}
				/* Check if tag name length is valid. */
				
                if (idx == kBXML_MaxTagDataLen) {
                    
                    buf[idx] = kASCII_NUL;
                    fprintf(stderr,"\nerror: <%s> data field '%s' (%d bytes) is too long. Max is %d bytes\n",pstTags->pszString[i],buf,idx,kBXML_MaxTagDataLen);
                    exit(-1);
                }
                fputc(idx, fd);                              	/* Write binary length of data field. */
            	for (y = 0; y < idx; y++) {                  	/* Write out each byte of data field. */

        			debug("%c", buf[y]);
                    fputc(buf[y], fd);                          /* Write data. */
                }    	    
                if (buf[idx] == EOF) break;
            }
		}
		else {
			
			fprintf(stderr,"error: missing dictionary entry for tag %s\n", pszTok);
		}
	}
	if (sp != stack) {											/* If scope wasn't properly closed... */
		
		fprintf(stderr, "WARNING! closing scope is incomplete.\n");
	}
	fprintf(stderr, "Done.\n");
}


typedef enum {
    
    kTokState_Idle = 0,
    kTokState_OpenTag,
    kTokState_TagBody,
    kTokState_EmptyTagCheck,
    kTokState_Ignore,
} GetTokenState_t;



static char *GetToken(char *pszStr, FILE *fs /*, CloseType_t *eCloseTagStatus*/) {

#define kLBBufMask 0x07

int		c, i;
char    ac[kLBBufMask+1];
char    *p;
GetTokenState_t state = kTokState_Idle;



    p = pszStr;
    i = 0;											/* Reset circular buffer index. */			
	while ((c = fgetc(fs)) != EOF) {

//		putc(c,stdout);
		if ((p - pszStr) > kWorkStringSize) {

			pszStr[kWorkStringSize] = 0;			/* Terminate the overflowed string so we can print it. */
            fprintf(stderr,"error: buffer overflow @ %s\n", pszStr);
			exit(-1);
		}
        ac[i++ & kLBBufMask] = c;       			/* Keep look back buffer. */
        switch (state) {
    
            case kTokState_Idle:
                
                if (c == kASCII_LT) {

					i = 0;                    
                    geCloseTag = kCloseType_None;
                    state = kTokState_OpenTag;
                }  
                else {
                	if (geCloseTag && !(isspace(c))) { /* If last tag was a closing tag, assure no data field. */

						if (geCloseTag == kCloseType_Comment) {
							
	                    	fprintf(stderr,"error: comment field @ <%s> can't have a data field!\n", pszStr);
						}
						else fprintf(stderr,"error: </%s> can't have a data field!\n", pszStr);
                    	exit(-1);
                	}
                }
                break;
                  
            case kTokState_OpenTag:
                
                if (c == kASCII_GT) {
    					
                    fprintf(stderr,"error: missing tag name\n");
                    exit(-1);
    			}
                else if (c == kASCII_Exclamation) {
                    
                    state = kTokState_Ignore;
                }
                else if (c == kASCII_FwdSlash) {

                    geCloseTag = kCloseType_Norm;
                    state = kTokState_TagBody;
                }
                else {
                                        
                    if (isalnum(c)) {
                        
                        *p++ = c;
                        state = kTokState_TagBody;
                    }
                    else {
                        
    	                ac[i++ & kLBBufMask] = 0;		/* Terminate buffer. */
	                    fprintf(stderr,"error: illegal character '%c' in tag <%s>\n", c, ac);
                        exit(-1);
                    }
    			}
                break;

            case kTokState_TagBody:
                
                if (c == kASCII_GT) {
    					
    			    *p = kASCII_NUL;            	/* Terminate the string. */
                    state = kTokState_Idle;         /* Find next tag. */
       				return pszStr;
    			}
				else if (c == kASCII_FwdSlash) {	/* This could be an empty tag. */
				
					state = kTokState_EmptyTagCheck;
				}
                else if (isalnum(c)) {
                    
                    *p++ = c;
                }
                else {
                    
                    ac[i++ & kLBBufMask] = 0;		/* Terminate buffer. */
                    fprintf(stderr,"error: illegal character '%c' in tag <%s>\n", c, ac);
                    exit(-1);
                }
                break;                
                
            case kTokState_EmptyTagCheck:
                
                if (c == kASCII_GT) {

					/* It's a legitimate empty tag. */
                    geCloseTag = kCloseType_EmptyTag;
    			    *p = kASCII_NUL;            	/* Terminate the string. */
                    state = kTokState_Idle;         /* Find next tag. */
       				return pszStr;
                }
                else {
                	    					
                    ac[i++ & kLBBufMask] = 0;		/* Terminate buffer. */
                    fprintf(stderr,"error: illegal character '%c' in tag <%s>\n", c, ac);
                    exit(-1);
                }
                break;                

            case kTokState_Ignore:

                if (c == kASCII_GT) {
                    
                    /* If it's the end of a comment, go back to idle and re-start. */
                    
                    if ((ac[(i-2) & kLBBufMask] == '-') && ac[(i-3) & kLBBufMask] == '-') {

//        			    geCloseTag = kCloseType_None;	/* Following stream is NOT data. Don't ignore. */
	                    geCloseTag = kCloseType_Comment;
                        state = kTokState_Idle;     	/* Find next tag. */
                    }
    			}
                break;                              /* Ignore anything else. */
            
            default:
                
                fprintf(stderr,"error: Unknown processing state %d\n", state);
                exit(-1);
    	}
    }
	return NULL;
}





			
			


