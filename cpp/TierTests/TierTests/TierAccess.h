
#pragma once
#include "TierTests.h"
class TierAccess
{
private:
	TierDefinitions::eTierID		m_TierID;
	const TierDefinitions::TierToFeature* m_t_to_f;

public:
	TierAccess(const TierDefinitions::TierToFeature* t_to_f)
		:	m_t_to_f(t_to_f)
	{

	}
	bool GetFeatureAccess(TierDefinitions::eFeatureID featureID);
	void SetTierAccess(TierDefinitions::eTierID);
};