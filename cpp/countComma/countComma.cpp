#include <stdio.h>


main()
{
	char inpStr[2001];
	char *currOfst;
	long lineNum = 0;
	while(!feof(stdin))
	{
		gets(inpStr);
      lineNum++;
		currOfst = inpStr;
		int commaCnt = 0;
		
		while(*currOfst)
		{
			if (*currOfst == ',')
			{
				commaCnt++;
			}
			currOfst++;
		}
		
		if (commaCnt!=11)
		{
			printf("bad line @%ld",lineNum);
		}
	}

   printf("Lines Processed:%ld",lineNum);
}