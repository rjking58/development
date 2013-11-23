#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <windows.h>


const long ARR_SIZE = 250000L;	// 1 meg...


//@DESC: memcpy function that uses huge pointers. This function uses the Borland memcpy function
//@DESC: as the initial pattern for creation.  Since the Borland memcpy does no overlap checking
//@DESC: this function does no overlap checking.  PROGRAMMERS TAKE NOTE: since this function uses 
//@DESC: 'huge' pointers, it cannot be optimized into assembler since the manipulation of huge
//@DESC: pointers depends on 'magic' that is done behind our back by the compiler and Windows. 
//@DESC: We could probably reverse engineer the way it is currently handled (up to a point), but any 
//@DESC: changes in the op. system/compiler would blow us out of the water.  
//@PGMR: RJK
//@CRDT: 961006

void huge * _FARFUNC memcpyHUGE(void huge *dst, const void huge *src, unsigned long n)
{

	// move in word fashion since we are OK with word alignment...
	unsigned int huge * 	mc_dst 		= (unsigned int huge *) dst ;
	unsigned int huge * 	mc_src		= (unsigned int huge *) src ;
	unsigned long			byte_move	= n & 1;
	unsigned long			mc_n			= n >> 1;

	while (mc_n>0)
	{
		*mc_dst = *mc_src;
		mc_dst++;
		mc_src++;
		mc_n--;
	}
	if (byte_move)
	{
		// cast back to byte and copy if this is the last one...
		* (unsigned char huge *) mc_dst = * (unsigned char huge *) mc_src;
	}
	return (dst);
}

						 

void main()
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

	result_F.open("memcpyt.out");


	for (x = 0 ; x < ARR_SIZE ; x++)
	{
		arr1[x] = (long) ((x % 60) | 0x80402000L);
		arr2[x] = 0x0f0f0f0fL;
	}

	memcpyHUGE(arr2,arr1,900002L);

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

		result_F << setw(2) << hex << setfill('0') << (int) ((arr2[x] >> 24) & 255) ;
		result_F << setw(2) << hex << setfill('0') << (int) ((arr2[x] >> 16) & 255);
		result_F << setw(2) << hex << setfill('0') << (int) ((arr2[x] >> 8) & 255);
		result_F << setw(2) << hex << setfill('0') << (int) ((arr2[x]) & 255) << " ";
		elements_on_line++;
	}

	GlobalUnlock( h_data1 );
	GlobalFree	( h_data1 );
	GlobalUnlock( h_data2 );
	GlobalFree	( h_data2 );

	result_F.close();

	cout << "convenient break point" << endl;
}
