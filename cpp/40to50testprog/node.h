
#ifndef FCINC_NODE_H
#define FCINC_NODE_H

#include <CompatNT.h>


class EULService;

class TSCDLL_IFA_CLASS nodeBase
{
public:
	nodeBase();
	
	virtual	const char*	GetName()
	{
		return( (const char *)name );
	}

	virtual int Cleanup()
	{
		return( FALSE );
	}

private:
	char *name;
};

class TSCDLL_IFA_CLASS EULNode : public nodeBase
{
public:
	
	EULNode();
	~EULNode();

	virtual int Cleanup();
	virtual	const char*	GetName();

	const char *GetDBVersion();
	const char *GetAPIVersion();

private:
	EULService *mService;
};




#endif // FCINC_NODE_H
