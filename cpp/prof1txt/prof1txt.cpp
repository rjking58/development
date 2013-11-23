#include <iostream.h>
#include <windows.h>

const int keylistsz = 32000;
char *default_str = {"<not found>"};


class KeyListBuilder;

class IniKey
{
private:
	friend KeyListBuilder;

public:
	IniKey();
	virtual ~IniKey();
	char * GetKey() = 0;
	
};

class IniKeyInt : public IniKey
{
	friend KeyListBuilder;
	// int  with Key value
	// String with Key name
	SetKey(int keyval);
public:
	IniKeyInt();
	virtual ~IniKeyInt();
	char * GetKey();

	
}

class IniKeyString : public IniKey
{
	friend KeyListBuilder;
	// String with Key value
	// String with Key name
	SetKey(char * keyval);
public:
	IniKeyString();
	virtual ~IniKeyString();
	char * GetKey();

}


class IniSection
{
private:
	// list of IniKey's

public:
	IniSection();
	~IniSection();

};

// this class encapsulates the dependent information on keys.. (types of keys,
// differences between op systems.. etc.
class KeyListBuilder
{

};

class IniFile
{
private:
	// list of IniSection's
public:
	// read in all ini sections....
	IniFile();
	~IniFile();
}

void main()
{
	char	*curr_key;
	int		curr_keysz;
	try
	{
		char *keylist;
		
		keylist = new char[keylistsz];

		if (!keylist)
		{
			throw("could not allocate memory for key list");
		}

		::GetPrivateProfileString(	"DataSources",	// app name (square brackets)
									NULL,			// key name (left side of '=' )
									default_str,	// default if not found.
									keylist,	// return values..
									keylistsz,	// max chars to return..
									"TSER.INI");	// file name (of ini file)
		curr_key = keylist;
		while( (curr_keysz = strlen(curr_key) ) )
		{	
			cout << "KeyName:" << curr_key << endl;
			curr_key += strlen(curr_key) + 1; // plus NULL!!
		}

	}
	catch (char * str)
	{
		cout << str << endl;
	}

}