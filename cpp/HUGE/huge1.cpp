#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>

// #define WINDOWSGLOBALSTYLE
#define NEWSTYLE

void main(void)
{

	#ifdef WINDOWSGLOBALSTYLE
	HGLOBAL  h_data;
	int huge * i_hp;
	int huge * i_hp2;
	long		distance;

	h_data = GlobalAlloc( GHND, sizeof( int ) * 200000L );
	i_hp = ( int huge * ) GlobalLock( h_data );
	i_hp2 = i_hp;

	i_hp2 += 140000L;
	distance = i_hp2 - i_hp;
	cout 	<< "distance =" 
			<< hex 
			<< setfill('0')
			<< "0x"
			<< (int) ((distance >> 24 	) & 0xFF )
			<< (int) ((distance >> 16 	) & 0xFF )
			<< (int) ((distance >> 8 	) & 0xFF )
			<< (int) ((distance 			) & 0xFF );
	#endif

	#ifdef NEWSTYLE
	long huge * i_hp;
	long huge * i_hp2;
	long		distance;
	long		i_ofst;

	i_hp = new long huge[200000L];
	i_hp2 = i_hp;

	i_hp2 += 140000L;
	distance = i_hp2 - i_hp;
	cout 	<< "distance =" 
			<< hex 
			<< setfill('0')
			<< "0x"
			<< (int) ((distance >> 24 	) & 0xFF )
			<< (int) ((distance >> 16 	) & 0xFF )
			<< (int) ((distance >> 8 	) & 0xFF )
			<< (int) ((distance 			) & 0xFF );

	for(i_ofst = 0; i_ofst < 140000L; i_ofst++)
	{
		i_hp[i_ofst] = i_ofst;
	}
	for(i_ofst = 0; i_ofst < 140000L; i_ofst++)
	{
		if(i_hp[i_ofst] != i_ofst)
		{
			cout << "bad match @" << i_ofst << endl;
			exit(0);
		}
		if((i_ofst % 1000L) == 0)
		{
			cout << ".";
		}
	}

	delete [] i_hp;	
	#endif

}