#include <iostream.h>
#include "bases2.h"

// basic class that will be manipulated by the factory...



class PrototypeFactoryXY
{
	AbBaseX *m_AbBaseXProto;
	AbBaseY *m_AbBaseYProto;
	
	public:
		
		PrototypeFactoryXY(	AbBaseX *AbBaseXProto,
							AbBaseY *AbBaseYProto	) :
								m_AbBaseXProto(AbBaseXProto),
								m_AbBaseYProto(AbBaseYProto) { }
		~PrototypeFactoryXY(void)
		{
			delete m_AbBaseXProto;
			delete m_AbBaseYProto;
		}

		virtual AbBaseX * MakeBaseX() const
		{
			return m_AbBaseXProto->Clone();
		}
		virtual AbBaseY * MakeBaseY() const
		{
			return m_AbBaseYProto->Clone();
		}

};

// class AbstractFactoryXY2 : public AbstractFactoryXY
// {
// 	public:
// 
// 		virtual AbBaseX * MakeBaseX(int obj_num) const
// 		{
// 			return new Derived1X(obj_num);
// 		}
// 		virtual AbBaseY * MakeBaseY(int obj_num) const
// 		{
// 			return new Derived2Y(obj_num);
// 		}
// 
// };
// class AbstractFactoryXY3 : public AbstractFactoryXY
// {
// 	public:
// 
// 		virtual AbBaseX * MakeBaseX(int obj_num) const
// 		{
// 			return new Derived2X(obj_num);
// 		}
// 		virtual AbBaseY * MakeBaseY(int obj_num) const
// 		{
// 			return new Derived2Y(obj_num);
// 		}
// 
// };

AbBaseX						*base_px[10];
AbBaseY						*base_py[10];

void make_em(PrototypeFactoryXY *proto_factory)
{
	int x=0;
			
	for (x = 0; x < 4; x++)
	{
		base_px[x] = proto_factory->MakeBaseX();
		base_px[x]->Initialize(x);
		base_py[x] = proto_factory->MakeBaseY();
		base_py[x]->Initialize(x);
	}

}

void main(void )
{
	int						x;
	int						next_obj_num = 0;
	PrototypeFactoryXY	 	proto_factory(new Derived1X, new Derived1Y);
//	PrototypeFactoryXY	 	proto_factory(new Derived2X, new Derived1Y);
//	PrototypeFactoryXY	 	proto_factory(new Derived2X, new Derived2Y);

	make_em(&proto_factory);

	for (x = 0; x < 4; x++)
	{
		base_px[x]->ImHere();
		base_py[x]->ImHere();
	}	

}