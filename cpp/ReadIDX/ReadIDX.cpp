// ReadIDX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

void test2();

struct IDXheader
{
   long  start;
   long  length;
   long  PAD1;
   long  PAD2;  
   long  PAD3;
   long  PAD4; 
   long  extra;     
};


int _tmain(int argc, _TCHAR* argv[])
{
   // read the idx file...
   
   FILE *idxFile;
   
   idxFile = fopen("g:\\tmp\\voice3.idx","rb");
   
   IDXheader currHeader;
   currHeader.extra = 0xFEFEFEFE;
   char      fileName[1000];
   char      tailer[10];
   bool      eofDetected = false;
   
   
   fseek(idxFile,24,SEEK_SET);
   
   do
   {
      // read header..
      fread((void *) &currHeader,
            24,
            1,
            idxFile);
      if (feof(idxFile))
      {
         eofDetected = true;
      }
      else
      {
         // read the string into string variable.      
         short currStrOfst = 0;
         
         bool endOfString = false;   
         while (!endOfString)
         {
            fread((void *) &(fileName[currStrOfst]),
                  1,
                  1,
                  idxFile);
            endOfString = fileName[currStrOfst] == 0;            
            currStrOfst++;
         }
         printf("start: 0x%x  length: 0x%x name: %s\n",currHeader.start,currHeader.length,fileName);
         fread((void *) &(tailer[0]),
               3,
               1,
               idxFile);
      }
      
   } while (!eofDetected);
   
   fclose(idxFile);
   
   test2();

   return 0;
}


// logic for writing a file
void test2()
{
   FILE *idxFile;
   FILE *datFile;
   FILE *mp3File;

   datFile = fopen("g:\\tmp\\voice3.dat","r+b");
   // datFile = fopen("g:\\Diablo2NonExpansion\\save\\SirDiesALot.d2s","r+b");
   mp3File = fopen("g:\\tmp\\test.mp3","wb");
   // basic read loop..
   
   long start = 0x01c5b444;
   long len   = 0x016c80;
   fseek(datFile,start,SEEK_SET);
   char curr_char;
   for(  long curr_ofst = 0;
         curr_ofst < len;
         curr_ofst++          )
   {
        fread((void *) &curr_char,
            sizeof(curr_char),
            1,
            datFile);
        fwrite((void *) &curr_char,
               1,
               1,
               mp3File);    
   }
   
   fclose(datFile);
   fclose(mp3File);
}

