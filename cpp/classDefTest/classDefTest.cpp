#include <strstrea.h>

class Outer
{
public:
   class IBase
   {
   public:
      virtual void PrintName() = 0;
   };
private:
   class I1 : public IBase
   {
   public:
      virtual void PrintName()
      {
         cout << "I1" << endl;
      }
   };
   class I2 : public IBase
   {
   public:
      virtual void PrintName()
      {
         cout << "I2" << endl;
      }
   };

   IBase **ib_ar;
   int Curr_ib;
public:
   Outer()
      :  Curr_ib(0)
   {
      ib_ar = new IBase * [ 10 ];
   }
   void MakeI1();
   void MakeI2();
   void PrintList();

};

void Outer::MakeI1()
{
   ib_ar[Curr_ib++] = new I1;
}
void Outer::MakeI2()
{
   ib_ar[Curr_ib++] = new I2;
}

void Outer::PrintList()
{
   for(int x = 0; x < Curr_ib; x++)
   {
      ib_ar[x]->PrintName();
   }
}


main()
{
   Outer o;

   o.MakeI1();
   o.MakeI2();
   o.MakeI1();
   o.MakeI2();
   o.MakeI1();
   o.MakeI2();
   o.MakeI1();
   o.PrintList();
}