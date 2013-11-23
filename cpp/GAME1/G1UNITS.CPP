#include "stdafx.h"
#include "g1units.h"

// Soldier Implementation

Soldier::Soldier(int xMapLocation, int yMapLocation) :
														Unit(xMapLocation,yMapLocation),
													   mCurrState(WAIT),
														mCurrDirection(NORTH)
{
	
	mUnitIconSize = ICON_SCALE;
}

Soldier::~Soldier()
{
}

void	Soldier::DrawUnit(CDC* aDC)
{
	// CDC
	// draw from the top left...
	aDC->TextOut(	mCurrUnitX*ICON_SCALE + 4,
						mCurrUnitY*ICON_SCALE + 4,
						"S",
						1											);

	// draw basic shape
	aDC->MoveTo(mCurrUnitX*ICON_SCALE + 2 ,
					mCurrUnitY*ICON_SCALE + 2 );

	aDC->LineTo(mCurrUnitX*ICON_SCALE + 2 ,
					mCurrUnitY*ICON_SCALE + (ICON_SCALE - 3));

	aDC->LineTo(mCurrUnitX*ICON_SCALE + (ICON_SCALE - 3),
					mCurrUnitY*ICON_SCALE + (ICON_SCALE - 3));

	aDC->LineTo(mCurrUnitX*ICON_SCALE + (ICON_SCALE - 3),
					mCurrUnitY*ICON_SCALE + 2 );

	aDC->LineTo(mCurrUnitX*ICON_SCALE + 2 ,
					mCurrUnitY*ICON_SCALE + 2 );

	// draw selected box if necessary
	if (mSelected)
	{
		CPen* OldPen;
		CPen  DottedPen(PS_DOT,1,RGB(255,0,50)); // Reddish dots for now...

		OldPen = aDC->SelectObject( &DottedPen );

		aDC->MoveTo(mCurrUnitX*ICON_SCALE     ,
						mCurrUnitY*ICON_SCALE     );

		aDC->LineTo(mCurrUnitX*ICON_SCALE     ,
						mCurrUnitY*ICON_SCALE + (ICON_SCALE - 1));

		aDC->LineTo(mCurrUnitX*ICON_SCALE + (ICON_SCALE - 1),
						mCurrUnitY*ICON_SCALE + (ICON_SCALE - 1));

		aDC->LineTo(mCurrUnitX*ICON_SCALE + (ICON_SCALE - 1),
						mCurrUnitY*ICON_SCALE     );

		aDC->LineTo(mCurrUnitX*ICON_SCALE     ,
						mCurrUnitY*ICON_SCALE     );

		aDC->SelectObject(OldPen);
	}
}
void	Soldier::RegisterObserver(GameMapObserver *ObRef)
{
	mObsrvrRef = ObRef;
}


GameMapObserver::GameMapObserver()
{
	int x,y;

	for (x = 0 ; x < MAP_WIDTH ; x++)
	{
		for (y = 0 ; y < MAP_HEIGHT ; y++)
		{
			mMap[x][y].aUnit 		= 0;
			mMap[x][y].reserved 	= 0;
		}
	}

}
void GameMapObserver::Obsrv_PositionChange(  int	oldX,
															int	oldY,
															int 	newX,
															int	newY,
															Unit	*unit)
{
	// for creation of units.
	mMap[oldX][oldY].aUnit = 0;
	Obsrv_PositionNew(newX,newY,unit);
}


void GameMapObserver::Obsrv_PositionNew(	int	newX,
														int	newY,
														Unit 	*unit)
{
	mMap[newX][newY].aUnit = unit;
}


Unit	*GameMapObserver::Obsrv_RequestLoc( int x, int y) const
{
	return mMap[x][y].aUnit;
}

int	GameMapObserver::Reserved(int x, int y) const 
{
	return mMap[x][y].reserved;
}


void	GameMapObserver::ReserveLoc(int x, int y)
{
	mMap[x][y].reserved = TRUE;
}



