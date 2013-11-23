#include "marrays.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

#define TEMPLATES
const	long	ARRSIZE = 32700;

struct MyStruct
{
	int  l;
	int	x;
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

typedef BIM_ISArrayAsVector<MyStruct> MyStructArrIS;
typedef BIM_IArrayAsVector<MyStruct> MyStructArrI;
typedef BIM_ArrayAsVector<long> MyStructArr;


void main(void)
{
	MyStructArr 	*MyStructAfwd 		= new MyStructArr(100,0,1000);
	MyStructArr 	*MyStructArvs 		= new MyStructArr(100,0,1000);
	MyStructArrI 	*MyStructAIfwd 	= new MyStructArrI(100,0,1000);
	MyStructArrI 	*MyStructAIrvs 	= new MyStructArrI(100,0,1000);
	MyStructArrIS 	*MyStructAISfwd 	= new MyStructArrIS(100,0,1000);
	MyStructArrIS 	*MyStructAISrvs 	= new MyStructArrIS(100,0,1000);

	MyStruct		*temp_MyStruct;
	int 			datacnt;

// DO IT YOURSELF ARRAY...
// Arkadi, take the 'huge' out and it will blow up.... rjk
//	MyStruct		* huge * MS;
//	HGLOBAL  	h_data;

	
//	h_data 	= GlobalAlloc( GHND, sizeof( MyStruct	* ) * ARRSIZE );
// Arkadi, take the 'huge' out and it will blow up.... rjk
//	MS			= ( MyStruct * huge * ) GlobalLock( h_data );
//		MS[datacnt] = temp_MyStruct;
//		if ((MS[datacnt])->x != datacnt)

	// BIM_ArrayAsVector fwd.
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		MyStructAfwd->add( datacnt );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		if ((*MyStructAfwd)[datacnt] != datacnt)
		{                       
				cout << "woof" << (*MyStructAfwd)[datacnt] << "  " << datacnt << endl;
		}
	}
	// BIM_ArrayAsVector rvs.
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		MyStructArvs->add( ARRSIZE - datacnt );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		if ((*MyStructArvs)[datacnt] != (ARRSIZE - datacnt))
		{                       
				cout << "woof" << (*MyStructArvs)[datacnt] << "  " << datacnt << endl;
		}
	}


//////////////////////////////////////////////
	//BIM_IArrayAsVector fwd
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		//forward order
		temp_MyStruct->l = datacnt*4097;
		temp_MyStruct->x = datacnt;
		MyStructAIfwd->add( temp_MyStruct );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		// forward order compare
		if ((*MyStructAIfwd)[datacnt]->x !=  datacnt)
		{
			// reverse order compare
//			if ((*MyStructA)[datacnt]->l != (((ARRSIZE - 1) -datacnt)*4097))
			// forward order compare
			if ((*MyStructAIfwd)[datacnt]->l != (datacnt*4097))
			{                       
				cout << "woof" << (*MyStructAIfwd)[datacnt]->x << "  " << datacnt << endl;
			}
		}
	}
	//BIM_IArrayAsVector rvs
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		// reverse order
		temp_MyStruct->l = ((ARRSIZE - 1) - datacnt)*4097;
		temp_MyStruct->x = (ARRSIZE - 1) - datacnt;
		MyStructAIrvs->add( temp_MyStruct );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		//reverse order compare
		if ((*MyStructAIrvs)[datacnt]->x != ((ARRSIZE - 1) -datacnt))
		{
			// reverse order compare
			if ((*MyStructAIrvs)[datacnt]->l != (((ARRSIZE - 1) -datacnt)*4097))
			{                       
				cout << "woof" << (*MyStructAIrvs)[datacnt]->x << "  " << datacnt << endl;
			}
		}
	}





//////////////////////////////////////////


	//BIM_ISArrayAsVector fwd
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		//forward order
		temp_MyStruct->l = datacnt*4097;
		temp_MyStruct->x = datacnt;
		MyStructAISfwd->add( temp_MyStruct );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		// forward order compare
		if ((*MyStructAISfwd)[datacnt]->x !=  datacnt)
		{
			// forward order compare
			if ((*MyStructAISfwd)[datacnt]->l != (datacnt*4097))
			{                       
				cout << "woof" << (*MyStructAISfwd)[datacnt]->x << "  " << datacnt << endl;
			}
		}
	}
	//BIM_IArrayAsVector rvs
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << ".";
		}		
		temp_MyStruct = new MyStruct;
		// reverse order
		temp_MyStruct->l = ((ARRSIZE - 1) - datacnt)*4097;
		temp_MyStruct->x = (ARRSIZE - 1) - datacnt;
		MyStructAISrvs->add( temp_MyStruct );
	}
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
			cout << "." ;
		}
		//reverse order compare
		if ((*MyStructAISrvs)[datacnt]->x != datacnt))
		{
			// reverse order compare
			if ((*MyStructAISrvs)[datacnt]->l != (((ARRSIZE - 1) -datacnt)*4097))
			{                       
				cout << "woof" << (*MyStructAISrvs)[datacnt]->x << "  " << datacnt << endl;
			}
		}
	}

#if 0
//////////////////////////////////////////
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
//			printf(".");
			cout << ".";
		}		
//		temp_MyStruct = new MyStruct;
		// reverse order
//		temp_MyStruct->l = ((ARRSIZE - 1) - datacnt)*4097;
//		temp_MyStruct->x = (ARRSIZE - 1) - datacnt;
		//forward order
//		temp_MyStruct->l = datacnt*4097;
//		temp_MyStruct->x = datacnt;
//		MyStructA->add( temp_MyStruct );
//		MyStructA->add( ( ARRSIZE - datacnt ));
		MyStructA->add( datacnt );
//		MS[datacnt] = temp_MyStruct;
	}
//	printf("\n");
	cout << endl;
	for (datacnt = 0; datacnt < ARRSIZE; datacnt ++)
	{
		if(!(datacnt % 1000))
		{
//			printf(".");
			cout << "." ;
		}
//		if ((MS[datacnt])->x != datacnt)
//		if ((*MyStructA)[datacnt] !=  datacnt)
		//reverse order compare
//		if ((*MyStructA)[datacnt]->x != ((ARRSIZE - 1) -datacnt))
		// forward order compare
//		if ((*MyStructA)[datacnt]->x != datacnt)
//		{
//			if ((MS[datacnt])->l != (datacnt*4097))
			// reverse order compare
//			if ((*MyStructA)[datacnt]->l != (((ARRSIZE - 1) -datacnt)*4097))
			// forward order compare
//			if ((*MyStructA)[datacnt]->l != (datacnt*4097))
			if ((*MyStructA)[datacnt] != (ARRSIZE - datacnt))
			{                       
//				printf("woof\n");
//				cout << "woof" << (*MyStructA)[datacnt]->x << "  " << datacnt << endl;
				cout << "woof" << (*MyStructA)[datacnt] << "  " << datacnt << endl;
//			}
		}
	}

#endif


//	printf("\n");
	cout << endl << " fini" << endl;
//	printf("fini!\n");

//	GlobalUnlock( h_data );
//	GlobalFree( h_data );

}