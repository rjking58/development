// TierTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TierTests.h"
#include "TierAccess.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{

//	const int FeatureCount = (int) TierDefinitions::FEATURE_TEN;
	TierDefinitions::TierToFeature	tier_to_feature[] = 
	{	{TierDefinitions::TIER_ONE,TierDefinitions::FEATURE_ONE,false},
		{TierDefinitions::TIER_TWO,TierDefinitions::FEATURE_TWO,false},
		{TierDefinitions::TIER_ONE,TierDefinitions::FEATURE_THREE,false},
		{TierDefinitions::TIER_THREE,TierDefinitions::FEATURE_FOUR,false},
		{TierDefinitions::TIER_TWO,TierDefinitions::FEATURE_FIVE,false},
		{TierDefinitions::TIER_ONE,TierDefinitions::FEATURE_SIX,false},
		{TierDefinitions::TIER_THREE,TierDefinitions::FEATURE_SEVEN,false},
		{TierDefinitions::TIER_TWO,TierDefinitions::FEATURE_EIGHT,false},
		{TierDefinitions::TIER_ONE,TierDefinitions::FEATURE_NINE,false},
		{TierDefinitions::TIER_TWO,TierDefinitions::FEATURE_TEN,false},
		{TierDefinitions::TIER_FOUR,TierDefinitions::FEATURE_ELEVEN,true}
	};

	TierAccess ta(tier_to_feature);

	ta.SetTierAccess(TierDefinitions::TIER_ONE);

	std::cout << "ONE" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_ONE)?"true":"false") << std::endl;
	std::cout << "TWO" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_TWO)?"true":"false") << std::endl;
	std::cout << "THREE" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_THREE)?"true":"false") << std::endl;
	std::cout << "FOUR" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_FOUR)?"true":"false") << std::endl;
	std::cout << "FIVE" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_FIVE)?"true":"false") << std::endl;
	std::cout << "SIX" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_SIX)?"true":"false") << std::endl;
	std::cout << "SEVEN" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_SEVEN)?"true":"false") << std::endl;
	std::cout << "EIGHT" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_EIGHT)?"true":"false") << std::endl;
	std::cout << "NINE" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_NINE)?"true":"false") << std::endl;
	std::cout << "TEN" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_TEN)?"true":"false") << std::endl;
	std::cout << "ELEVEN" << (ta.GetFeatureAccess(TierDefinitions::FEATURE_ELEVEN)?"true":"false") << std::endl;

	return 0;
}

