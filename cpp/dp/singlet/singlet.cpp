#include <iostream.h>


class Singleton
{

public:
	// access to object w/ automatic instantiation.
	static	Singleton* Instance();
	// exercise the object..
	void	HiThere()
	{
		cout << "Hi from obj #" << obj_num << "!" << endl;
	}

protected:
	// prevent instantiation through normal means...
   Singleton(int n) 
      :  obj_num(n)
   {
   }

private:
	int					obj_num;
	static int			obj_num_tracker;
};

int		   Singleton::obj_num_tracker = 0;

Singleton* Singleton::Instance()
{
	obj_num_tracker++;
   static Singleton _instance(obj_num_tracker);
   cout << "#" << obj_num_tracker << " call to Instance" << endl;

	return &_instance;
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



