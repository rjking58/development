#include <iostream.h>
#include <string.h>

class C
{
public:
	C(const char *Name)
	{
		if(Name)
		{
			mName = new char [(strlen(Name) + 1)];
			strcpy(mName,Name);
		}
		else
		{
			mName = 0;
		}
	}
	~C()
	{
		delete [] mName;
	}

	void	aFunc()
	{
		static int i = 0;
		
		i++;
		cout << mName << "::" << i << endl;
	}

private:
	char	*mName;
};

void main()
{
	C	c1("c1");
	C	c2("c2");

	c1.aFunc();
	c2.aFunc();
	c1.aFunc();
	c2.aFunc();
	c1.aFunc();
	c2.aFunc();
				 

}