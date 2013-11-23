/*
	WAIT -> WAIT
	MOVETO_GT_2 
		ifNotBlocked
			Move towards goal
		else
			search for sub path
			move toward sub goal
		endif		
		if = 2 from goal
			transition to MoveTo_EQ_2
		
	MOVETO_EQ_2

		ifNotBlocked
			Move towards goal
		else
			Don't do anything 
		endif		

		if = 1 from goal
			transition to MoveTo_EQ_1

	MOVETO_EQ_1

		ifNotBlocked
			Move towards goal
		else
			Don't do anything 
		endif		

		if = 1 from goal
			transition to WAIT

  
*/


// class Brain
// {
// 	enum Direction
// 	{
// 		NORTH = 1,
// 		NORTHEAST,
// 		EAST,
// 		SOUTHEAST,
// 		SOUTH,
// 		SOUTHWEST,
// 		WEST,
// 		NORTHWEST
// 	}
// 	enum BrainState
// 	{
// 		WAIT = 0,
// 		MOVETO_GT_2,
// 		MOVETO_EQ_2,
// 		MOVETO_EQ_1
// 	}
// 
// 	struct Cortex
// 	{
// 		BrainState thisState;
// 		BrainState nextState;
// 	}
// 
// 	BrainState	currState;
// 	Direction	currDirection;
// 
// 
// 	void Think()
// 	{
// 
// 	}
// 
// }
// 
// 