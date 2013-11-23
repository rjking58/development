#include <iostream.h>

struct S3
{
	int i,j,k;
};

class Vector 
{
	public:
		Vector(void)
		{
			the_array =  (struct S3 far **) new struct S3 * [30];
		}
		struct S3 * far & operator [] ( unsigned int ref)
		{
			return (struct S3 *) the_array[ref];
		}
	void add ( int where, struct S3 * to_add)
	{
		the_array[where] = to_add;
	}

	protected:
		struct S3 far ** the_array ;
};


main()
{
	  Vector				v1;
	  unsigned int		x;
//	  struct S3			far ** an_array;
	  struct S3			far * S3_p;
	  
//	  an_array = (struct S3 **) new struct S3 * [30] ;

	  for (x = 0; x < 10 ; x++)
	  {
			S3_p = (struct S3 far *) new struct S3;
			S3_p->i = x+1;
			S3_p->j = (x+1)*10;
			S3_p->k = (x+1)*100;
			
			v1.add(x,S3_p);
	  //		an_array[x] = S3_p;
	  }
	  for (x = 0; x < 10 ; x++)
	  {
			cout << v1[x]->i << v1[x]->j << v1[x]->k << " " << endl;
		//	cout << an_array[x]->i << an_array[x]->j << an_array[x]->k << " ";
	  }                     
}