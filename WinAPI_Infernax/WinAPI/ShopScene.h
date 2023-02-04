#pragma once
#include "GameNode.h"
#include "Unit.h"
#include "VillageScene.h"

enum VILLAGE_SHOP
{
	SKILL,
	SMITH,
	SHELTER
};
struct VillageShop
{
	RECT npcRc;
	RECT Rc;
	float X, Y;
};

class ShopScene : public GameNode
{
private:
	VillageShop shop;
	Unit* unit;
	VillageScene* village;

	int worldTimeCount;
	int smithFrameX;
	int magicianFrameX;
	int skillFrameX;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ShopScene() {}
	~ShopScene() {}

};

