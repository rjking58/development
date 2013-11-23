
#include "testarg.h"
#include <valClss.h>


const int MAX_ARGUMENTS = 30;


void main()
{


	Argument	*InputArguments[Argument::MAX_ARGUMENTS];
	Val		*aValp;

	KeyHandle KHandle1;
	KeyHandle KHandle2;
	KeyHandle KHandle3;
	KeyHandle KHandle4;
	KeyHandle KHandle5;
	KeyHandle KHandle6;
	KeyHandle KHandle7;
	KeyHandle KHandle8;
	KeyHandle SKHandle1;
	KeyHandle SKHandle2;
	KeyHandle SKHandle3;
	KeyHandle SKHandle4;



	KHandle1 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_CONSOL_CD);
	KHandle2 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_CONSOL_CD);
	KHandle3 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_YEAR_S);
	KHandle4 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_YEAR_S);
	KHandle5 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_BUCKET_NUM);
	KHandle6 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_BUCKET_NUM);
	KHandle7 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_SCENARIO_NUM);
	KHandle8 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_SCENARIO_NUM);
	KHandle7 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_SCENARIO_NUM);
	KHandle8 = Val::DoubleKeyMake(IDENT_TO_HANDLE::IDNT_SCENARIO_NUM);
	SKHandle1 = Val::StringKeyMake(IDENT_TO_HANDLE::IDNT_AS_OF_DATE);
	SKHandle2 = Val::StringKeyMake(IDENT_TO_HANDLE::IDNT_AS_OF_DATE);
	SKHandle3 = Val::StringKeyMake(500);
	SKHandle4 = Val::StringKeyMake(501);
	
	cout << "(Double::IDNT_CONSOL_CD)Handle=" << KHandle1 << endl;
	cout << "(Double::IDNT_CONSOL_CD)Handle=" << KHandle2 << endl;
	cout << "(Double::IDNT_YEAR_S)Handle=" << KHandle3 << endl;
	cout << "(Double::IDNT_YEAR_S)Handle=" << KHandle4 << endl;
	cout << "(Double::IDNT_BUCKET_NUM)Handle=" << KHandle5 << endl;
	cout << "(Double::IDNT_BUCKET_NUM)Handle=" << KHandle6 << endl;
	cout << "(Double::IDNT_SCENARIO_NUM)Handle=" << KHandle7 << endl;
	cout << "(Double::IDNT_SCENARIO_NUM)Handle=" << KHandle8 << endl;
	cout << "(String::IDNT_AS_OF_DATE)Handle=" << SKHandle1 << endl;
	cout << "(String::IDNT_AS_OF_DATE)Handle=" << SKHandle2 << endl;
	cout << "(String::500)Handle=" << SKHandle3 << endl;
	cout << "(String::501)Handle=" << SKHandle4 << endl;



	char *Strings[1000];	
	int	nxtValidString = 0;
	aValp = new Val;
	while (GetArgs(InputArguments))
	{
		InputArguments[0]->UpStringArg();
		if(strcmp(InputArguments[0]->asCharPtr(),"SETDOUBLEKEY") == 0)
		{
  			aValp->SetDoubleKey(InputArguments[1]->asInt(),InputArguments[2]->asDouble());
			cout << "SetDoubleKey complete" << endl;
		}
		else if(strcmp(InputArguments[0]->asCharPtr(),"GETDOUBLEKEY") == 0)
		{
			cout << "keyval>>" << aValp->GetDoubleKey(InputArguments[1]->asInt()) << "<<" << endl;
		}
		else if(strcmp(InputArguments[0]->asCharPtr(),"SETSTRINGKEY") == 0)
		{
			// keep passed string around...
			Strings[nxtValidString] = new char[strlen(InputArguments[2]->asCharPtr())+1];
			strcpy(Strings[nxtValidString],InputArguments[2]->asCharPtr());
			
  			aValp->SetStringKey(InputArguments[1]->asInt(),Strings[nxtValidString]);
			nxtValidString++;
			cout << "SetStringKey complete" << endl;
		}
		else if(strcmp(InputArguments[0]->asCharPtr(),"GETSTRINGKEY") == 0)
		{
			if( aValp->GetStringKey(InputArguments[1]->asInt()) )
			{
				cout << "keyval>>" << aValp->GetStringKey(InputArguments[1]->asInt()) << "<<" << endl;
			}
			else
			{
				cout << "NULL pointer found" << endl;
			}
		}
		else if(strcmp(InputArguments[0]->asCharPtr(),"INITIALIZE") == 0)
		{
  			aValp->Initialize();
			cout << "initialize complete" << endl;
		}
		else
		{
			cout << "unrecognized function!" << endl;
		}
	
	}

}