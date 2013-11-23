#include "harrays.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

// #include "hvectimp.h"
#define TEMPLATES
const	long	ARRSIZE = 100000L;

struct MyStruct
{
	long  l;
	long	x;
};
//------------------------- OverLoading operators 
inline int operator == (const MyStruct& s1, const MyStruct& s2)
{
	return ( ( s1.x == s2.x ) ? 1 : 0 );
}

//------------------------- OverLoading operators 
inline int operator > (const MyStruct& s1, const MyStruct& s2)
{
	return ( ( s1.x > s2.x ) ? 1 : 0 );
}

//------------------------- OverLoading operators 
inline int operator < (const MyStruct& s1, const MyStruct& s2)
{
	return ( ( s1.x < s2.x ) ? 1 : 0 );
}

typedef BIH_IArrayAsVector<MyStruct> MyStructArr;


void main(void)
{
//	MyStructArr *MyStructA = new MyStructArr(100L,0,1000);
	MyStruct		*temp_MyStruct;
	long 			datacnt;
	// Arkadi, take the 'huge' out and it will blow up.... rjk
	MyStruct		* huge * MS;
	HGLOBAL  	h_data;

	
	h_data 	= GlobalAlloc( GHND, sizeof( MyStruct	* ) * ARRSIZE );
   // Arkadi, take the 'huge' out and it will blow up.... rjk
	MS			= ( MyStruct * huge * ) GlobalLock( h_data );

	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 10000L))
		{
//			printf(".");
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		temp_MyStruct->l = datacnt*4097L;
		temp_MyStruct->x = datacnt;
//		MyStructA->add( temp_MyStruct );
		MS[datacnt] = temp_MyStruct;
	}
//	printf("\n");
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 10000L))
		{
//			printf(".");
			cout << "." ;
		}
		if ((MS[datacnt])->x != datacnt)
		{
			if ((MS[datacnt])->l != (datacnt*4097))
			{
//				printf("woof\n");
				cout << "woof";
			}
		}
	}
//	printf("\n");
	cout << endl << " fini" << endl;
//	printf("fini!\n");

	GlobalUnlock( h_data );
	GlobalFree( h_data );

}
