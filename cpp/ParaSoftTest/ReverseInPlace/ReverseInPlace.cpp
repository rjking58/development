// reverse string in place.
// compiled and tested in Microsoft Visual C++ .net (2003)
// Author: Richard King
//    revision history:
//          2006-Jun-20:  initial creation.

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>


enum ReverseStringErrors
{
   STRING_REVERSED = 0,    // everything went ok.
   NULL_POINTER_PASSED,    // null pointer was passed to function.
   STRING_NOT_SWAPPED      // happens if strlen of passed string is equal to 1 or 0
};

//    ReverseStringInPlace
//       -- reverse a string 'in place' (i.e. do not re allocate string on the 
//       -- heap, the pointer passed in is assumed to not change.
//             char const *strToReverse   :  the string to reverse.  
//                                           Pointer is const, string is not.
//             ErrorCode                  :  error.. see ReverseStringErrors enum.
// 
//    possible improvements:
//       o depending on environment, there may be a maximum allowable size to 
//         the string.. detect that and return error in that case.
//       o Unicode support
//       o support for international character sets.
void ReverseString(char * const strToReverse, ReverseStringErrors &ErrorCode)
{
   ErrorCode = STRING_REVERSED;
   
   if (strToReverse == 0)
   {
      ErrorCode = NULL_POINTER_PASSED;
   }
   else
   {
      long length = strlen(strToReverse);
      if (length < 2)
      {
         ErrorCode = STRING_NOT_SWAPPED;
      }
      else
      {
         char * startStr_p = strToReverse;
         char * endStr_p = strToReverse + (length - 1);
         char tmp;
         while (startStr_p < endStr_p)
         {
            tmp = *endStr_p;
            *endStr_p = *startStr_p;
            *startStr_p = tmp;
            startStr_p++;
            endStr_p--;
         }
      }
   }
}


//    printError
//       -- VERY simple error return. for our reverse string function.  
//          Decoupled so that it can easily be enhanced.
// 
//    possible improvements:
//       o internationalize and make us of more standard error 
//         decoupled error mechanism (strings in separate file, etc.)   
//       
void printError(ReverseStringErrors ErrorCode)
{
   switch(ErrorCode)
   {
      case STRING_REVERSED :
         std::cout << "String was reversed normally" << std::endl;
         break;
      case NULL_POINTER_PASSED :
         std::cout << "Null pointer passed to ReverseString!" << std::endl;
         break;
      case STRING_NOT_SWAPPED :
         std::cout << "String to short to reverse" << std::endl;
         break;
      default:
         std::cout << "Unknown error code!!" << std::endl;
         break;
   }
}

// test our string reversal.
//   Possible improvements:
//   move test cases into CPPTest or other test case framework for repeatability.
void main(void)
{
   ReverseStringErrors ErrorCode;
   //                          000000000111111
   //                          123456789012345
   char requirements_test[] = "Madam, I'm Adam"; // string is odd 
                                                 // # of characters long
   //                         000000000111
   //                         123456789012
   char even_length_test[] = "Even Length ";     // string is even 
                                                 // # of characters long.
   // 0 length string.
   char zero_length_test[] = "";
   // 1 length string.
   char one_length_test[] = "1";

   // null string test..
   ReverseString((char *)0,ErrorCode);
   std::cout << "null pointer test::" << std::endl;
   printError(ErrorCode);
   std::cout << std::endl;


   // have we fulfilled basic requirements?   
   std::cout   << "requirements_test before reverse>>" 
               << requirements_test 
               << "<<" 
               << std::endl;
   ReverseString(requirements_test,ErrorCode);
   std::cout   << "requirements_test after  reverse>>" 
               << requirements_test 
               << "<<" 
               << std::endl;
   printError(ErrorCode);
   std::cout   << std::endl;

   // since requirements test is a string of odd # of characters, 
   // test even length to verify  we are working in that case.               
   std::cout   << "even_length_test before reverse>>" 
               << even_length_test 
               << "<<" 
               << std::endl;
   ReverseString(even_length_test,ErrorCode);
   std::cout   << "even_length_test after  reverse>>" 
               << even_length_test 
               << "<<" 
               << std::endl;
   printError(ErrorCode);
   std::cout   << std::endl;

   // 'corner' or 'boundary' cases.                                    
   // make sure we do ok stuff with a valid string that is length == 0
   std::cout   << "zero_length_test before reverse>>" 
               << zero_length_test 
               << "<<" 
               << std::endl;
   ReverseString(zero_length_test,ErrorCode);
   std::cout   << "zero_length_test after  reverse>>" 
               << zero_length_test 
               << "<<" 
               << std::endl;
   printError(ErrorCode);
   std::cout   << std::endl;

   // make sure we do ok stuff with a valid string that is length == 1
   std::cout   << "one_length_test before reverse>>" 
               << one_length_test 
               << "<<" 
               << std::endl;
   ReverseString(one_length_test,ErrorCode);
   std::cout   << "one_length_test after  reverse>>" 
               << one_length_test 
               << "<<" 
               << std::endl;
   printError(ErrorCode);
   std::cout   << std::endl;
   
 
   // verify no memory leaks..   
   // just generally good practice here..
   _CrtDumpMemoryLeaks();
}
