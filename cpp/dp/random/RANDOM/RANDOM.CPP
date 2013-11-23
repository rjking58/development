#include <iostream.h>

#include <afxwin.h>		 // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxtempl.h>


enum Direction {North=0,South,East,West};

class MapSite
{
	public:
		// go into the puppy...
		virtual void Enter() = 0;
};


class Room : public MapSite
{
	public:
		Room(int roomNo): _roomNumber(roomNo) { };

		MapSite*	GetSide(Direction d) const
		{
			return _sides[d];
		}
		void SetSide(Direction the_dir, MapSite* the_mapsite)
		{
			_sides[the_dir]= the_mapsite;
		}

		virtual void Enter()
		{
			if(_sides[d]->Enter(d))
			{
				return _sides[d]->OtherSideFrom(this)

			}
			else
			{
				return this;
			} 
		}

		int	GetRoomNo()
		{
			return _roomNumber;
		}

	private:
		MapSite * _sides[4];
		int _roomNumber;
};

class RoomBarrier
{
	virtual int Use(Direction d)= 0;
}

class Wall : public MapSite
{
	public:
		Wall() {};
		virtual void Enter()
		{ 
			// we didn't go anywhere...
			return 0;
		}
		
};

class Door : public MapSite
{
	public:
		Door(Room* R1 = 0,Room* R2 = 0)
		{
			_room1 = R1;
			_room2 = R2;
			_isOpen = 1;
		}

		virtual void Enter()
		{
			// we actually entered the next room
			return 1; 
		}

		Room*	OtherSideFrom(Room * Rx)
		{
			if (Rx == _room1)
			{
				return _room2;
			}
			if (Rx == _room2)
			{
				return _room1;
			}	
			return NULL;

		}

	private:
		Room*	_room1;
		Room*	_room2;
		int		_isOpen;
};


typedef CTypedPtrArray<CPtrArray, Room *> RoomArrayType;

class Maze
{
	public:
		Maze(){};

		void	AddRoom(Room* theRoom)
		{
			RoomArray.Add(theRoom); 
		}
		Room * 	RoomNo(int theRoomNo) const
		{
			int	arrsize= RoomArray.GetSize();
			int	x=0;

			while(		(x < arrsize							)
					&&	(RoomArray[x]->GetRoomNo() != theRoomNo )	)
			{
				x++;
			}
			if(x == arrsize)
			{
				return 0;
			}
			else
			{
				return RoomArray[x];
			}
		}

	private:
		RoomArrayType RoomArray;

};


class MazeGame
{
	public:
		MazeGame()
		{
			theMaze = CreateMaze();
			location = 1;
		}


	private:
		Maze * theMaze;
		Maze * MazeGame::CreateMaze();
		int	 location;
		Direction facing;
};

Maze * MazeGame::CreateMaze()
{
  	Maze*	aMaze = new Maze;
	Room*	r1 = new Room(1);
	Room*	r2 = new Room(2);
	Door*	theDoor = new Door(r1,r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North,new Wall);
	r1->SetSide(South,new Wall);
	r1->SetSide(East,theDoor);
	r1->SetSide(West,new Wall);

	r2->SetSide(North,new Wall);
	r2->SetSide(South,new Wall);
	r2->SetSide(East,new Wall);
	r2->SetSide(West,theDoor);

	return aMaze;
}


//class MazeFactory
//{
//	public:
//		MazeFactory();
//
//		virtual Maze*	MakeMaze() const
//		{	
//			return new Maze;
//		}
//		virtual Wall*	MakeWall() const
//		{
//			return new Wall;
//		}
//		virtual Room*	MakeRoom(int n) const
//		{
//			return new Room(n);
//		}
//		virtual Door*	MakeDoor(Room * r1,Room * r2) const
//		{
//			return new Door(r1,r2);
//		}
//};

//class tst_class // : public CObject <--- only needed if CTypedPtrArray<CObArray, tst_class*>
//{
//	public:
//		tst_class(int i)
//		{
//			m_i = i;
//		}
//
//		int get_i()
//		{
//			return m_i;
//		}
//	private:
//		int m_i;
//
//};

// array of pointers to objects of class 'tst_class'.  non-ordered.
//CTypedPtrArray<CPtrArray, tst_class*> tst_classArray;

void main()
{
//	int x;
//	tst_class *t_c_p;
//
//	for (x=0;x<20;x++)
//	{
//		t_c_p = new tst_class(x);
//		tst_classArray.Add(t_c_p);
//	} 
//	for (x=0 ; x < tst_classArray.GetSize() ; x++ )
//	{
//		cout << tst_classArray[x]->get_i() << " " ;
//	}


}
