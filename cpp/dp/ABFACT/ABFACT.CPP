#include <iostream.h>
#include "bases.h"

// basic class that will be manipulated by the factory...



class AbstractFactoryXY
{

	public:

		virtual AbBaseX * MakeBaseX(int obj_num) const
		{
			return new Derived1X(obj_num);
		}
		virtual AbBaseY * MakeBaseY(int obj_num) const
		{
			return new Derived1Y(obj_num);
		}

};

class AbstractFactoryXY2 : public AbstractFactoryXY
{
	public:

		virtual AbBaseX * MakeBaseX(int obj_num) const
		{
			return new Derived1X(obj_num);
		}
		virtual AbBaseY * MakeBaseY(int obj_num) const
		{
			return new Derived2Y(obj_num);
		}

};
class AbstractFactoryXY3 : public AbstractFactoryXY
{
	public:

		virtual AbBaseX * MakeBaseX(int obj_num) const
		{
			return new Derived2X(obj_num);
		}
		virtual AbBaseY * MakeBaseY(int obj_num) const
		{
			return new Derived2Y(obj_num);
		}

};

AbBaseX						*base_px[10];
AbBaseY						*base_py[10];

void make_em(AbstractFactoryXY *factory)
{
	int x=0;
			
	for (x = 0; x < 4; x++)
	{
		base_px[x] = factory->MakeBaseX(x);
		base_py[x] = factory->MakeBaseY(x);
	}

}

void main(void )
{
	int						x;
	int						next_obj_num = 0;
	AbstractFactoryXY	 	factory;

	make_em(&factory);

	for (x = 0; x < 4; x++)
	{
		base_px[x]->ImHere();
		base_py[x]->ImHere();
	}	

}