#include "SimpStr.h"
#include <assert.h>
#include <string.h>
#include "partitiondesc.h"

ostream& operator<<(ostream &Strm, const FCPartitionDesc & pdr)
{
	if (Strm.opfx())
	{  
		Strm << "start FCPartitionDesc::::::::::::::::" << endl;
		Strm << "mColName:" << pdr.GetColName() << endl;
		Strm << "mTableName;" << pdr.GetTableName() << endl;
		switch(pdr.GetType())
		{
      case FCPartitionDesc::double_type:
				Strm << "mColType::double_type" << endl;
				break;

      case FCPartitionDesc::char_ptr_type:
				Strm << "mColType::char_ptr_type" << endl;
				break;

      case FCPartitionDesc::long_type:

				Strm << "mColType::long_type" << endl;
				break;

      case FCPartitionDesc::date_type:
				Strm << "mColType::date_type" << endl;
				break;

      default:
				Strm << "mColType::NO TYPE!!!" << endl;
				break;

		}
		Strm << "mColSize:" << pdr.GetSize() << endl;
		switch(pdr.GetType())
		{
			case FCPartitionDesc::double_type:
				Strm << "double:" << pdr.GetDouble() << endl;
				break;

         case FCPartitionDesc::char_ptr_type:
				Strm << "char*:" << pdr.GetCharPtr() << endl;
				break;

			case FCPartitionDesc::long_type:
				Strm << "long:" << pdr.GetLong() << endl;
				break;

			case FCPartitionDesc::date_type:
				Strm << "COL_DATE.nDay:" << pdr.GetColDate().nDay << endl;
				Strm << "COL_DATE.nMonth:" << pdr.GetColDate().nMonth << endl;
				Strm << "COL_DATE.nYear:" << pdr.GetColDate().nYear << endl;
				break;

			default:
				Strm << "mColType::NO TYPE!!!" << endl;
				break;

		}
		Strm << "mColHandle:" << pdr.mColHandle << endl;
		
		Strm << "end FCPartitionDesc::::::::::::::::" << endl;
	
	}
	Strm.osfx();

	return Strm;
}


	//@DESC: implement construction/copy semantics.
	//@PGMR: RJK
	//@CRDT: 19990615
FCPartitionDesc::FCPartitionDesc()
   :  mColType(none)
{
}
FCPartitionDesc::FCPartitionDesc(SimpleString TableName,
											SimpleString ColName    )
	:	mTableName(TableName),
		mColName(ColName),
		mColType(none)
{

}
//@DESC: virtual destructor required for char *
//@PGMR: RJK
//@CRDT: 19990615
FCPartitionDesc::~FCPartitionDesc() 
{
	if (mColType == char_ptr_type)
	{
		delete [] mCharPtrVal;
	}
}

FCPartitionDesc::FCPartitionDesc(const FCPartitionDesc & pdr)
{
	mColName 	= pdr.mColName;
	mTableName 	= pdr.mTableName;

	mColType 	= pdr.mColType; 	
	mColSize 	= pdr.mColSize;  
	mColHandle	= pdr.mColHandle;
	switch (mColType)
	{
		case double_type:
			mdoubleVal = pdr.mdoubleVal;
			break;
		case char_ptr_type:
			mCharPtrVal = new char [strlen(pdr.mCharPtrVal) + GLBL_RANGE_8]; 
			strcpy(mCharPtrVal,pdr.mCharPtrVal);
			break;
		case long_type:
			mlongVal = pdr.mlongVal;
			break;
		case date_type:
			mDateVal.nDay		= pdr.mDateVal.nDay;
			mDateVal.nMonth	= pdr.mDateVal.nMonth;
			mDateVal.nYear		= pdr.mDateVal.nYear;
			break;
		case none:
		default:
			break;
	}
}

FCPartitionDesc& FCPartitionDesc::operator=( const FCPartitionDesc & pdr)
{
	if (&pdr != this)
	{
		// do this before we start the copy...
		if (mColType == char_ptr_type)
		{
			if(mCharPtrVal)
			{
					delete [] mCharPtrVal;
					mCharPtrVal = 0;
					mColType = none;
			}
		}
		mColName 	= pdr.mColName;
		mTableName 	= pdr.mTableName;

		mColType 	= pdr.mColType; 	
		mColSize 	= pdr.mColSize;  
		mColHandle	= pdr.mColHandle;
		switch (pdr.mColType)
		{
			case double_type:
            mdoubleVal = pdr.mdoubleVal;
				break;
			case char_ptr_type:
				mCharPtrVal = new char [strlen(pdr.mCharPtrVal) + GLBL_RANGE_8];
				strcpy(mCharPtrVal,pdr.mCharPtrVal);
				break;
			case long_type:
            mlongVal = pdr.mlongVal;
				break;
			case date_type:
            mDateVal.nDay		= pdr.mDateVal.nDay;
            mDateVal.nMonth	= pdr.mDateVal.nMonth;
            mDateVal.nYear		= pdr.mDateVal.nYear;
				break;
			case none:
			default:
				break;
		}
	}
   return *this;
}

double 						FCPartitionDesc::GetDouble() const
{
	assert(mColType == double_type);
	return mdoubleVal;
}
const char 	*				FCPartitionDesc::GetCharPtr() const
{
	assert(mColType == char_ptr_type);
	return mCharPtrVal;
}
long							FCPartitionDesc::GetLong() const
{
	assert(mColType == long_type);
	return mlongVal;
}
COL_DATE						FCPartitionDesc::GetColDate() const
{
	assert(mColType == date_type);
	return mDateVal;
}
FCPartitionDesc::DataType	FCPartitionDesc::GetType() const
{
	return mColType;
}
unsigned int 				FCPartitionDesc::GetSize() const
{
	return mColSize;
}
void							FCPartitionDesc::SetColName(SimpleString ColName)
{
	mColName = ColName;
}
void							FCPartitionDesc::SetTableName(SimpleString TableName)
{
	mTableName = TableName;
}
SimpleString				FCPartitionDesc::GetColName() const
{
	return mColName;
}
SimpleString				FCPartitionDesc::GetTableName() const
{
	return mTableName;
}

