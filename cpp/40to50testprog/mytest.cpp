
#include <strstrea.h>
#include <node.h>


int main()
{

	try
	{
		EULNode *aNode = new EULNode;

		const char *aName = aNode->GetName();

		cout << "EUL Name: " << aName << endl;
		cout << "EUL Schema Version: " << aNode->GetDBVersion() << endl;
		cout << "EUL API Version: " << aNode->GetAPIVersion() << endl;

		aNode->Cleanup();
	
		delete aNode;

		return 1;
	}
	catch (CException* e)
	{
		TCHAR    szCause[255];

      e->GetErrorMessage(szCause, 255);

		cout << szCause << endl;

	}
}