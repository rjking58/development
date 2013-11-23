#include <iostream.h>
#include <iomanip.h>
#include <string.h>



struct TestDataStruct
{
	char *	testStr;
	int		MaxLen;
};

class ColClass
{
	
	int m_length;
public:
		void SetLength(int length) { m_length = length; }
		int GetLength(void) { return m_length; }
} ;

void strStrip(char *TempStr , ColClass* Col )
{

				// Set string position (Pos) equal to length of string - 1
				int Pos = strlen( TempStr ) - 1;

				if ( Pos >= 0 )
				{
					// While position is greater than 0, and character at position is a space
					// decrement the position counter
					while ( ( Pos >= 0 ) && ( TempStr[ Pos ] == ' ' ) )
						Pos--;
					
					// Get us back to a normal 0-offset value.
					Pos ++;
				}
				else
				{
					Pos = 0;
				}

				// If position is greater than 0 and position is less than string length - 1
				// then set position + 1 to NULL terminating byte '\0'
				if ( ( Pos >= 0 ) && ( Pos <= ( Col->GetLength() - 1 ) ) )
					TempStr[ Pos ] = '\0';

}

void main(void)
{
	int x;
	unsigned int y;
	struct TestDataStruct testData[] = {	
										{""			,2},
										{""			,3},	  
										{""			,4},	  
										{"a"		,2},	  
										{"a"		,3},	  
										{"a"		,4},	  
										{"a"		,5},	  
										{"ab"		,2},	  
										{"ab"		,3},	  
										{"ab"		,4},	  
										{"ab"		,5},	  
										{"ab"		,6},	  
										{"abc"		,2},	  
										{"abc"		,3},	  
										{"abc"		,4},	  
										{"abc"		,5},	  
										{"abc"		,6},	  
										{"abc"		,7},	  
										{"abcd"		,2},	  
										{"abcd"		,3},	  
										{"abcd"		,4},	  
										{"abcd"		,5},	  
										{"abcd"		,6},	  
										{"abcd"		,7},	  
										{"abcd"		,8},	  
										{" "   		,2},
										{" "   		,3},	  
										{" "   		,4},	  
										{"a "		,2},	  
										{"a "		,3},	  
										{"a "		,4},	  
										{"a "		,5},	  
										{"ab "		,2},	  
										{"ab "		,3},	  
										{"ab "		,4},	  
										{"ab "		,5},	  
										{"ab "		,6},	  
										{"abc "		,2},	  
										{"abc "		,3},	  
										{"abc "		,4},	  
										{"abc "		,5},	  
										{"abc "		,6},	  
										{"abc "		,7},	  
										{"abcd " 	,2},	  
										{"abcd " 	,3},	  
										{"abcd " 	,4},	  
										{"abcd " 	,5},	  
										{"abcd " 	,6},	  
										{"abcd " 	,7},	  
										{"abcd " 	,8},	  
										{"  "    	,2},
										{"  "    	,3},	  
										{"  "    	,4},	  
										{"a  "		,2},	  
										{"a  "		,3},	  
										{"a  "		,4},	  
										{"a  "		,5},	  
										{"ab  "		,2},	  
										{"ab  "		,3},	  
										{"ab  "		,4},	  
										{"ab  "		,5},	  
										{"ab  "		,6},	  
										{"abc  " 	,2},	  
										{"abc  " 	,3},	  
										{"abc  " 	,4},	  
										{"abc  " 	,5},	  
										{"abc  " 	,6},	  
										{"abc  " 	,7},	  
										{"abcd  " 	,2},	  
										{"abcd  " 	,3},	  
										{"abcd  " 	,4},	  
										{"abcd  " 	,5},	  
										{"abcd  " 	,6},	  
										{"abcd  " 	,7},
										{"abcd  " 	,8}	  
									};

	#define testDataSize  (sizeof(testData)/sizeof(testData[0]))

	ColClass GlobalCol;

	for	( x = 0 ; x < testDataSize ; x++)
	{
		GlobalCol.SetLength(testData[x].MaxLen);
		cout << "======================================================" << endl;
		cout << "======================================================" << endl;
		cout << "Original(" << testData[x].MaxLen << ")" << "case# " << x << endl;
		for (y = 0 ; y <= strlen(testData[x].testStr) ; y++)
		{
			cout << setw(2) << (int) (testData[x].testStr[y]) << " ";
		}
		cout << endl;
		for (y = 0 ; y <= strlen(testData[x].testStr) ; y++)
		{
			cout << testData[x].testStr[y] << "  ";
		}
		cout << endl;

		strStrip(testData[x].testStr,&GlobalCol);

		cout << "Stripped(" << testData[x].MaxLen << ")" << endl;
		for (y = 0 ; y <= strlen(testData[x].testStr) ; y++)
		{
			cout << setw(2) << (int) (testData[x].testStr[y]) << " ";
		}
		cout << endl;
		for (y = 0 ; y <= strlen(testData[x].testStr) ; y++)
		{
			cout << testData[x].testStr[y] << "  ";
		}
		cout << endl;


	}

}