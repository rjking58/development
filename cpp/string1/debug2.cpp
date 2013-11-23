
#include "\volatile\cpp\debug\debug.h"



main()
{
	DebugOut		dbg("testx");

	const int	ar1_len = 20;
	int 			ar1[ar1_len];


	for(int i = 0; i < ar1_len; i++)
		ar1[i] = 100 + i;

	dbg.put(1,"a-one",__FILE__,__LINE__);
	dbg.put('a',"an 'a'",__FILE__,__LINE__);
	dbg.put("12345","a string",__FILE__,__LINE__);
	dbg.put(ar1,"an array",ar1_len, __FILE__,__LINE__ );

}


