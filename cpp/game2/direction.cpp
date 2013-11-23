#include "stdafx.h"
#include "direction.h"

static struct XYIncrementStruct
{
	int	XIncrement;
	int	YIncrement;
} XYIncrement[] =	{	
							{
								0,
								-1		//NORTH
							},
							{			
								1,		// EAST
								-1		//NORTH
							},
							{
								1,		// EAST
								0
							},
							{
								1,		// EAST
								1		// SOUTH
							},
							{
								0,
								1		// SOUTH
							},
							{
								-1,	// WEST
								1		// SOUTH
							},
							{
								-1,	// WEST
								0
							},
							{
								-1,	// WEST
								-1		// NORTH
							}
						};


DirectionNS::Direction FindDirection(	int startX,
							  						int startY,
							  						int endX,
							  						int endY)
{
	if(startX>endX) // moving left
	{
		if(startY>endY) // moving up
		{ // left-up
			return DirectionNS::NORTHWEST;
		}
		else if (startY<endY) // moving down
		{ // left -down
			return DirectionNS::SOUTHWEST;
		}
		else // moving horizontal only
		{ // left
			return DirectionNS::WEST;
		}
	}
	else if (startX<endX) // moving right
	{
		if(startY>endY) // moving up
		{ // right up
			return DirectionNS::NORTHEAST;
		}
		else if (startY<endY) // moving down
		{ // right down
			return DirectionNS::SOUTHEAST;
		}
		else // moving horizontal only
		{ // right
			return DirectionNS::EAST;
		}
	}
	else // (startX==endX) // moving vertical only
	{
		if(startY>endY) // moving up
		{ // up
			return DirectionNS::NORTH;
		}
		else if (startY<endY) // moving down
		{ // down
			return DirectionNS::SOUTH;
		}
		else // moving horizontal only
		{ // hopefully impossible.
			return DirectionNS::NORTH;
		}
	}

}


void MapIncrement(	DirectionNS::Direction D,
							int *x,
							int *y )
{

	*x = XYIncrement[(int)D].XIncrement;
	*y = XYIncrement[(int)D].YIncrement;
}

