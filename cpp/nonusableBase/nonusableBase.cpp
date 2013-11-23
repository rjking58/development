
#include <iostream.h>

class Base
{
public:

   int Get_i()
   {
      return m_i;
   }
protected:
   Base(int i)
      :  m_i(i)
   {
   }

private:
   int m_i;
};

class Deriv : public Base
{
public:
   Deriv(int i)
      :  Base( i )
   {
   }
private:


};

//************OR*************

class Base2
{
public:

   int Get_i()
   {
      return m_i;
   }
   Base2(int i)
      :  m_i(i)
   {
   }
   virtual ~Base2()=0;

private:
   int m_i;
};

Base2::~Base2(){}


class Deriv2 : public Base2
{
public:
   Deriv2(int i)
      :  Base2( i )
   {
   }
private:


};




void main(void)
{
   Base b(4);
   Base2 b2(7);
   Deriv d(10);
   Deriv2 d2(20);

   cout << "i=" << d.Get_i() << endl;
   cout << "i2=" << d2.Get_i() << endl;

}
