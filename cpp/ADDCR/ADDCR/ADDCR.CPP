#include <stdio.h>


void main(void)
{
	char input_buf[2000];

	while (!feof(stdin))
	{	
		gets(input_buf);
		printf("%s\n",input_buf);
	}
}