// asmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


void clr_mem( void *mem, unsigned int size);


// the only truly important comment left in:
// this program is proof that I'm a serious wanker.
int _tmain(int argc, _TCHAR* argv[])
{
   int x = 3;
   int y = 4;
   int z = 0;
   
   _asm 
   {
      mov eax,x;
      mov ebx,y
      add eax,ebx;
      mov z,eax;
   }
   
   cout << "x(" << x << ") y(" << y << ") z(" << z << ")" << endl;
   
   struct test_struct
   {
      short a;
      int b;
      char string1[20];
      char my_c;
   } test_s;
   test_s.a = 1;
   test_s.b = 2;
   strcpy(test_s.string1,"my string");
   test_s.my_c = 'x';
   

   
   int test_size;

   _asm
   {
         mov eax,SIZE test_s  
         mov test_size,eax    
         sar eax,2            
         and eax,eax          
         je  no_more_words    
         
         mov ecx,eax          
         mov eax,0            
         lea edi, test_s      
         cld                  
         rep stosd            
      
      no_more_words:
         mov eax,test_size    
         and eax,3            
         je  we_are_done      
         
         mov ecx,eax          
         mov eax,0
         cld                  
         rep stosb            
      
      
      we_are_done:
   }
   
   char my_arr[11];
   my_arr[0] = 1;
   my_arr[1] = 2;
   my_arr[2] = 3;
   my_arr[3] = 4;
   my_arr[4] = 5;
   my_arr[5] = 6;
   my_arr[6] = 7;
   my_arr[7] = 8;
   my_arr[8] = 9;
   my_arr[9] = 10;
   my_arr[10] = 11;      
   
   int my_arr_size;
   
   _asm
   {
         mov eax,SIZE my_arr  
         mov my_arr_size,eax  
         sar eax,2            
         and eax,eax          
         je  no_more_words2   
         
         mov ecx,eax          
         mov eax,0            
         lea edi,my_arr       
         cld                  
         rep stosd            
      
      no_more_words2:
         mov eax,my_arr_size  
         and eax,3            
         je  we_are_done2     
         
         mov ecx,eax          
         mov eax,0
         cld                  
         rep stosb            
      
      
      we_are_done2:
   }
               
   
   test_s.a = 1;
   test_s.b = 2;
   strcpy(test_s.string1,"my string");
   test_s.my_c = 'x';
   
   my_arr[0] = 1;
   my_arr[1] = 2;
   my_arr[2] = 3;
   my_arr[3] = 4;
   my_arr[4] = 5;
   my_arr[5] = 6;
   my_arr[6] = 7;
   my_arr[7] = 8;
   my_arr[8] = 9;
   my_arr[9] = 10;
   my_arr[10] = 11;      
               
   clr_mem(&test_s,sizeof(test_s));
   clr_mem(my_arr,sizeof(my_arr));
    
   
   return 0;
   
}

void clr_mem( void *mem, unsigned int var_size)
{
   
   _asm
   {
         mov eax,var_size     
         sar eax,2            
         and eax,eax          
         je  no_more_words    
         
         mov ecx,eax          
         mov eax,0            
         mov edi,mem          
         cld                  
         rep stosd            
      
      no_more_words:
         mov eax,var_size     
         and eax,3            
         je  we_are_done      
         
         mov ecx,eax          
         mov eax,0
         cld                  
         rep stosb            
      
      
      we_are_done:
   }

}
