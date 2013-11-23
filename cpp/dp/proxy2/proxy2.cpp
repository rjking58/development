
#include <iostream.h>

// proxy example
class IFOwner;

class Satellite
{
public:
   virtual void DoAction() = 0;
};

class ConcreteSatelliteA : public Satellite
{
public:
   virtual void DoAction()
	{
		cout 	<< "ConcreteSatelliteA::DoAction()" 
				<< endl;
	}
};

class ConcreteSatelliteB : public Satellite
{
public:
   virtual void DoAction()
	{
		cout 	<< "ConcreteSatelliteB::DoAction()" 
				<< endl;
	}

};

class SatelliteProxy : public Satellite
{
public:
	friend IFOwner;

	SatelliteProxy(Satellite *ConcreteSatellite)
		:	mConcreteSatellite(ConcreteSatellite)
	{
	}

   virtual void DoAction()
	{
		mConcreteSatellite->DoAction();
	}

private:
	void SetNewSatellite(Satellite *ConcreteSatellite)
	{
		mConcreteSatellite = ConcreteSatellite;
	}

	Satellite	*mConcreteSatellite;
};


class IFOwner
{
public:
	IFOwner()
	{
		mCurrentSatellite = new ConcreteSatelliteA;
      mOurProxy = new SatelliteProxy(mCurrentSatellite);

	}

	~IFOwner()
	{
		delete mCurrentSatellite;
		delete mOurProxy;
	}

   Satellite *GetSatellite()
	{
		return mOurProxy;
	}

	void SomeImportantAction()
	{
		// note: this is NOT MULTI-THREADED safe.. AT ALL
		cout << "doing something important" << endl;
		delete mCurrentSatellite;
		mCurrentSatellite = new ConcreteSatelliteB;
		mOurProxy->SetNewSatellite(mCurrentSatellite);
	}

private:
	Satellite		*mCurrentSatellite;
	SatelliteProxy	*mOurProxy;
	
};

void main()
{
	IFOwner		anIF;
	Satellite	*OurSatellite;

	OurSatellite = anIF.GetSatellite();
	OurSatellite->DoAction();
	anIF.SomeImportantAction();
	OurSatellite->DoAction();

}


