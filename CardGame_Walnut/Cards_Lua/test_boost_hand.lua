-- test battlecry-> boost random hand
test_boost_hand = 
{
    path = "Data/boost_hand.png",
    atk = 2,
    health = 2,
    cost = 2,
	
	mEffect = effect.Battlecry,
	mType = etype.Boost,
	mTarget = Target.Hand,
	    mTarget_spec = target_spec.Random,
	mStat = stat.Attack,
    amount = 2
}
    