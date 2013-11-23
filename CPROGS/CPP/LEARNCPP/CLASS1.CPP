#include <iostream.h>
#define DEBUGGING 1
#include "tracer.h"


// this example demostrates the sequence of events when a class
// is passed to a function...  specifically, the destructor to the 
// passed class is called.  This is done since a copy of the class
// was made for the local function, and when the function exits,
// the local class goes out of scope. 
class myclass
   {
      int val;
   public:
      myclass(int i)
         {
         TRACE_ENTER("myclass::myclass");
         val = i;
         cout << "Constructing myclass w/" << i << "\n";
         TRACE_EXIT("myclass::myclass");
         }
      ~myclass()
         {
         TRACE_ENTER("myclass::~myclass");
         cout << "Destructing\n";
         TRACE_EXIT("myclass::~myclass");
         }
      int getval()
         {
         TRACE_ENTER("myclass::getval");
         return val;
         TRACE_EXIT("myclass::getval");
         }   
   };      

void display(myclass ob)
   {
   // copy of class called 'ob' is used here... 
   // constructor is NOT called, since C++ is smart enough
   // to not damage the copy.
   TRACE_ENTER("display");
   
   cout << ob.getval() << "\n";
   TRACE_EXIT("display");
   // ob's destructor is called here 
   }   

main ()
   {

#ifdef DEBUGGING
   if ((trcfile = fopen("class1.trc", "w")) == NULL) 
      {
      printf("Can't open PC file");
      exit(0);
      }
   else 
      {
#endif
      // instantiate class 'a', call its constructor
      myclass a(10);

      TRACE_STR("before display");
      display(a);
      TRACE_STR("after display");


#ifdef DEBUGGING
//      fclose(trcfile);
      }
#endif
   return 0;
   //destruct a, call its destructor!
   }
