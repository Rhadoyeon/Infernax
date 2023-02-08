#pragma once
#include "GameNode.h"

struct Player_Item_Skill
{
	int price;
};

class ItemSkill : public GameNode
{
private:
	vector<Player_Item_Skill> _itemSkill;
	vector<Player_Item_Skill> _playerInventory;

public:
	HRESULT init(void);

	vector<Player_Item_Skill> getItemSkill(void) { return _itemSkill; }

	ItemSkill() {}
	~ItemSkill() {}
};