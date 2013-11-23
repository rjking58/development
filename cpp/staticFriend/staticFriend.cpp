
#include <iostream.h>

class statC
{
   static int statVar;
public:
   static void SetStatVar(int x)
   {
      statVar = x;
   }

   static int GetStatVar()
   {
      return statVar;
   }
};

int statC::statVar = 0;

class statCFriend : public statC
{
public:
   static void ResetVar()
   {
      statC::statVar = 0;
   }

};

main()
{
   cout << "1:" << statC::GetStatVar() << endl;
   statC::SetStatVar(10);
   cout << "2:" << statC::GetStatVar() << endl;
   statCFriend::ResetVar();
   cout << "3:" << statC::GetStatVar() << endl;
}
