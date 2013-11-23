
#pragma once


namespace TierDefinitions
{
	enum eTierID
	{
		TIER_ONE = 1,
		TIER_TWO,
		TIER_THREE,
		TIER_FOUR
	};
	enum eFeatureID
	{
		FEATURE_ONE = 1,
		FEATURE_TWO,
		FEATURE_THREE,
		FEATURE_FOUR,
		FEATURE_FIVE,
		FEATURE_SIX,
		FEATURE_SEVEN,
		FEATURE_EIGHT,
		FEATURE_NINE,
		FEATURE_TEN,
		FEATURE_ELEVEN
	};

	struct TierToFeature
	{
		eTierID		TierID;
		eFeatureID	FeatureID;
		bool		isLast;
	};

}