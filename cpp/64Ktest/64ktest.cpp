#include <iostream.h>
#include <fstream.h>

main()
{
	long huge * i_p;
	long i_ofst;
	i_p = new long huge  [100000L];
	ofstream OutFile;
	OutFile.open("64ktest.out", ios::out);

	for(i_ofst=0; i_ofst < 100000L; i_ofst++)
	{
		i_p[i_ofst] = i_ofst;
	}
	for(i_ofst=0; i_ofst < 100000L; i_ofst++)
	{
   	OutFile << i_p[i_ofst] << endl;
	}
}
