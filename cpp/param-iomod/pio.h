// Copyright (C) 1998 ORACLE Corporation ALL RIGHTS RESERVED

#ifndef INC_PIO_H
#define INC_PIO_H

#ifndef INC_TBLINFO_H
#include <tblinfo.h>
#endif // INC_TBLINFO_H
#ifndef INC_STR_CNFG_H
#include <str_cnfg.h>
#endif // INC_STR_CNFG_H

#include <obpar_frcsttocoi.h>
#include <simpstr.h>
#include <acc_col.h>
#include <tserdefs.h>





class TSCDLL_ACC_CLASS io_base;
class TSCDLL_ACC_CLASS dbview;

//@DESC: io_module to join IDT_FORECASTS to CATALOG_OF_IDS.ID_TYPE=504
//@DESC: this must be done THROUGH ID_DESC_SHORT.
//@DESC: The BP Group in their infinite wisdom decided to store
//@DESC: ORG_UNIT_IDS in ID_DESC_SHORT in the CATALOG_OF_IDS in a 
//@DESC: special ID_TYPE.  eesh.
//@DESC: this io_module deals with conversion of ID_DESC_SHORT
//@DESC: to a double (the preferred type for ORG_UNIT_ID)
//@PGMR: RJK
//@CRDT: 19980415
class TSCDLL_OME_CLASS io_p
{
public:

	io_p(DBHandle 	handleNum);
	~io_p();

	void GetID();

private:
	LS						*buf_ID;

	column 				*c_org_unit_id;
	column 				*c_gl_account_id;
	column 				*c_common_coa_id;	// last month of history for BP
	column				*c_x;

	// HasA instead of IsA (more appropriate!)
	io_base				*iob;
	dbview				*v_ID;
};

#endif
