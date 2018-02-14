function ggg(T) local count = 0 for _ in pairs(T) do count = count + 1 end return count end

function get(T,index)
return T[index]
end

effect = 
{
    [0] = "No Effect",
	Nothing = "No Effect",
	
    [1] = "Battlecry",
	Battlecry = "Battlecry",
	
    [2] = "Deathwish",
	Deathwish = "Deathwish",
	
	--[2] = "Turnstart",
	--Turnstart = "Turnstart",
	
	--[3] = "Turnend",
	--Turnend = "Turnend"
}

etype =
{
    [0] = "Boost",
	Boost = "Boost",
	
	[1] = "TEST",
	TEST = "Test"
	
	--[1] = "Deal Damage",
	--Damage = "Deal Damage",
	
	--[2] = "Spawn Token",
	--Spawn = "Spawn Token"
	
}

Target =
{
    [0] = "Self",
    Self = "Self",
	
	[1] = "Field",
	Field = "Field",
	
	[2] = "Hand",
	Hand = "Hand",
	
	[3] = "Deck",
	Deck = "Deck"
}

target_spec =
{
    [0] = "Random",
    Random = "Random",
	
	[1] = "All",
	All = "All",
	
	[2] = "Target",
	Target = "Target" --only for field
}

stat = 
{
    [0] = "Attack",
    Attack = "Attack",
	
	[1] = "Health",
	Health = "Health",
	
	[2] = "Cost",
	Cost = "Cost"
}