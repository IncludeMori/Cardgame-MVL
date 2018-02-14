-- test battlecry-> boost field (all)
test_boost_field = 
{
    path = "Data/boost_field.png",
    atk = 2,
    health = 2,
    cost = 2,
	
	mEffect = effect.Battlecry,
	mType = etype.Boost,
	mTarget = Target.Field,
	     mTarget_spec = target_spec.Target,
	mStat = stat.Attack,
    amount = 2
}
    