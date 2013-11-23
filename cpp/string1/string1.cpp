#include <stdio.h>
#include <stdlib.h>

main()

{

	char strTemp[28] = "";
	printf("012345678901234567890123456789\n");

	sprintf( strTemp, "'%25s'", "100" );
	printf("%s",strTemp);

}
