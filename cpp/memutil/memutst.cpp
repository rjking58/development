#include <memutil.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <windows.h>

const long ARR_SIZE = 250000L;	// 1 meg...

main()
{

//	long huge 	*arr1 = new long huge [ARR_SIZE];
//	long huge 	*arr2 = new long huge [ARR_SIZE];
	long huge 	*arr1;
	long huge 	*arr2;
	long			x;
	int			elements_on_line= 0;
	HGLOBAL		h_data1;
	HGLOBAL		h_data2;


	h_data1	= GlobalAlloc( GHND, (long) sizeof(long) * (long) ARR_SIZE);
	arr1		= ( long huge * ) GlobalLock( h_data1 );
	h_data2	= GlobalAlloc( GHND, (long) sizeof(long) * (long) ARR_SIZE);
	arr2		= ( long huge * ) GlobalLock( h_data2 );

	//	declare our file...
	ofstream		result_F;

	result_F.open("memutil.out");


	for (x = 0 ; x < ARR_SIZE ; x++)
	{
		arr1[x] = 0x0f0f0f0fL;
	}

	memsetHUGE(&(arr1[30]),0x33,119999L);

	// setup first address in output file.
	x = 0;
	result_F << setw(10) << setfill('0') << x << ":: ";

	for (x = 0 ; x < ARR_SIZE ; x++)
	{
		if(elements_on_line > 3)
		{
			elements_on_line = 0;
			result_F << endl;
			result_F << setw(10) << x << ":: ";
		}          

		result_F << setw(2) << hex << setfill('0') << (int) ((arr1[x] >> 24) & 255) ;
		result_F << setw(2) << hex << setfill('0') << (int) ((arr1[x] >> 16) & 255);
		result_F << setw(2) << hex << setfill('0') << (int) ((arr1[x] >> 8) & 255);
		result_F << setw(2) << hex << setfill('0') << (int) ((arr1[x]) & 255) << " ";
		elements_on_line++;
	}

	GlobalUnlock( h_data1 );
	GlobalFree	( h_data1 );
	GlobalUnlock( h_data2 );
	GlobalFree	( h_data2 );

	result_F.close();

	cout << "convenient break point" << endl;
}