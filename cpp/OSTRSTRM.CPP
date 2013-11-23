
#include <strings.h>
#include <strstream.h>
#include <iostream.h>

main()
{
	char buf[1000];
	strcpy(buf, "JUNK");

	ostrstream stm(buf, sizeof(buf));

	cerr << buf << endl;

	stm << "STUFF";
	cerr << buf << ":" << endl;	// Garbage.

	stm << '\0';
	cerr << buf << ":" << endl;	// OK.
}
