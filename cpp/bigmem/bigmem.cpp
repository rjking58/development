#include <windows.h>
#include <strstream.h>
#include <malloc.h>
#define SIZE_TO_TEST 100
#define SIZE_TO_TEST2 100



struct s
{
	char x[SIZE_TO_TEST];
};
struct s2
{
	char x[SIZE_TO_TEST2];
};

main()
{
#if 0
	HGLOBAL mHPtrSorted;
	void * huge * PtrSorted;
	mHPtrSorted = GlobalAlloc( GHND, 1000000L );
	PtrSorted	= ( void * huge * ) GlobalLock( mHPtrSorted );

	_heapadd( PtrSorted,1000000L);
#endif
	long sz = 0;

	while(1)
	{
		new s;
//		new s2;             
		sz += SIZE_TO_TEST;
//		sz += SIZE_TO_TEST2;
		cout << sz << endl;
	}
#if 0
	GlobalUnlock( mHPtrSorted );
	GlobalFree( mHPtrSorted );
#endif
}













