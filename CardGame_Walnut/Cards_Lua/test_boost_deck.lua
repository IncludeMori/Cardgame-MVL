-- test battlecry-> boost deck(all)
test_boost_deck = 
{
    --card = "MONSTER"
    path = "Data/boost_deck.png",
    atk = 2,
    health = 2,
    cost = 2,
	
	mEffect = effect.Battlecry,
	mType = etype.Boost,
	mTarget = Target.Deck,
         mTarget_spec = target_spec.Random,
	mStat = stat.Attack,
    amount = 2
}
    