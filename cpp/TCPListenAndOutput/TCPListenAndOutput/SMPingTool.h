#pragma once

#include "SMUtilitiesLink.h"

// Wraps ping tool
class SMUTILITIES_API SMPingTool
{
public:
	SMPingTool(void);
	virtual ~SMPingTool(void);

	bool operator()(const char* pszIP) const;
	bool TryConnect(const char* pszIPToConnect) const;
};

