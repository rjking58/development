#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <windows.h>


const long ARRSIZE = 200000L;	// 1 meg...





void huge *_CType _FARFUNC memmoveHUGE( void huge *dst, const void huge *src, unsigned long n )
{
	long 	               x;
	unsigned char			huge *src_byte_p = (unsigned char huge *)src;
	unsigned char			huge *dst_byte_p = (unsigned char huge *)dst;

	// same space array copy.  If the source pointer is less than target pointer, assume that the
	// source and target spaces overlap and do a backward copy to prevent hosing the data during 
	// the move.  If the source pointer is greater than the target pointer, do a forward move for 
	// the same reason.  And finally, if both pointers are equal, return since there is nothing
	// to do!  rjk

	// if they are equal.. do nothing!
	if (src_byte_p != dst_byte_p)
	{
		
		// if src 
		if (src_byte_p < dst_byte_p)
		{
			// do a backward copy...

			// move pointers to end of memory space to be moved.
			src_byte_p += (n - 1);
			dst_byte_p += (n - 1);

			// move from high to low memory.
			for (x=n; x > 0; x--)
			{
				*dst_byte_p = *src_byte_p;
				dst_byte_p--;
				src_byte_p--;
			}
		}
		else
		{
			// do a forward copy
			// move from low to high memory.
			for (x=n; x > 0; x--)
			{
				*dst_byte_p = *src_byte_p;
				dst_byte_p++;
				src_byte_p++;
			}
		}               
	}
	return( dst );
}




void main()
{

	const long	   STARTPOINT 	= 20L;
	const long	   DESTPOINT	= 10L;
	const long		MOVECNT		= 100000L;
	
//	long huge 	   *arr1 = new long huge [ARRSIZE];
//	long huge 	   *arr2 = new long huge [ARRSIZE];
	unsigned char 	huge *arr1;
	unsigned char 	huge *arr2;

	unsigned char	testval;  
	long			   x;
	int			   elements_on_line= 0;
	HGLOBAL		   h_data1;
	HGLOBAL		   h_data2;


	h_data1	= GlobalAlloc( GHND, (long) sizeof(long) * (long) ARRSIZE);
	arr1		= ( unsigned char huge * ) GlobalLock( h_data1 );
	h_data2	= GlobalAlloc( GHND, (long) sizeof(long) * (long) ARRSIZE);
	arr2		= ( unsigned char huge * ) GlobalLock( h_data2 );

	//	declare our file...
	ofstream		result_F;

	result_F.open("memMOVt.out");


	for (x = 0 ; x < ARRSIZE ; x++)
	{
		arr1[x] = 0x0f;
	}

	testval = 1;
	for (x = (0+STARTPOINT) ; x < (MOVECNT+STARTPOINT) ; x++)
	{
		arr1[x] = testval;
		testval++;
	}

	memmoveHUGE(arr1+DESTPOINT,arr1+STARTPOINT,MOVECNT);


	testval = 1;
	for (x = (DESTPOINT) ; x < (DESTPOINT+(MOVECNT-1)) ; x++)
	{
		cout << ".";
		if (arr1[x] != testval)
		{
			cout << "woof" << endl;
		}
		testval++;
	}
	cout << endl;

	// setup first address in output file.
	x = 0;
	result_F << setw(10) << setfill('0') << x << ":: ";

	for (x = 0 ; x < ARRSIZE ; x++)
	{
		if(elements_on_line > 15)
		{
			elements_on_line = 0;
			result_F << endl;
			result_F << setw(10) << x << ":: ";
		}          

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