#pragma once

#include "SMUtilitiesLink.h"
#include<stdexcept>
#include "SMUtilitiesLink.h"
#include "SMUtilities.h"

#pragma warning(push)
#pragma warning(disable:4275)
class SMUTILITIES_API SMRuntimeException 
	#if !defined(_DEBUG)
	: public SMStructuredException
	#endif
{	
#pragma warning(pop)
	struct ErrMessageConstructor
	{
		std::string operator()(DWORD);
	};

	//SMRuntimeException(void);

public:
	// Copy & assignment ops.
	// The defaults were possibly smashing the stack.
	// These where created so that we could step into them and see what is what.
	SMRuntimeException(const SMRuntimeException&);
	SMRuntimeException& operator=(const SMRuntimeException&);

	SMRuntimeException(DWORD);
	SMRuntimeException(HRESULT);
	SMRuntimeException(std::string);
	virtual ~SMRuntimeException(void);

	SMString what() const;

protected:
	SMString exceptionDescription;
};
