

class MapLoc 
{
	MapLoc();
public:
	int x,y;
	MapLoc(int xPos, int yPos) : x(xPos),y(yPos)
	{
	}

};


 
// struct BrainCommand
// {
// 	enum ACommand
// 	{
// 		MOVE = 1,
// 		DEFEND
// 	};
// 
// 	BrainCommand(ACommand Command,MapLoc Destination) :
// 				mCommand(Command),
// 				mDestination(Destination)
// 	{
// 	}
// 	
// 	ACommand	mCommand;
// 	MapLoc		mDestination;
// };

