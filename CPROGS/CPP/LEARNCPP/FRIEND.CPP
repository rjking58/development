#include <iostream.h>
#include <stdio.h>
#include <conio.h>

// this program is setup for BC++ EasyWin!  It has a project 
// associated with it by the name friend.ide!
// turbo C++ text.. rjk 9/2/94


// forward define line for the box class definition...
class line;

// ********************************************************
// class box...
// ********************************************************

class box
   {
   private:
      unsigned char ltype; // color of box
      int upx, upy; // upper left corner
      int lowx, lowy; // lower right corner
   public:
      friend int same_ltype( line l, box b);
      void set_ltype(unsigned char c);
      void define_box(int x1, int y1, int x2, int y2);
      void show_box(void);
   };

// and its functions...   
void box::set_ltype(unsigned char c)
   {
   ltype = c;
   }
   
void box::define_box(int x1, int y1, int x2, int y2)
   {
   upx = x1;
   upy = y1;
   lowx = x2;
   lowy = y2;
   }   

void box::show_box(void)
   {
   int i;

      gotoxy(upx, upy);

   for(i=upx; i<= lowx; i++)
      printf("%c",ltype);

   gotoxy(upx, lowy-1);
   
   for(i = upx; i<=lowx; i++)
      printf("%c",ltype);

   gotoxy(upx,upy);

   for (i=upy; i<= lowy; i++)
      {
      printf("%c",ltype);
      gotoxy(upx,i);
      }   
   gotoxy(lowx,upy);
   
   for (i=upy; i<= lowy; i++)
      {
      printf("%c",ltype);
      gotoxy(lowx,i);
      }      
   }   

// ********************************************************
// class line
// ********************************************************
   
class line
   {
   private:
      unsigned char ltype;
      int startx, starty;
      int len;
   public:
      friend int same_ltype(line l, box b);
      void set_ltype(unsigned char c);
      void define_line(int x, int y, int l);
      void show_line();
   };

// and its functions...
void line::set_ltype(unsigned char c)
   {
   ltype = c;
   }

void line::define_line(int x, int y, int l)
   {
   startx = x;
   starty = y;
   len = l;
   }   

void line:: show_line(void)
   {
   int i;


   gotoxy(startx, starty);

   for(i=0; i< len; i++)
      printf("%c",ltype);
   }      
   
// a friend function to both line and box classes...
int same_ltype(line l, box b)
   {
   if (l.ltype==b.ltype) 
      return 1;
   return 0;
   }

// ********************************************************
// main block entry
// ********************************************************

main(void)
   {
   box b;
   line l;

   clrscr(); // for grins!
   
   b.define_box(10,10,15,15);
   b.set_ltype('*');
   b.show_box();

   l.define_line(2,2,10);
   l.set_ltype('+');
   l.show_line();

   if(!same_ltype(l,b))
      cout << "not the same";
   cout << "\npress a key";

   getch();

   // now make line and box the same color
   l.define_line(2,2,10);
   l.set_ltype('*');
   l.show_line();

   if(same_ltype(l,b)) 
      cout << "are the same ltype!!";
      
   return 0;
   }
