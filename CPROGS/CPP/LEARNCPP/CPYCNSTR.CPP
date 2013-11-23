#include <iostream.h>
#include <stdlib.h>
              
int   next_class_num = 0;
              
class myclass
{     
   private:
      int   *p;                               
      int   myclass_num;
   public:
      myclass(int i);            
      // copy constructor...
      myclass(const myclass &ob);   
      ~myclass();
      int getval();
      int get_myclass_num();
};

int myclass::get_myclass_num()
{
   return myclass_num;
}

int myclass::getval(void)
{
   return *p;
}    

// copy constructor
myclass::myclass(const myclass &obj)
{                               
   cout << "myclass::myclass(const myclass &obj):> invoke for " << next_class_num << "\n";
   cout << "Creating 'new' p\n";
   p = new int;
   if (!p)
   {
      cout << "Allocation Error";
      exit(1);
   }

   *p = *obj.p;   //copy the value!
   myclass_num = next_class_num++;
   cout << "myclass::myclass(const myclass &obj):> exit.\n";
}

myclass::myclass(int i=1)
{
   cout << "myclass::myclass(int i=1):> invoke for " << next_class_num << "\n";
   cout << "Allocating p\n";
   p = new int;
   if (!p)
   {
      cout << "Allocation Error";
      exit(1);
   }
   myclass_num = next_class_num++;
   *p = i;
   cout << "myclass::myclass(int i=1):> exit " << "\n";
}

myclass::~myclass()
{
   cout << "myclass::~myclass():> Freeing p\n";
   delete p;
}

void display (myclass ob)
{       
   // entering this puppy causes invokation of copy constructor!
   cout << "display():> enter\n";
   cout << "object(" << ob.get_myclass_num() << ") = " << ob.getval() << "\n";
   cout << "display():> exit\n";
}

main ()
{
   myclass a(10);

   cout << "main():> before display(a)\n";
   display (a);
   cout << "main():> after display(a)\n";

   return 0;
}
