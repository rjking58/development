#include <stdio.h>
#include <stdlib.h>

class dlink
{  
   private:
      dlink * pre;   //previous
      dlink * suc;   //successor
      char  dlink_id;
   public: 
      void append(dlink *);  
      dlink(char chr);

};

dlink::dlink(char chr)
{
   pre = (dlink *)NULL;
   suc = (dlink *)NULL;
   dlink_id = chr;
}

void dlink::append(dlink *p)
{
   p->suc = suc;
   p->pre = this;
   if (suc == (dlink *) NULL)
   {
      suc = p;
   }
   else
   {
      suc->pre = p;
      suc = p;
   }
}

dlink* list_head;

main()
{
   dlink a('a'),
         b('b'),
         c('c');

   list_head = new dlink('l');
   
   list_head->append(&a);
   list_head->append(&b);
   list_head->append(&c);
   printf("bye!");
}