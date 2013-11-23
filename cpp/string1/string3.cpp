#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TEST1


main()

{
	#ifdef TEST1
	char lesser[]	=	"123";
	char greater[]	=	"1234"; // it is greater!!
	#endif

	#ifdef TEST2
	char lesser[]	=	"ABC";
	char greater[]	=	"abc"; // it is greater!!
	#endif

	#ifdef TEST4
	char lesser[]	=	"abc"; // it is greater!! (REVERSED FOR THE HELL OF IT)
	char greater[]	=	"ABC"; 
	#endif

	#ifdef TEST3
	char lesser[]	=	"123";
	char greater[]	=	"123"; // it is greater!!
	#endif


	printf("lesser = '%s'  greater = '%s'\n",lesser,greater);

	if(strcmp(lesser,greater) < 0)
	{
		printf("strcmp(lesser,greater) < 0\n");
	}
	if(strcmp(lesser,greater) > 0)
	{
		printf("strcmp(lesser,greater) > 0\n");
	}

	if(strcmp(greater,lesser) < 0)
	{
		printf("strcmp(greater,lesser) < 0\n");
	}
	if(strcmp(greater,lesser) > 0)
	{
		printf("strcmp(greater,lesser) > 0\n");
	}
}
