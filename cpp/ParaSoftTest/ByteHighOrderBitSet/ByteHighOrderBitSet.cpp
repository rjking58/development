// This is the main project file for VC++ application project 
// generated using an Application Wizard.
#include <iostream>

void main(void)
{
   unsigned char HIGH_ORDER_BIT_TEST = 0x80;
   unsigned char high_set = 0xFF;
   unsigned char high_not_set = 0x7F;

   if ((high_set & HIGH_ORDER_BIT_TEST) != 0)
   {
      // code executes through this branch.
      std::cout   << "high_set=" 
                  << (int) high_set 
                  << " and high order bit is set" 
                  << std::endl;
   }
   else
   {
      std::cout   << "high_set=" 
                  << (int) high_set 
                  << " and high order bit is NOT set" 
                  << std::endl;
   }

   if ((high_not_set & HIGH_ORDER_BIT_TEST) != 0)
   {
      std::cout   << "high_not_set=" 
                  << (int) high_not_set 
                  << " and high order bit is set" 
                  << std::endl;
   }
   else
   {
      // code executes through this branch.
      std::cout   << "high_not_set=" 
                  << (int) high_not_set 
                  << " and high order bit is NOT set" 
                  << std::endl;
   }

}
