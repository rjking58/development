// Copyright (C) 1998 ORACLE Corporation ALL RIGHTS RESERVED

#include "CompatNT.h"
// COMMON
#include <limits.h>
#include <pio.h>			// DEFAULTS DATABASE TABLE I/O CLASS DEFINITION
#include <tscdebug.h>
#include <stddef.h>
#include <acc_col.h>
#include <tblinfo.h>
#include <acc_cond.h>
#include <stdlib.h>

#ifndef INC_ACC_DBVW_H
#include <acc_dbvw.h>
#endif // INC_ACC_DBVW_H
#ifndef INC_ACC_BASE_H
#include <acc_base.h>
#endif // INC_ACC_BASE_H



#ifndef _MSC_VER
#include <strstream.h>
#else
#include <strstrea.h>
#endif
#include <string.h>


#include <lenmax.h>

struct LS
{
	double 	org_unit_id;
	double 	gl_account_id;
	double 	common_coa_id;
	long		x;

	LS(	double 		ou_id = 0.0,
	  		double 		gl = 0.0,
	  		double 		common = 0.0,
			long			an_x = 0)
		:	org_unit_id(ou_id),
			gl_account_id(gl),
			common_coa_id(common),
			x(an_x)
	{
	}
};




static char		*NON_CONST_ORG_UNIT_ID    	= "ORG_UNIT_ID";
static char		*NON_CONST_GL_ACCOUNT_ID	= "GL_ACCOUNT_ID";
static char		*NON_CONST_COMMON_COA_ID	= "COMMON_COA_ID";

static char		*WIERD_TABLE_NAME = "(select org_unit_id,gl_account_id,common_coa_id,1 x from ledger_stat where org_unit_id in (1620,1640) and gl_account_id = 150000 group by org_unit_id,gl_account_id,common_coa_id union select org_unit_id,gl_account_id,common_coa_id,2 x from ledger_stat where org_unit_id in (1620,1640) and common_coa_id = 820 group by org_unit_id,gl_account_id,common_coa_id)";


//@DESC: io_module to join IDT_FORECASTS to CATALOG_OF_IDS.ID_TYPE=504
//@DESC: this must be done THROUGH ID_DESC_SHORT.
//@DESC: The BP Group in their infinite wisdom decided to store
//@DESC: ORG_UNIT_IDS in ID_DESC_SHORT in the CATALOG_OF_IDS in a 
//@DESC: special ID_TYPE.  eesh.
//@DESC: this io_module deals with conversion of ID_DESC_SHORT
//@DESC: to a double (the preferred type for ORG_UNIT_ID)
//@DESC: 
//@DESC: this is the essential 'BP HACK'.
//@PGMR: RJK
//@CRDT: 19980415
io_p::io_p( 	DBHandle 	handleNum)
{
	

	iob = new io_base(handleNum);
	v_ID = new dbview(WIERD_TABLE_NAME, 
							0, 
							sizeof( LS ), 
							1									);
	

	buf_ID = new LS;

	v_ID->SetMaxRows( UINT_MAX/2 );
	
	// non-const char *'s are used due to the interface reqr'd by 
	// the column templates (eesh)  rjk
	
	c_org_unit_id = new c_double(WIERD_TABLE_NAME, 
											NON_CONST_ORG_UNIT_ID, 
											offsetof( LS, org_unit_id ), 
											NON_CONST_ORG_UNIT_ID );
	v_ID->AddColumn(c_org_unit_id);	
	
	c_gl_account_id = new c_double(WIERD_TABLE_NAME, 
											NON_CONST_GL_ACCOUNT_ID, 
											offsetof( LS, gl_account_id ), 
											NON_CONST_GL_ACCOUNT_ID );
	v_ID->AddColumn(c_gl_account_id);	
	
	c_common_coa_id = new c_double(	WIERD_TABLE_NAME, 
												NON_CONST_COMMON_COA_ID, 
												offsetof( LS, common_coa_id ), 
												NON_CONST_COMMON_COA_ID );
	v_ID->AddColumn(c_common_coa_id);	

	c_x = c_sum( new c_long(WIERD_TABLE_NAME, 
									"x", 
									offsetof( LS, x ), 
									"x" 						));
	
	
	iob->SetView( v_ID );

	v_ID->ClearWheres();

	v_ID->AddGroupBy(c_org_unit_id);
	v_ID->AddGroupBy(c_gl_account_id);
	v_ID->AddGroupBy(c_common_coa_id);
	
	
}

//--------------------------------------------------------- Destructor
io_p::~io_p()
{
	delete buf_ID;

	delete iob;
	delete v_ID;
	
}

//---------------------------------------------------------- Get ID
void io_p::GetID()
{
//	ostrstream theJoin;
//	ostrstream theWhere;
	
	TSCLog( ACCESS_LOG, LOW, "/* %d:  *io_p::GetID*/", 142 );

//	theWhere	<<	FILENAME_CATALOG_IDS << "." << ID_TYPE 
//				<< "=" 
//				<< OME_BPCONST::BP_ORG_MAPPING_IDTYPE 
//				<< ends;
				
//	v_ID->AddWhere(new cond_where(theWhere.str()));
	
//	theJoin 	<< "(" 
//				<< 	IDT_FORECASTS << "." << RESULT_SYS_ID
//				<<		"="
//				<<		FILENAME_CATALOG_IDS << "." << SYS_ID_NUM
//				<< ")"
//				<< ends;
				
//	v_ID->AddJoin(new cond_join(theJoin.str()));
		
	
	
	if ( !iob->LoadStart() )
	{
		iob->LoadEnd();
		return NULL;
	}

	while ( iob->LoadNext( buf_ID ) )
	{	
		
		cout << "OU:" << buf_ID->org_unit_id
			  << " GL:" << buf_ID->gl_account_id
			  << " COMMON:" << buf_ID->common_coa_id
			  << " X:" << buf_ID->x
			  << endl;

		// do output here..
	}

	iob->LoadEnd();

//	theJoin.rdbuf()->freeze(0);
//	theWhere.rdbuf()->freeze(0);
}


