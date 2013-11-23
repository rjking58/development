#include <iostream.h>

void main(void)
{
	// pointer to an int array...
	int *i_p = new int[100];
	// copy of pointer to int array
	void *i_p_t = i_p;

	// loop control variable
	int x;

	// put 10 chars into the array in packed format...
	for (x = 0; x < 10; x++)
	{
		// convert our temporary pointer to a char
		* (char *) i_p_t = '0' + x;
      // increment as a char...
		((char *) i_p_t)++;

	}

	for (x = 0; x < 10; x++)
		cout << hex << "0x" << i_p[x] << endl;	

}