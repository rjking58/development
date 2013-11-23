#include "SimpStr.h"
#include <assert.h>
#include <string.h>
#include "partitiondesc.h"



const char * CHARFIELD = "WOOF WOOF";


class PDFriend
{
public:
	static void MakeADouble(FCPartitionDesc &pdr)
	{
		pdr.mColType = FCPartitionDesc::double_type;
		pdr.mColSize = sizeof(double);
		pdr.mdoubleVal = 1.1;
		pdr.mColHandle = 1;

	}
	static void MakeACharPtr(FCPartitionDesc &pdr)
	{
		// must be globalized..
		pdr.mCharPtrVal = new char[strlen(CHARFIELD) + 1];
		strcpy(pdr.mCharPtrVal,CHARFIELD);
		pdr.mColType = FCPartitionDesc::char_ptr_type;
		pdr.mColSize = strlen(CHARFIELD) + 1;
		pdr.mColHandle = 2;
	}
	static void MakeALong(FCPartitionDesc &pdr)
	{
		pdr.mColType = FCPartitionDesc::long_type;
		pdr.mColSize = sizeof(long);
		pdr.mlongVal = 3333;
		pdr.mColHandle = 3;
	}
	static void MakeAColDate(FCPartitionDesc &pdr)
	{
		pdr.mColType = FCPartitionDesc::date_type;
		pdr.mColSize = sizeof(COL_DATE);
		pdr.mDateVal.nDay = 21;
		pdr.mDateVal.nMonth = 7;
		pdr.mDateVal.nYear = 1958;
		pdr.mColHandle = 4;
	}
};


void main()
{
	FCPartitionDesc dbl("dbl","dbl");
	FCPartitionDesc lng("lng","lng");
	FCPartitionDesc charp("charp","charp");
	FCPartitionDesc date("date","date");
	FCPartitionDesc dblx("dblx","dblx");
	FCPartitionDesc lngx("lngx","lngx");
	FCPartitionDesc charpx("charpx","charpx");
	FCPartitionDesc datex("datex","datex");

   PDFriend::MakeADouble(dbl);
	PDFriend::MakeACharPtr(charp);
	PDFriend::MakeALong(lng);
	PDFriend::MakeAColDate(date);


	// test copy constructor..
	FCPartitionDesc dbl2(dbl);
	FCPartitionDesc lng2(lng);
	FCPartitionDesc charp2(charp);
	FCPartitionDesc date2(date);

	dblx = dbl;
	lngx = lng;
	charpx = charp;
	datex = date;


   cout << "dbl----" << endl << dbl ;
   cout << "lng----" << endl << lng ;
   cout << "charp--" << endl << charp ;
   cout << "date---" << endl << date << endl;
   cout << "dbl2----" << endl << dbl2 ;
   cout << "lng2----" << endl << lng2 ;
   cout << "charp2--" << endl << charp2 ;
   cout << "date2---" << endl << date2 << endl;
   cout << "dblx----" << endl << dblx ;
   cout << "lngx----" << endl << lngx ;
   cout << "charpx--" << endl << charpx ;
   cout << "date2x--" << endl << datex << endl;


   cout << dbl.GetDouble() << endl;
   cout << charp.GetCharPtr() << endl;
   cout << lng.GetLong() << endl;
   cout  << date.GetColDate().nMonth   << "/" 
         << date.GetColDate().nDay     << "/"
         << date.GetColDate().nYear    << endl;

}
