

#include <strstrea.h>
#include <iomanip.h>

void main()
{
	ostrstream strm;

	strm.setf(ios::uppercase);

	strm << "abcd" << ends;

	cout << strm.str();

	strm.rdbuf()->freeze(0);

}