//GLBL: This file modified by TSC GoGlobal
//PGMR: ESB
//DATE: 4/19/96
/*DESC: No changes required.
*/
// TSC Spreadsheet Class - DPM, July 26, 1993

#include <strstream.h>
#ifndef _INC_TSCSPRED_H
#include "tsc_gall.h"
#include "lenmax.h"
#include "tscspred.h"
#include "winutils.h"
#include <mdi.h>
#endif

#define VK_X 88		// glbl:esb - not a string length

//--------------------------------------------------- full constructor
TTSCSpread::TTSCSpread (PTWindowsObject AParent, int AnId, LPSTR ATitle, int X,
			 int Y, int W, int H, PTModule AModule )
	: TSpread(AParent, AnId, ATitle, X, Y, W, H, AModule)
{
  IsCutFlag = FALSE;
}

//--------------------------------------------------- short constructor
TTSCSpread::TTSCSpread (PTWindowsObject AParent, int ResourceId, PTModule AModule )
	: TSpread(AParent, ResourceId, AModule)
{
	IsCutFlag = FALSE;
	// get the default date format from the MS Window control panel
	// these settings are stored and updated in the "win.ini" file.
	char 			strDate[11];
	char			strDelim[2];
	short			bCentury, nFormat;
	short			bLeadingDay, bLeadingMonth;
	GetPrivateProfileString("intl", "sShortDate", "", strDate, 11, "win.ini");
	GetPrivateProfileString("intl", "sDate", "", strDelim, 2, "win.ini");

	// get the global date settings
	GlobalDateSettings( strDate, &bCentury , &nFormat, &bLeadingDay, &bLeadingMonth );
	NewDateFormat.nFormat = nFormat;
	NewDateFormat.bCentury = bCentury;
	NewDateFormat.cSeparator = strDelim[0];
	NewDateFormat.bSpin = FALSE;
	DateGetDlgItemFormat( Parent->HWindow,GetId(), &OldDateFormat );
	OldDateFormat.nFormat = IDF_MMDDYY;
	OldDateFormat.bCentury = TRUE;
	return;
}

//--------------------------------------------------- destructor
TTSCSpread::~TTSCSpread()
{
	//............................ deactivates control bar if left active
	SendMessage( GetApplication()->MainWindow->HWindow,
		SSM_DATACHANGE, FALSE, MAKELONG( NULL, FALSE ) );
}


//----------------------- (JPD) This function will setup the date format in the spreadsheet
void TTSCSpread::SetupWindow()
{
	TSpread::SetupWindow();

	if( !DateSetDlgItemFormat( Parent->HWindow,GetId(), &NewDateFormat ) )
		//GLBL:MAY /*MessageBox(NULL, "Date format could not be set ","Date Format Error",MB_OK);/*GLBL_INVESTIGATE_LINE*/
		MessageBox(NULL, TSCLoadString(GLBL_tscspred_cpp_DateFormatCould_14)/*GLBL:MAY "Date format could not be set "*/,
					TSCLoadString(GLBL_tscspred_cpp_DateFormatError_15)/*GLBL:MAY "Date Format Error"*/, MB_OK);/*GLBL_INVESTIGATE_LINE*/
	return;
}


//----------------------- (JPD) This function formats the date fields in the spreadsheet
LPSS_CELLTYPE TTSCSpread::SetTypeDate(LPSS_CELLTYPE CellType, long Style,
									LPDATEFORMAT lpFormat, LPDATE lpMin, LPDATE lpMax)
{
	(*lpFormat).bCentury = NewDateFormat.bCentury;
	(*lpFormat).nFormat = NewDateFormat.nFormat;
	(*lpFormat).cSeparator = NewDateFormat.cSeparator;

	return( TSpread::SetTypeDate(CellType, Style, lpFormat, lpMin, lpMax) );
}

//----------------------- (JPD) This function checks the data format before the Get Data function
short TTSCSpread::GetData(SS_COORD Col, SS_COORD Row, LPSTR Data)
{
	short rtncode = FALSE;
	SS_CELLTYPE CellType;
	DATE Date;

	// RDE-LYL-11/5/96-EC1110 - Fixes Formula Leaves formula paste GP - pating  in   //
	// 500+ char array into 256 MAX_CHAR_FLD! Wrong! 						  //
	//	char TempData[MAX_CHAR_FLD] = "";
	if ( !Data )
		return rtncode;
	unsigned int DataLen = strlen( Data );
	if ( DataLen < 2048 )
		DataLen = 2048;
	char* TempData = new char[ DataLen + 1 ];	
	strcpy( TempData, "");

	char strColumn[20/*GLBL_USE_RANGE_HERE*/] = GLBL_BLANK_STR/*GLBL: ""*/;

	SSGetData( HWindow, Col, SS_HEADER, strColumn );
	TSpread::GetCellType(Col, Row, &CellType);
	rtncode = TSpread::GetData(Col, Row, TempData);

	if ( strcmp( TempData, "" ) )		//glbl:clc  2.60G.00.009 - Changed from Data to TempData to fix save error in YMD format
	{
		if ( Row != SS_HEADER )
		{
			if( CellType.Type == SS_TYPE_DATE )
			{
					DateStringToDMY( TempData, &Date, &NewDateFormat );
					DateDMYToString( &Date, TempData, &OldDateFormat );
			}	// ar 7103, Globalize Multiplier representations, based on header.
			else if (strcmp(strColumn, TSCLoadString(GLBL_tscspred_cpp_Mult_1)) == 0)
			{
				if (strcmp(TSCLoadString(GLBL_tsccombo_cpp_Days_1), TempData) == 0)
				{
					strcpy(TempData, "D");
				}
				else if (strcmp(TSCLoadString(GLBL_tsccombo_cpp_Years_3), TempData) == 0)
				{
//					strcpy(TempData, "Y");
				}
				else		// Default month
				{
					strcpy(TempData, "M");
				}
			}
		}
	}
	strcpy( Data, TempData );
	// RDE-LYL-11/6/96-EC1110 //
	delete TempData;
	return( rtncode );
}


//----------------------- (JPD) This function checks the data format before the Set Data function
BOOL TTSCSpread::SetData(SS_COORD Col, SS_COORD Row, LPSTR Data)
{
	SS_CELLTYPE CellType;
	DATE Date;

	//	char TempData[MAX_CHAR_FLD] = "";
	// RDE-LYL-11/5/96-EC1110 - Fixes Formula Leaves formula paste GP - pating  in   //
	// 500+ char array into 256 MAX_CHAR_FLD! Wrong! 						  //
	if ( !Data )
		return FALSE;
	unsigned int DataLen = strlen( Data );
	if ( DataLen < 2048 )
		DataLen = 2048;
	char* TempData = new char[ DataLen + 1 ];	
	strcpy( TempData, "");

	char strColumn[20/*GLBL_USE_RANGE_HERE*/] = GLBL_BLANK_STR/*GLBL: ""*/;

	SSGetData( HWindow, Col, SS_HEADER, strColumn );
	//glbl:clc  Check if Data == NULL (GPF if not handled!)
	if (Data)
	{
		strcpy( TempData, Data );
		TSpread::GetCellType(Col, Row, &CellType);
		if ( strcmp( Data, "" ) )
		{
			if ( Row != SS_HEADER )
			{
				if( CellType.Type == SS_TYPE_DATE )
				{
					DateStringToDMY( TempData, &Date, &OldDateFormat );
					if( !DateIntIsValid( &Date ) )
						DateStringToDMY( "01/01/1990", &Date, &OldDateFormat );

					DateDMYToString( &Date, TempData, &NewDateFormat );
				}
				else if (strcmp(strColumn, TSCLoadString(GLBL_tscspred_cpp_Mult_1)) == 0)
				{
					// AR 7103, globalized Multiplier fields -- LDC
					switch (*Data)
					{
						case 'D':
						case 'd':
							strcpy(TempData, TSCLoadString(GLBL_tsccombo_cpp_Days_1));
							break;

						case 'Y':
						case 'y':
							strcpy(TempData, TSCLoadString(GLBL_tsccombo_cpp_Years_3));
							break;

						case 'M':
						case 'm':
						default:
							strcpy(TempData, TSCLoadString(GLBL_tsccombo_cpp_Months_2));
							break;
					}
				}
			}
		}
	} //glbl:clc  Check Data
	// RDE-LYL-11/6/96-EC1110 //
	BOOL Ret = TSpread::SetData( Col, Row, TempData);
	delete TempData;
	return Ret;
}


//----------------------- (JPD) This function fomats column in the spreadsheet
BOOL TTSCSpread::SetFormat( SS_COORD Col, SS_COORD Row, LPSTR strFormatType )
{
	SS_CELLTYPE	CellType;
	SS_CELLTYPE	CellType2;
	DATE			Max;
	DATE      	Min;
	DATEFORMAT 	Type;
	int			cDigit ;

	char strColumn[20/*GLBL_USE_RANGE_HERE*/] = GLBL_BLANK_STR/*GLBL: ""*/;

	SSGetData( HWindow, 3, SS_HEADER, strColumn );
	if (!strcmp( strColumn, TSCLoadString( GLBL_tscspred_cpp_Mult_1 )/*GLBL: "Mult."*/ ))
		SSShowCol( HWindow, 3, FALSE );
	  // SSDelCol( HWindow, 3 );

	if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_BALANCE_2 )/*GLBL: "BALANCE"*/)) {
		// format all the calls as balance
		//GLBL:MAY  Changed to check WIN.INI's iCurrDigits value
		//SSSetTypeFloat( HWindow, &CellType, ES_RIGHT, 25, 2,
		cDigit = GlobalCurrDigits( 2 ) ;

		double val = 999999999999999.0;

		for (int i = 0; i < cDigit; i++)
		{
			val /= 10.0;
		}
		SSSetTypeFloat( HWindow, &CellType, ES_RIGHT, 15 - cDigit, cDigit,
		// JCL, 2_60_MRG2 (code 2.50.10) - Modified line to modify the number
		// format to display one more whole digit.
		//GLBL:MAY -999999999999999.99, 999999999999999.99 );
		-val, val );
	}

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_PERCENT_3 )/*GLBL: "PERCENT"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_RATE_4 )/*GLBL: "RATE"*/))
		// format all the calls as a rate
		SSSetTypeFloat( HWindow, &CellType, ES_RIGHT, 8, 4, -999999999., 999999999. );

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_NUMERIC_5 )/*GLBL: "NUMERIC"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_NUMBER_6 )/*GLBL: "NUMBER"*/ ) )
		// format all the calls as a rate
		SSSetTypeFloat( HWindow, &CellType, ES_RIGHT, 25, 0, -999999999., 999999999. );

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_IDNUMBER_7 )/*GLBL: "ID_NUMBER"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_ID_8 )/*GLBL: "ID"*/ ) )
		// format all the calls as a long numberic
		SSSetTypeEdit( HWindow, &CellType, ES_AUTOHSCROLL | ES_RIGHT, 25, SS_CHRSET_NUM, SS_CASE_NOCASE );

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_strapat_cpp_CODE_5 )/*GLBL: "CODE"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_CHAR_9 )/*GLBL: "CHAR"*/))
		// format all the calls as a code value
		SSSetTypeEdit( HWindow, &CellType, ES_AUTOHSCROLL | ES_RIGHT, 25, SS_CHRSET_CHR, SS_CASE_NOCASE );

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_DATE_10 )/*GLBL: "DATE"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_YEAR_11 )/*GLBL: "YEAR"*/))
	{
		Min.nDay =   1;
		Min.nMonth = 1;
		Min.nYear =  1900;

		Max.nDay =   31;
		Max.nMonth = 12;
		Max.nYear =  2099;

//		Type.bCentury = TRUE;
//		Type.cSeparator = '/';
//		Type.nFormat = IDF_MMDDYY;
//		Type.bSpin = TRUE;

		// format all the calls as a date
		SSSetTypeDate( HWindow, &CellType, ES_RIGHT, &NewDateFormat, &Min, &Max );
	}	// else if

	else if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_FREQ_12 )/*GLBL: "FREQ"*/) ||
				!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_TERM_13 )/*GLBL: "TERM"*/))
	{
		// format all the calls as a term
		SSSetTypeFloat( HWindow, &CellType, ES_RIGHT, 8, 0, -9999999., 99999999. );

		// add a col for multiplier
		if ( SSGetMaxCols( HWindow ) == 2 )
		{
			SSSetMaxCols( HWindow, 3);
			SSInsCol( HWindow, 3 );
		}	// if
		else
			SSShowCol( HWindow, 3, TRUE );

		SSSetData( HWindow, 3, SS_HEADER, TSCLoadString( GLBL_tscspred_cpp_Mult_1 )/*GLBL: "Mult."*/ );
		SSSetColWidth( HWindow, 3, 5 );

		// AR7103 -- LDC, Build string from Globalized D/M/Y
		ostrstream strm; // Not time critical, just use heap allocation
		strm << TSCLoadString(GLBL_tsccombo_cpp_Days_1) << '\t'
			  << TSCLoadString(GLBL_tsccombo_cpp_Months_2) << '\t'
			  << TSCLoadString(GLBL_tsccombo_cpp_Years_3) << ends;

		SSSetTypeComboBox( HWindow, &CellType2, 0, strm.str() );
		strm.rdbuf()->freeze(0);	// Free string
	}	// else if
	else
		// format all the calls as text
		SSSetTypeEdit( HWindow, &CellType, ES_AUTOHSCROLL | ES_RIGHT, 25, SS_CHRSET_CHR, SS_CASE_NOCASE );

	if ( !SSSetCellType( HWindow, Col, Row, &CellType ))
		return FALSE;

	if (!strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_FREQ_12 )/*GLBL: "FREQ"*/) ||
		 !strcmp( strFormatType, TSCLoadString( GLBL_tscspred_cpp_TERM_13 )/*GLBL: "TERM"*/))
			SSSetCellType( HWindow, 3, Row, &CellType2 );

	if (SSGetBool(HWindow, SSB_AUTOSIZE))
	{
		SS_COORD Rows, Cols;
		SSGetAutoSizeVisible(HWindow, &Rows, &Cols);
		if (Cols != SSGetMaxCols(HWindow))
		{
			SSSetAutoSizeVisible(HWindow, Rows,SSGetMaxCols(HWindow));
      }
	}

	return TRUE;
}

//-------------------------------------------- WM_CUT
void  TTSCSpread::WMIsCut(RTMessage Msg)
{
	Msg.Result = IsCutFlag;
}

//-------------------------------------------- WM_KEY_DOWN
void TTSCSpread::WMKeyDown( RTMessage Msg )
{
	if(!IsCutFlag)
	{
		if( Msg.WParam == VK_CONTROL)
		{
			CtrlDown = TRUE;
		}
		else if ( Msg.WParam == VK_SHIFT)
		{
			ShiftDown = TRUE;
		}
		else if ( CtrlDown == TRUE && Msg.WParam == VK_X  || ShiftDown == TRUE && Msg.WParam == VK_DELETE )
		{
			return;
		}
	}
	DefWndProc(Msg);
}

//-------------------------------------------- WM_KEY_UP
void TTSCSpread::WMKeyUp( RTMessage Msg )
{
	if(!IsCutFlag)
	{
		if( Msg.WParam == VK_CONTROL)
		{
			CtrlDown = FALSE;
		}
		else if ( Msg.WParam == VK_SHIFT)
		{
			ShiftDown = FALSE;
		}
	}
	DefWndProc(Msg);
}
