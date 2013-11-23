#include <strstrea.h>
#include <stdlib.h>
#include <string.h>

void ltrim(char *string);
void rtrim(char *string);


main()
{
	char	*env_include;
	char	*local_env_include; 
	char	*include_paths[200];	// this should be enough!
	int	pathCnt = 0;
   int   currPath;

	env_include = getenv( "INCLUDE" );
	if (env_include)
	{
		local_env_include = new char [strlen(env_include) + 1];
		strcpy(local_env_include,env_include);

		// split up 


		char	*Token;							// current token read from input.
		char	DELIMS[] = ";";				// delimiter for tokens

		cout << local_env_include << "------------------" << endl ;
		// get arguments to command (space delimited)
		Token = strtok(local_env_include,DELIMS);

		while (Token)
		{
			char  *tmpStr;

			tmpStr = new char[strlen(Token) + 1]; // +null 
			strcpy(tmpStr, Token);
			// strip off trailing spaces...
			rtrim(tmpStr);
			// strip off leading spaces..
			ltrim(tmpStr);

			strupr(tmpStr);

			if(strcmp(tmpStr,"%INCLUDE%") == 0)
			{
				delete [] include_paths[pathCnt];
			}
			else
			{
				// copy to permanent place with quotes..
				include_paths[pathCnt] = new char[strlen(tmpStr)+3]; // 2 quotes and a null extra..
				strcpy(include_paths[pathCnt],"\"");
				strcat(include_paths[pathCnt],tmpStr);
				strcat(include_paths[pathCnt],"\"");
				pathCnt++;
				delete [] tmpStr;
			}

			Token = strtok(NULL,DELIMS);
		} 
	}
	
	for (currPath = 0; currPath < pathCnt; currPath++)
	{
		cout << "#" << currPath << ": " << include_paths[currPath] << endl;
	}

	cout << "include:" << env_include << endl;

	for (currPath = 0; currPath < pathCnt; currPath++)
	{
		delete [] include_paths[currPath];
	}
}


void ltrim(char *string)
{
	//glbl,kmk
	char *p = string;

	while (  *p ==  ' ' )
       p++;

	//glbl, kmk, the following code is dbcs compatible
	if (p != string)
	{
		 while ( *p != '\0' )
		 {
			  *string++ = *p++;
		 }
		 *string = '\0';
	}
}

void rtrim(char *string )
{
	//glbl, kmk
	int 	nLen = strlen(string);
	char 	*psz = string;
   psz += (nLen - 1);

	for ( int nIndex = 0; nIndex < nLen; nIndex ++ )
	{
		if ( *psz == ' ' )
		{
			*psz = '\0';
			psz--;	  
		}
		else
		{
			break;		// 2.60Je.00.018_AR6970: esb
		}
	}
}




