#include <iostream.h>


class Singleton
{

public:
	// access to object w/ automatic instantiation.
	static	Singleton* Instance();
	// exercise the object..
	void	HiThere()
	{
		cout << "Hi from obj #" << obj_num << "ref #" << ref_count_tracker << "!" << endl;
	}
   ~Singleton()
   {
      ref_count_tracker--;
      if(!ref_count_tracker)
      {
         delete _instance;
         cout << "DELETING" << endl;
      }
   }

protected:
	// prevent instantiation through normal means...
	Singleton() { }

private:
	int					obj_num;
	static int			ref_count_tracker;
   static int        obj_num_tracker;
	static Singleton	*_instance;
};

Singleton* Singleton::_instance = 0;
int		   Singleton::ref_count_tracker = 0;
int         Singleton::obj_num_tracker = 0;

Singleton* Singleton::Instance()
{
	// if we haven't created one yet then...
   ref_count_tracker++;
	if(_instance==0)
	{
		// do it...
		_instance = new Singleton;
		// and set its object number up..
      obj_num_tracker++;
		_instance->obj_num = obj_num_tracker;
	}
	return _instance;
}

void main(void)
{
	
	Singleton *s1;
	Singleton *s2;
	Singleton *s3;

	s1 = Singleton::Instance();
	s2 = Singleton::Instance();
	s3 = Singleton::Instance();

	s1->HiThere();
	s2->HiThere();
	s3->HiThere();

   
}



