#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class dog
{
   private:
      dog   *body;
      char  *name;
      dog   *tail;
   public:
      dog ( char * dog_name);
      char * dog_name();
      void create_tail( char * name_of_tail);
      char * get_name_of_tail();
};

// constructor for 'dog'
dog::dog(char *dog_name)
{
   // instantiate a character array for the name
   name = new char [strlen(dog_name) + 1];
   // put name in array
   strcpy(name,dog_name);
   // NULL out other pointers.
   tail = body = 0;
}      

// get the name and return it to caller.
char * dog::dog_name()
{  
   return name;
}

// make a tail and link it back to main 'dog'
void dog::create_tail( char * name_of_tail)
{
   // instantiate a 'dog' object with name set to tail name
   tail = new dog(name_of_tail);
   // set it's body pointer to point back to the object
   // which is pointing to it.
   tail->body = this; // as in 'this' object
}

char * dog::get_name_of_tail()
{
   return tail->dog_name();
}

main()
{
   dog sheep_dog("sheep dog");

   sheep_dog.create_tail("Furry");

   printf("\nThe name of the dog is %s",
          sheep_dog.dog_name());
   printf("\n The type of tail is %s",
          sheep_dog.get_name_of_tail());
             
}
