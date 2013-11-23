// TierAccess.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "TierAccess.h"

bool TierAccess::GetFeatureAccess(TierDefinitions::eFeatureID featureID)
{
	bool retval = false;
	int currRelator = -1;
	bool foundFeature = false;
	do 
	{
		currRelator++;
		if(featureID == m_t_to_f[currRelator].FeatureID)
		{
			foundFeature = true;
		}

	} while (		( ! m_t_to_f[currRelator].isLast)
				&&	( ! foundFeature				));

	retval = m_t_to_f[currRelator].TierID <= m_TierID;
	
	return retval;
}

void TierAccess::SetTierAccess(TierDefinitions::eTierID tierID)
{
	m_TierID = tierID;
}

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

