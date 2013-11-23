#include <iostream.h>
#include <string.h>

class three_d
{
      int   x, 
            y, 
            z;
      char  three_d_name[20];

   public:
      three_d() 
      { 
         x = y = z = 0; 
         strcpy(three_d_name,"NoNameGiven");
      }
      three_d(int i, int j, int k, char *a_name) 
      {
         x = i; 
         y = j; 
         z = k; 
         strcpy(three_d_name,a_name);
      }
      three_d  operator+ (three_d op2);
      three_d  operator= (three_d op2);
      three_d  operator++();            // prefix (i.e. ++x)
      three_d  operator++(int notused); // postfix (i.e. x++)   
      void     show(void);
};

three_d three_d::operator+(three_d op2)
{
   three_d temp;

   temp.x = x + op2.x;
   temp.y = y + op2.y;
   temp.z = z + op2.z;

   return temp;
}

three_d three_d::operator=(three_d op2)
{

   x = op2.x;
   y = op2.y;
   z = op2.z;

   return *this;
}

three_d three_d::operator++() // prefix
{

   x++;
   y++;
   z++;

   return *this;
}

three_d three_d::operator++(int notused) // postfix
{

   three_d temp = *this;

   x++;
   y++;
   z++;

   return temp;
}

void three_d::show(void)
{
   cout << three_d_name << ":: " << x << ", ";
   cout << y << ", ";
   cout << z << "\n";
}

main()
{
   three_d  a(1,2,3,"a"),
            b(10,10,10,"b"),
            c;
   cout << "start\n";
   a.show();
   b.show();
   c.show();

   cout << "c = a+b\n";
   c = a+b;

   a.show();
   b.show();
   c.show();

   cout << "c = a+b+c\n";
   c = a+b+c;
   a.show();
   b.show();
   c.show();

   cout << "c = b = a\n";
   c = b = a;
   a.show();
   b.show();
   c.show();

   cout << "++c\n";
   ++c;
   a.show();
   c.show();

   cout << "c++\n";
   c++;
   a.show();
   c.show();

   cout << "a = ++c\n";
   a = ++c;
   a.show();
   c.show();

   cout << "a = c++\n";
   a = c++;
   a.show();
   c.show();

   return 0;
}
