class DirectionNS
{
public:
	enum Direction
	{                          
		NORTH = 0,             
		NORTHEAST,             
		EAST,                  
		SOUTHEAST,             
		SOUTH,                 
		SOUTHWEST,             
		WEST,                  
		NORTHWEST              
	};

};

DirectionNS::Direction FindDirection(	int startX,
													int startY,
													int endX,
													int endY);

void MapIncrement( 	DirectionNS::Direction D,
				  			int *x,
				  			int *y );

