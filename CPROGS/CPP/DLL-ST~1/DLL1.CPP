#include <iostream.h>

extern "C" int __far __pascal f1(void); 
// void __far __pascal F1(void);  

main()
{
   cout << "calling DLL1 f1()" << endl;
   cout << f1() << endl;
}
