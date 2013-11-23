// Diablo2Hackit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

enum PALADIN_SKILLS
{
   sacrifice = 0,
   smite,
   might,
   prayer,
   resist_fire,
   holy_bolt, //6
   holy_fire,
   thorns,
   defiance,
   resist_cold,
   zeal, //12
   charge,
   blessed_aim,
   cleansing,
   resist_lightning,
   vengeance,  // 18
   blessed_hammer,
   concentration,
   holy_freeze,
   vigor,
   conversion, // 24
   holy_shield,
   holy_shock,
   sanctuary,
   meditation,
   fist_of_heavens, //30
   fanatacism,
   conviction,
   redemption,
   salvation
};


int _tmain(int argc, _TCHAR* argv[])
{
   FILE *d2sFile;

   d2sFile = fopen("g:\\Diablo2NonExpansion\\save\\SirDiesALot.d2s","r+b");
   if(d2sFile == NULL)
   {
      printf("bad open\n");
   }
   else
   {
      printf("good open\n");
      unsigned char *d2sBuffer = new unsigned char[4000];
      unsigned long d2sBufferSize = 0;
      unsigned long ReadChecksum = 0;

      
            
      fseek(d2sFile,12,SEEK_SET);
      fread((void *) &ReadChecksum,
            sizeof(ReadChecksum),
            1,
            d2sFile);
      printf("ReadChecksum: 0x%x\n",ReadChecksum);
      
      // now calculate checksum
      fseek(d2sFile,0,SEEK_SET);
      d2sBufferSize = fread(d2sBuffer,sizeof(char),4000,d2sFile);
      printf("d2sBufferSize: %x\n",d2sBufferSize);
            
      // clear checksum field..            
      d2sBuffer[12] =0;
      d2sBuffer[13] =0;
      d2sBuffer[14] =0;
      d2sBuffer[15] =0;                  


#if 0      
      // this works for sure..
      _asm
      {
         push  esi;
         mov   esi,d2sBufferSize;
         xor   eax,eax;
         xor   ecx,ecx;
         test  esi,esi;
         jle   we_are_done;
         push  ebx;
         push  edi;
         mov   edi,d2sBuffer;
         
         checksum_loop:
         xor   edx,edx;
         xor   ebx,ebx;
         mov   dl, byte ptr [ecx+edi]  ;  this is just the next byte in the buffer.
         test  eax,eax                 ;  set flags based on byte..
         setl  bl                      ;  this rolls the high bit into the low bit..
         add   edx,ebx                 ;  
         inc   ecx;
         cmp   ecx,esi
         lea   eax,dword ptr [edx + 2 * eax]; this is the shift left add quantity..
         jl    checksum_loop;
         pop   edi;
         pop   ebx;

         we_are_done:
         mov   bufferChecksum,eax;
         pop   esi;
      }
#endif



      unsigned int skill_ofst;
      
      // look for 'if' for skills...
      for (skill_ofst = 769; skill_ofst < d2sBufferSize; skill_ofst++)
      {
         if (     d2sBuffer[skill_ofst]   == 'i' 
               && d2sBuffer[skill_ofst+1] == 'f')
         {
            break;
         }
      }
      skill_ofst += 2;
      
      printf("smite: %d\n"       ,d2sBuffer[skill_ofst +smite]);
 
      d2sBuffer[skill_ofst +smite] = 1;
      fseek(d2sFile,skill_ofst +smite,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +smite]),1,1,d2sFile);
      
      printf("might: %d\n"       ,d2sBuffer[skill_ofst +might]);

      d2sBuffer[skill_ofst +might] = 10;
      fseek(d2sFile,skill_ofst +might,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +might]),1,1,d2sFile);      
            
      printf("holy_bolt: %d\n"   ,d2sBuffer[skill_ofst +holy_bolt]);

      d2sBuffer[skill_ofst +holy_bolt] = 0;
      fseek(d2sFile,skill_ofst +holy_bolt,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +holy_bolt]),1,1,d2sFile);      
      d2sBuffer[skill_ofst +zeal] = 1;
      fseek(d2sFile,skill_ofst +zeal,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +zeal]),1,1,d2sFile);      

      
      printf("holy_fire: %d\n"   ,d2sBuffer[skill_ofst +holy_fire]);
      printf("charge: %d\n"      ,d2sBuffer[skill_ofst +charge]);
      printf("blessed_aim: %d\n" ,d2sBuffer[skill_ofst +blessed_aim]);
      printf("holy_freeze: %d\n" ,d2sBuffer[skill_ofst +holy_freeze]);
      printf("blessed_hammer: %d\n" ,d2sBuffer[skill_ofst +blessed_hammer]);

      d2sBuffer[skill_ofst +holy_fire] = 0;
      fseek(d2sFile,skill_ofst +holy_fire,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +holy_fire]),1,1,d2sFile);      
      d2sBuffer[skill_ofst +holy_freeze] = 0;
      fseek(d2sFile,skill_ofst +holy_freeze,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +holy_freeze]),1,1,d2sFile);      
      
      d2sBuffer[skill_ofst +vengeance] = 2;
      fseek(d2sFile,skill_ofst +vengeance,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +vengeance]),1,1,d2sFile);      
      



      d2sBuffer[skill_ofst +blessed_hammer] = 0;
      fseek(d2sFile,skill_ofst +blessed_hammer,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +blessed_hammer]),1,1,d2sFile);      

      d2sBuffer[skill_ofst +sacrifice] = 1;
      fseek(d2sFile,skill_ofst +sacrifice,SEEK_SET);
      fwrite(&(d2sBuffer[skill_ofst +sacrifice]),1,1,d2sFile);      



      unsigned long bufferChecksum = 0;
      unsigned long byte_read;
      
      // this matches the _asm block, but is kinda easier to read!
      for (unsigned int x = 0; x < d2sBufferSize; x++)
      {
         byte_read = d2sBuffer[x];

         // roll the top bit low if necessary...
         if (bufferChecksum &0x80000000)
         {
            byte_read++;
         }
         
         bufferChecksum = bufferChecksum << 1;
         bufferChecksum += byte_read;
      }
      
      printf("bufferChecksum: 0x%x\n",bufferChecksum);
      fseek(d2sFile,12,SEEK_SET);
      fwrite(&bufferChecksum,4,1,d2sFile);
            
      fclose(d2sFile);    
      delete d2sBuffer;  
   }


	return 0;
}

