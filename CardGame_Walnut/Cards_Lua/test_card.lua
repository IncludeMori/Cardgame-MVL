--test: battlecry-> boost self
test_card = 
{
    path = "Data/boost_self.png",
    atk = 2,
    health = 2,
    cost = 2,
	
	mEffect = effect.Battlecry,
	mType = etype.Boost,
	mTarget = Target.Self,
	mStat = stat.Attack,
    amount = 1
}
    