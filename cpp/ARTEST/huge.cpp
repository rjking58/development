#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


main()
{
	long * huge * hi;
	long * huge * hi2;
	long l;

	hi  = new long * huge [160000L];
	hi2 = new long * huge [160000L];

	for (l = 0; l < 160000L; l++)
	{
		hi[l] = new long ;
		*(hi[l]) = l;
	}


	memmove( hi2 , hi, 100000L * sizeof(long *) );

	for (l = 0; l < 100000L; l++)
		if( *(hi2[l]) != l)
		{
			printf("bad compare\n");
			exit(0);
		}
	printf("done");
}