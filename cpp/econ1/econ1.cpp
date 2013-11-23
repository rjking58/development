// economic game model #1
// rjk 1/14/97
//
//    make sure to look for FIXME's before expecting this to run!
//
#include <iostream.h>


#include <afxwin.h>		 // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxtempl.h>


#include <math.h>

//forward refs.
class PlanetC;
class StarRouteC;


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// SpecialIndustryC
//		pure virtual class that implements the basic interface 
//		for all industries that can be on a planet.
//
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class SpecialIndustryC
{

		long	Warehouse;
		long	Coffers;
		long  MinimumRequiredPopulation;
		long  ItemPrice;
		long	mMaintenanceFee;

	public:
		SpecialIndustryC(); 
		
		virtual int MakeProduct(int Population) = 0;
		
		virtual void OfferProduct(void) = 0;
		virtual void SellProduct(void) = 0;

	
};

SpecialIndustryC::SpecialIndustryC()
{

} 

class LightWeaponsIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);
};
int LightWeaponsIndustryC::MakeProduct(int Population)
{
	// FIXME
	return 1;
}

void LightWeaponsIndustryC::OfferProduct(void)
{

}
void LightWeaponsIndustryC::SellProduct(void)
{

}

class HeavyWeaponsIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);

};
int HeavyWeaponsIndustryC::MakeProduct(int Population)
{
	// FIXME
	return 1;

}

void HeavyWeaponsIndustryC::OfferProduct(void)
{

}
void HeavyWeaponsIndustryC::SellProduct(void)
{

}


class MetalIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);

};
int MetalIndustryC::MakeProduct(int Population)
{
	// FIXME
	return 1;

}

void MetalIndustryC::OfferProduct(void)
{

}
void MetalIndustryC::SellProduct(void)
{

}


class GemIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);

};
int GemIndustryC::MakeProduct(int Population)
{

	// FIXME
	return 1;
}

void GemIndustryC::OfferProduct(void)
{

}
void GemIndustryC::SellProduct(void)
{

}


class StarShipIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);

};

int StarShipIndustryC::MakeProduct(int Population)
{

	// FIXME
	return 1;
}

void StarShipIndustryC::OfferProduct(void)
{

}
void StarShipIndustryC::SellProduct(void)
{

}

class FuelIndustryC : public SpecialIndustryC
{
	public:
		virtual int MakeProduct(int Population);
		
		virtual void OfferProduct(void);
		virtual void SellProduct(void);

};

int FuelIndustryC::MakeProduct(int Population)
{

	// FIXME
	return 1;
}

void FuelIndustryC::OfferProduct(void)
{

}
void FuelIndustryC::SellProduct(void)
{

}



class SpecialIndustryFactoryC
{
	public: 

	SpecialIndustryC *makeLightWeaponsIndustry()
	{
		SpecialIndustryC *LightWeaponsIndustry;

		LightWeaponsIndustry = new LightWeaponsIndustryC;
		
		return LightWeaponsIndustry;
	}
	SpecialIndustryC *makeHeavyWeaponsIndustry()
	{
		SpecialIndustryC *HeavyWeaponsIndustry;

		HeavyWeaponsIndustry = new HeavyWeaponsIndustryC;

		return HeavyWeaponsIndustry; 
	}
	SpecialIndustryC *makeMetalIndustry()
	{
		SpecialIndustryC *MetalIndustry;

		MetalIndustry = new MetalIndustryC;

		return MetalIndustry; 
	}
	SpecialIndustryC *makeGemIndustry()
	{
		SpecialIndustryC *GemIndustry;

		GemIndustry = new GemIndustryC;

		return GemIndustry; 
	}
	SpecialIndustryC *makeFuelIndustry()
	{
		SpecialIndustryC *FuelIndustry;

		FuelIndustry = new FuelIndustryC;

		return FuelIndustry; 
	}
	SpecialIndustryC *makeStarShipIndustry()
	{
		SpecialIndustryC *StarShipIndustry;

		StarShipIndustry = new StarShipIndustryC;

		return StarShipIndustry; 
	}
};


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// StarShipC
//		a ship that can xport stuff.
//		this class will be subclassed with different types of ships.
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class StarShipC
{

	protected:
		long		mShipsHold;
		long		mFuel;
		long		mFuelEfficiency;
		long		mMaxFuel;												
		long		mSpeed;
		PlanetC	*mOwner;
		long		mMaintenanceFee;

	public:
		StarShipC();
		void Fly(void);

};

StarShipC::StarShipC()
{

}

void StarShipC::Fly(void)
{

}

typedef CTypedPtrArray<CPtrArray, StarShipC *> StarShipArrType;

StarShipArrType	UnownedStarShipArr;

// forward reference for StarRoute!

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//	 The place on a planet where star ships land...
//
//
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class StarBerthC
{

		StarShipC	*StarShip;
		StarRouteC	*LinkedStarRoute;
		long			mMaintenanceFee;

	public:
		StarBerthC () {  }
		
		void				DockStarShip	(StarShipC *StarShip);
		StarShipC		*LaunchStarShip(void);

};

void StarBerthC::DockStarShip(StarShipC *StarShip)
{ 

}

StarShipC	*StarBerthC::LaunchStarShip(void)
{ 
	// need LOTS more code here!!!  FIXME
	return StarShip; 
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// abstraction of food production on a planet
//
//
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class FoodProductionC
{
		int	mCapacity;

		long	mMaintenanceFee;

		long	mFoodStorage;

	public:

		void  Make_Food(int Population);
};

void FoodProductionC::Make_Food(int Population) 
{
}

typedef CTypedPtrArray<CPtrArray, StarBerthC *>			StarBerthArrType;
typedef CTypedPtrArray<CPtrArray, SpecialIndustryC *> SpecialIndustryArrType;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// a planet, and all that it contains.
//
//
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


class PlanetC
{
		// planet's location in cartesian space.
		long							mplanetX;
		long							mplanetY;

		long							mfuel;

		// planets food production sector
		FoodProductionC			mFoodProduction;
	
		// planets industrial sector
		SpecialIndustryArrType	mSpecialIndustryArr;

		// planets people.
		long							mPopulation;

		// yuk... but gotta have it.
		short							mTaxRate;

		// planets treasury...
		long							mTreasury;

		// starBerth's
		StarBerthArrType			mStarBerthArr;

		

	public:

		PlanetC();

		void NextMonth();
		void NextDay();

		void GrowPopulation();

} ;

PlanetC::PlanetC()
{
}

void PlanetC::NextMonth()
{
}


void PlanetC::NextDay()
{

}

void PlanetC::GrowPopulation()
{

}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// a route between planets...
//
//
//
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class StarRouteC
{
	private:
		// the two ends of our star route.
		StarBerthC		*mStarPort1;
		StarBerthC		*mStarPort2;

		// ships enroute to star berths
		StarShipArrType	mStarShipArr;

		long					mStarRouteDistance;
		long					mMaintenanceFee;
		long					mUsageFee;
		long					mCoffers;

	public:
		StarRouteC(	void);
		// when route is assigned to two star berths.
		void AssignStarRoute(StarBerthC *StarPort1,
									StarBerthC *StarPort2,
									long Planet1X,
									long Planet1Y,
									long Planet2X,
									long Planet2Y					);
		// when route is freed for future use.
		void ReleaseStarRoute(	StarBerthC *StarPort1,
										StarBerthC *StarPort2);
		StarBerthC *GetDestStarBerth(StarBerthC *SourceStarBerth);
		
	
};

StarRouteC::StarRouteC(	void )
{

	mStarPort1 = 0;
	mStarPort2 = 0;
}

void StarRouteC::AssignStarRoute(StarBerthC *StarPort1,
											StarBerthC *StarPort2,
											long Planet1X,
											long Planet1Y,
											long Planet2X,
											long Planet2Y)
{
	// FIXME prefigure distance... assign star ports...
}
void StarRouteC::ReleaseStarRoute(	StarBerthC *StarPort1,
												StarBerthC *StarPort2)
{

	// FIXME clear both distance and star ports...
}

StarBerthC *StarRouteC::GetDestStarBerth(StarBerthC *SourceStarBerth)
{
	// for now... FIXME
	// should return the star berth that was NOT passed to us.
	return mStarPort1;
}

typedef CTypedPtrArray<CPtrArray, StarRouteC *> StarRouteArrType;

// available star routes.
StarRouteArrType	AvailableStarRouteArr;

main()
{




}


