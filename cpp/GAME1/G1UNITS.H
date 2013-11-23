#ifndef G1UNITS_H
#define G1UNITS_H 1

#include "maploc.h"

int const MAP_WIDTH 		= 20;
int const MAP_HEIGHT 	= 20;
int const ICON_SCALE 	= 60;
int const MAX_UNITS		= 100;

// should be prime number that is at least
// 20% larger then MAX_UNITS!!
int const MAX_MAP_HASH	= 211;

class MapFeatureType
{
public:
	enum MapFeatureTypes
	{
		NOTHING  = 0,
		TREES,
		BLDNG,
		UNIT
	};
};

// TODO make Unit serializable (and its descendents)


// behaviour of a controllable unit..
class GameMapObserver;

class Unit : public CObject
{
	Unit();
public:
	Unit(int xMapLocation, int yMapLocation) :	mSelected(FALSE),
														      mCurrUnitX(xMapLocation),
														      mCurrUnitY(yMapLocation)
	{

		mUnitRect.top		=	mCurrUnitY * ICON_SCALE;
		mUnitRect.bottom	=	(mCurrUnitY * ICON_SCALE)
									+ (ICON_SCALE-1);

		mUnitRect.left		=	mCurrUnitX * ICON_SCALE;
		mUnitRect.right	=	(mCurrUnitX * ICON_SCALE) 
									+ (ICON_SCALE-1);
	}
	virtual ~Unit()
	{
	}
	virtual void		DrawUnit(CDC* aDC) = 0;
	virtual void		RegisterObserver(GameMapObserver *ObRef) = 0;
	virtual void		MoveOrAttackUnit(int DestinationX, int DestinationY) = 0;
	virtual void 		TimeSliceAction() = 0;

	void				Select()
	{
		mSelected = TRUE;
	}
	void				UnSelect()
	{
		mSelected = FALSE;
	}

	int IsSelected()
	{
		return mSelected;
	}

	MapFeatureType::MapFeatureTypes	Im_a()
	{
		return MapFeatureType::UNIT;
	}
	
	CPoint GetUnitPoint()
	{
		CPoint UnitPoint;

		UnitPoint.x = mUnitRect.right - (ICON_SCALE/2);
		UnitPoint.y = mUnitRect.bottom - (ICON_SCALE/2);

		return UnitPoint;
	}
	CRect GetUnitRect()
	{
		return mUnitRect;
	}


protected:

	// we are currently selected for a command..
	int		mSelected;

	// where the unit is at now.
	// MapLoc	* mUnitLocation;
	int		mCurrUnitX;
	int		mCurrUnitY;
	CRect		mUnitRect;
	int		mUnitIconSize; // height & width same for now

	// Map registration point (so that unit can notify map
	// when it is moving).
	GameMapObserver	*mObsrvrRef;

};

class Soldier : public Unit
{
private:
	Soldier();

	enum Direction             
	{                          
		NORTH = 1,             
		NORTHEAST,             
		EAST,                  
		SOUTHEAST,             
		SOUTH,                 
		SOUTHWEST,             
		WEST,                  
		NORTHWEST              
	};
	enum BrainState            
	{                          
		WAIT = 0,              
		MOVETO_GT_2,           
		MOVETO_EQ_2,           
		MOVETO_EQ_1            
	};
                            
	struct Cortex              
	{                          
		BrainState thisState;  
		BrainState nextState;  
	};
                            
	BrainState	mCurrState;     
	Direction	mCurrDirection; 
	int			mDestinationX;
	int			mDestinationY;


	// WAIT -> WAIT
	// MOVETO_GT_2 
	// 	ifNotBlocked
	// 		Move towards goal
	// 	else
	// 		search for sub path
	// 		move toward sub goal
	// 	endif		
	// 	if = 2 from goal
	// 		transition to MoveTo_EQ_2
	// 	
	// MOVETO_EQ_2
	// 
	// 	ifNotBlocked
	// 		Move towards goal
	// 	else
	// 		Don't do anything 
	// 	endif		
	// 
	// 	if = 1 from goal
	// 		transition to MoveTo_EQ_1
	// 
	// MOVETO_EQ_1
	// 
	// 	ifNotBlocked
	// 		Move towards goal
	// 	else
	// 		Don't do anything 
	// 	endif		
	// 
	// 	if = 1 from goal
	// 		transition to WAIT
	// 
  	// 
	void Think()               
	{                          
		switch(mCurrState)
		{
			case WAIT 			:
			{
				// TODO:  should search for targets here...
				
			}
			case MOVETO_GT_2	:
			{
				
				
			}
			case MOVETO_EQ_2	:
			{

				
			}
			case MOVETO_EQ_1	:
			{

				
			}
		}
	}                          
                            

public:
	Soldier(int xMapLocation, int yMapLocation);
	~Soldier();
	virtual void		DrawUnit(CDC* aDC);
	virtual void		RegisterObserver(GameMapObserver *ObRef);

	// result of a right mouse click when selected..
	virtual void		MoveOrAttackUnit(int DestinationX, int DestinationY)
	{
		mDestinationX = DestinationX;
		mDestinationY = DestinationY;

		// TODO:for now..
      mCurrState = MOVETO_GT_2;
	}

	// called during activity time slice..
	virtual void 		TimeSliceAction()
	{

		Think();
	}

};

class GameMapObserver : public CObject
{
public:
	GameMapObserver();
//	~GameMapObserver();
	void Obsrv_PositionChange(	int 		oldX,
										int		oldY,
										int		newX,
										int		newY,
										Unit 		*unit);

	void Obsrv_PositionNew(		int		newX,
								  		int		newY,
								  		Unit 		*unit);

	Unit *Obsrv_RequestLoc(		int x,
										int y  ) const;

	int	Reserved(				int x, 
										int y) const;

	void	ReserveLoc(				int x, 
										int y);


private:
	struct mapStruct
	{
		Unit	*aUnit;
		int	reserved;
	} mMap[MAP_WIDTH][MAP_HEIGHT];

};


#endif
