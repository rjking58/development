


#include <iostream.h>

main()
{
	int 	*i_p;

	i_p = (int *) NULL;
	
	cout << "set to NULL pointer=" << i_p << endl;
	
	i_p = new int;

	cout << "'newed' pointer=" << i_p << endl;

	*i_p = 10;

	cout << "pointer=" << i_p << "  containing" << *i_p << endl;

	delete i_p;

	cout << "after delete pointer=" << i_p << endl;

	i_p = (int *) NULL;

	cout << "set to NULL pointer=" << i_p << endl;

	
}
