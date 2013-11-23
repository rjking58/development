#ifndef FCPARTITIONDESC_H
#define FCPARTITIONDESC_H

#include "SimpStr.h"
#include <assert.h>
#include <string.h>

struct COL_DATE
{
	int nDay;  	    /* Day of the Month  1..31 */
	int nMonth;     /* Month of the Year 1..12 */
	int nYear;      /* Year */
}; // COL_DATE

#define GLBL_RANGE_8 1

// TBD-RJK
class PDFriend;

//@DESC: Class for use in communicating column values between Units of work
//@DESC: and specific engines.
//@PGMR: RJK
//@CRDT: 19990615
class FCPartitionDesc
{
	// TBD-RJK
	friend class PDFriend;
public:
	enum DataType
	{
		double_type,
		char_ptr_type, 	 
		long_type,
		date_type,
		none
	};


	//@DESC: implement construction/copy semantics.
	//@PGMR: RJK
	//@CRDT: 19990615
	FCPartitionDesc();
	FCPartitionDesc(	SimpleString TableName,
                  SimpleString ColName    );
	//@DESC: virtual destructor required for char *
	//@PGMR: RJK
	//@CRDT: 19990615
	virtual ~FCPartitionDesc();

	FCPartitionDesc(const FCPartitionDesc & pdr);

	FCPartitionDesc& 		operator=( const FCPartitionDesc & pdr);
	
	double 						GetDouble() const;
	const char 	*				GetCharPtr() const;
	long							GetLong() const;
	COL_DATE						GetColDate() const;
	FCPartitionDesc::DataType	GetType() const;
	unsigned int 				GetSize() const;
	void							SetColName(SimpleString ColName);
	void							SetTableName(SimpleString TableName);
	SimpleString				GetColName() const;
	SimpleString				GetTableName() const;

	friend ostream& operator<<(ostream &Strm, const FCPartitionDesc & pdr);

private:
	SimpleString	mColName;
	SimpleString	mTableName;

	DataType 		mColType; 	// type type of the col
						// valid after call to
						// EngineBase::AddPartitionCol
	unsigned int	mColSize;	// The size of the col
						// valid after call to
						// EngineBase::AddPartitionCol
	union
	{
		long			mlongVal;
		double		mdoubleVal;
		char			*mCharPtrVal; 	// This structure retains
											// ownership of this
											// pointer.
		COL_DATE 	mDateVal;
	};					// the current value of
						// the col.
						// valid after call to
						// UnitOfWork::GetValue
	unsigned int 	mColHandle;
};

#endif //FCPARTITIONDESC_H
