#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class MyString
{
	private:
		char	mStr[20];
	public:
		MyString(const char*Str)		// Convert from const char* to SimpleString
		{
			strcpy(mStr,Str);
		}
		operator char*() 	// Convert to a const char*, allows to be used in strcpy, etc.
		{
			return mStr;
		}

};

main()
{
	MyString Str("hello world");
	char *	x;

//	x = Str;
	printf("Say: %s\n", Str);
//	printf("Say: %s\n", x);

}